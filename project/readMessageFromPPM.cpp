#include "binaryToChar.cpp"

std::string readMessageFromPPM(std::string& filename) {
    uint32_t width, height;
    uint16_t bitsPerPixel;
    std::vector<char> imageData;
    std::string magicNumber;
    int maxColorValue;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }
    std::string widthStr, heightStr, maxColorValueStr;

    // Read the PPM header.
    std::getline(file, magicNumber);
    magicNumber = trim(magicNumber);
    // Check for the P3 magic number
    if (magicNumber != "P3" && magicNumber != "P6") {
        throw std::runtime_error("\033[31mERROR: Invalid PPM format. Only P3 and P6 are supported.\033[0m");
    }
    file >> width >> height >> maxColorValueStr;
    file.ignore(); // Consume the newline character after the header.

    imageData = readPPM(filename, width, height, bitsPerPixel);

    std::string binaryMessage = "";
    std::string message = "";
    bool endOfMessage = false;
    uint32_t bitIndex = 0;
    uint32_t charCount = 0; // Keep track of the number of characters processed

    if (magicNumber == "P6") {
        throw std::runtime_error("\033[31mERROR: This function is designed for P3 format with the specified encoding method.\033[0m");
    } else {
        for (uint32_t i = 0; i < width * height * 3 - 1 && !endOfMessage; ++i) {
            if (imageData[i] != ' ' && imageData[i + 1] == ' ') {
                binaryMessage += ((imageData[i] & 1) == 1) ? '1' : '0';
                bitIndex++;

                if (bitIndex % 8 == 0) {
                    char c = 0;
                    for (int k = 0; k < 8; ++k) {
                        if (binaryMessage[binaryMessage.length() - 8 + k] == '1') {
                            c |= (1 << (7 - k));
                        }
                    }
                    if (c == 0) {
                        endOfMessage = true;
                    } else {
                        message += c;
                        charCount++;
                    }
                }
            }
        }
    }
    return message;
}
