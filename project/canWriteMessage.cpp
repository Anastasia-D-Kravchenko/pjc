#include "getFileSize.cpp"
#include "readBMPHeader.cpp"
// Function to check if a message can be written to an image
bool canWriteMessage(const std::string& filename, const std::string& message) {
    long fileSize = getFileSize(filename);
    if (fileSize == -1) {
        throw std::runtime_error("\033[31mCould not get file size.\033[0m");
    }

    std::string fileExtension = filename.substr(filename.find_last_of('.') + 1);
    std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case

    if (fileExtension == "bmp") {
        uint32_t width, height;
        uint16_t bitsPerPixel;
        uint32_t dataOffset = readBMPHeader(filename, width, height, bitsPerPixel);
        long availableBits = (fileSize - dataOffset) * 8 / bitsPerPixel; //14 for bmp header, 40 for dib header.
        long messageBits = (message.length() + 2) * 8; // +2 for the two null terminators.
        std::cout << "Message size: " << messageBits/8 << ", available " << availableBits/8 << std::endl;
        return messageBits <= availableBits;
    } else if (fileExtension == "png") {
        uint32_t width, height;
        uint16_t bitsPerPixel;
        std::vector<char> imageData = readPPM(filename, width, height, bitsPerPixel);
        long availableBits = imageData.size() * 8 / bitsPerPixel;
        long messageBits = (message.length() + 2) * 8;
        std::cout << "Message size: " << messageBits/8 << ", available " << availableBits/8 << std::endl;
        if (messageBits > availableBits / 8) throw std::runtime_error("\033[31mMessage is too long to fit in the image.\033[0m");
        return messageBits <= availableBits;
    } else {
        throw std::runtime_error("\033[31mUnsupported file format.\033[0m");
    }
}