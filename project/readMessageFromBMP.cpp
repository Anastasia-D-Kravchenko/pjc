std::string readMessageFromBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }

    // Read the BMP file header
    unsigned char bmpSignature[2];
    uint32_t fileSize;
    uint32_t dataOffset;

    file.read(reinterpret_cast<char*>(bmpSignature), 2);
    file.read(reinterpret_cast<char*>(&fileSize), 4);
    file.seekg(10, std::ios::beg); // Seek to the data offset
    file.read(reinterpret_cast<char*>(&dataOffset), 4);

    // Calculate the number of bytes available for the message
    uint32_t dataSize = fileSize - dataOffset;
    std::vector<unsigned char> imageData(fileSize);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize);

    std::string binaryMessage = "";
    uint32_t bitIndex = 0;
    std::string message = "";
    bool endOfMessage = false;
    for (uint32_t i = dataOffset; i < fileSize && !endOfMessage; ++i) {
        for (int j = 0; j < 8 && !endOfMessage; ++j) {
            if (j == 0) {
                if (binaryMessage[bitIndex] == '1') { // 0 or 1 and 1 or 1 will give 1.
                    imageData[i] |= (1 << j);
                } else { // Not 1 and 1 so always 0.
                    imageData[i] &= ~(1 << j);
                }
            }
            bitIndex++;
        }
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
    return message;
}