#include "additional/getFileSize.cpp"
#include "BMP/readBMPHeader.cpp"
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
        uint32_t dataOffset = readBMPHeader(filename, width, height, bitsPerPixel, false);
        uint32_t dataSize = fileSize - dataOffset;
        uint32_t availableBytes = dataSize / 8;
        int n = 1;
        long messageBytes = message.length() + 2;
        if (bitsPerPixel == 1) {n=100;std::cout << "Message size: " << messageBytes << ", available " << availableBytes/100 << std::endl;}
        else if (bitsPerPixel == 2 || bitsPerPixel == 4) {n=6;std::cout << "Message size: " << messageBytes << ", available " << availableBytes/6 << std::endl;} // legal on Windows CE
        else {std::cout << "Message size: " << messageBytes << ", available " << availableBytes << std::endl;}
        return messageBytes < availableBytes/n;
    } else if (fileExtension == "ppm") {
        uint32_t width, height;
        uint16_t bitsPerPixel;
        std::string magicNumber, maxColorValueStr;
        std::vector<char> imageData = readPPM(filename, width, height, bitsPerPixel,magicNumber, maxColorValueStr);
        int bytesPerPixel = (magicNumber == "P6") ? 3 : 1;
        long availableBits = (magicNumber == "P6") ? width * height * bytesPerPixel * 8 : width * height * 8;
        std::cout << "Message size: " << message.length() << ", available " << ((magicNumber == "P6") ? availableBits/(8*8) : availableBits/( 10 * 8)) << std::endl;
        return message.length() * 8 < ((magicNumber == "P6") ? availableBits/10 : availableBits/8);
    } else {
        throw std::runtime_error("\033[31mUnsupported file format.\033[0m");
    }
}