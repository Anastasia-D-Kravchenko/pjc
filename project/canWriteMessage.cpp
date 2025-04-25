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
        std::ifstream file(filename, std::ios::binary);
        uint32_t width, height;
        uint16_t bitsPerPixel;
        readBMPHeader(file, width, height, bitsPerPixel);
        file.close();
        long availableBits = (fileSize - 14 - 40) * 8 / bitsPerPixel; //14 for bmp header, 40 for dib header.
        long messageBits = (message.length() + 2) * 8; // +2 for the two null terminators.
        return messageBits <= availableBits;
    } else if (fileExtension == "png") {
        uint32_t width, height;
        uint16_t bitsPerPixel;
        std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);
        long availableBits = imageData.size() * 8 / bitsPerPixel;
        long messageBits = (message.length() + 2) * 8;
        return messageBits <= availableBits;
    } else {
        throw std::runtime_error("\033[31mUnsupported file format.\033[0m");
    }
}