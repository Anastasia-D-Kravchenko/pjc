// Function to read a hidden message from a PPM image
std::string readMessageFromPPM(std::string& filename) {
    uint32_t width, height;       // Variables to store the width and height of the image
    uint16_t bitsPerPixel;    // Variable to store the number of bits per pixel (though often not directly used in PPM)
    std::vector<char> imageData;  // Vector to store the image data as characters
    std::string magicNumber, maxColorValueStr; // Variables to store PPM header information

    try {
        // Read the PPM image data and header information
        imageData = readPPM(filename, width, height, bitsPerPixel, magicNumber, maxColorValueStr);
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Error reading PPM data: " + std::string(e.what()));
    }

    std::string binaryMessage = ""; // String to store the extracted binary message
    std::string message = "";       // String to store the decoded message
    bool endOfMessage = false;    // Flag to indicate the end of the message
    uint32_t bitIndex = 0;          // Index to track the number of bits read
    uint32_t charCount = 0;       // Keep track of the number of characters processed
    size_t dataSize = (magicNumber == "P6") ? width * height * 3 : imageData.size();
    if (dataSize == 0)throw std::runtime_error("No data read from the PPM file.");

    // Handle different PPM formats (P6 and P3)
    if (magicNumber == "P6") {
        // For P6 (binary PPM), extract message from the least significant bit of each color component
        for (uint32_t i = 0; i < width * height * 3 && !endOfMessage; ++i) {
            for (int j = 0; j < 8 && !endOfMessage; ++j) {
                if (j == 0) {
                    if ((imageData[i] >> j) & 1) {
                        binaryMessage += '1';
                    } else {
                        binaryMessage += '0';
                    }
                }
            }
            bitIndex++;
            if (bitIndex % 8 == 0) {
                char c = 0;
                for (int k = 0; k < 8; ++k) {
                    if (binaryMessage[binaryMessage.length() - 8 + k] == '1') {
                        c |= (1 << (7 - k));
                    }
                }
                if (c == 0) { //check for end of message
                    endOfMessage = true;
                } else {
                    message += c;
                }
            }
        }
    } else {
        // For P3, extract message from specific patterns (e.g., space after a character)
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
    return message; // Return the extracted message
}