// Function to write a message into a BMP image
void writeMessageToBMP(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }

    // Read the BMP file header
    uint32_t dataOffset = readBMPHeader(filename, width, height, bitsPerPixel);

    // Calculate the number of bytes available for the message
    long fileSize = getFileSize(filename);
    uint32_t dataSize = fileSize - dataOffset; // Calculates the size of the image data (excluding the header) in bytes.
    uint32_t availableBits = dataSize / bitsPerPixel; // Determines the number of bits available for embedding the message, considering the bits per pixel.
    long messageBits = message.length() + 2; // Calculates the total number of bits required to store the message (including two null as a marker).
    std::cout << "Message size: " << messageBits << ", available " << availableBits << std::endl;
    if (messageBits > availableBits) throw std::runtime_error("\033[31mERROR: Message is too long to fit in the image.\033[0m"); // Throws an error if the message is too large.

    // Read the entire image data
    std::vector<unsigned char> imageData(fileSize); // Creates a vector of unsigned characters to hold the entire content of the BMP file.
    file.seekg(0, std::ios::beg); // Pointer.
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize); // Reads the entire file content into the imageData vector.

    std::string binaryMessage; // Initializes an empty string to store the binary representation of the message.
    for (char c : message) binaryMessage += charToBinary(c);
    binaryMessage += "0000000000000000"; //16 zero bits !!! "end-of-message" marker !!!

    // Embed the message
    uint32_t bitIndex = 0; // Initializes an index to keep track of the current bit being processed in the binary message.
    for (uint32_t i = dataOffset; i < fileSize && bitIndex < binaryMessage.length(); ++i) {
        for (int j = 0; j < 8 && bitIndex < binaryMessage.length(); ++j) {
            // Iterates through the 8 bits of the current byte in the image data.
            if ( j == 0 ){
                if (binaryMessage[bitIndex] == '1') { // 0 or 1 and 1 or 1 will give 1.
                    imageData[i] |= (1 << j); // Sets the j-th bit of the current image data byte to 1 if the corresponding bit in the binary message is 1.
                } else { // Not 1 and 1 so always 0.
                    imageData[i] &= ~(1 << j); // Sets the j-th bit of the current image data byte to 0 if the corresponding bit in the binary message is 0.
                }
                // j = 0:  Targets the LSB.  1 << 0 results in 00000001.
                // j = 1:  Targets the second LSB. 1 << 1 results in 00000010.
                // j = 2:  Targets the third LSB.  1 << 2 results in 00000100.
                // ...and so on.
                bitIndex++; // Moves to the next bit in the binary message.
            }
        }
    }

    // Write the modified image data back to the file
    std::ofstream outfile("ref_" + filename, std::ios::binary); // Opens the specified file in binary mode for writing.
    if (!outfile.is_open()) throw std::runtime_error("\033[31mERROR: Could not open file for writing.\033[0m"); // Throws an error if the output file cannot be opened.
    outfile.write(reinterpret_cast<char*>(imageData.data()), fileSize); // Writes the modified image data (including the embedded message) back to the file.
}