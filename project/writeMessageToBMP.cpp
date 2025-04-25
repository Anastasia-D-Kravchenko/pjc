// Function to write a message into a BMP image
void writeMessageToBMP(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
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
    uint32_t availableBits = dataSize; // 1 byte per pixel.
    uint32_t messageSizeInBits = message.length() * 8;

     if (messageSizeInBits > availableBits) {
        throw std::runtime_error("\033[31mERROR: Message is too long to fit in the image.\033[0m");
    }

    // Read the entire image data
    std::vector<unsigned char> imageData(fileSize);
    file.seekg(0, std::ios::beg);
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize);
    file.close();

    // Convert message to binary
    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    binaryMessage += "0000000000000000"; // End of message marker

    // Embed the message in the least significant bits
    uint32_t bitIndex = 0;
    for (uint32_t i = dataOffset; i < fileSize && bitIndex < binaryMessage.length(); ++i) {
        for (int j = 0; j < 8 && bitIndex < binaryMessage.length(); ++j) {
            if (binaryMessage[bitIndex] == '1') {
                imageData[i] |= (1 << j); // Set the j-th bit to 1
            } else {
                imageData[i] &= ~(1 << j); // Set the j-th bit to 0
            }
            bitIndex++;
        }
    }

    // Write the modified image data back to the file
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file for writing.\033[0m");
    }
    outfile.write(reinterpret_cast<char*>(imageData.data()), fileSize);
    outfile.close();
}