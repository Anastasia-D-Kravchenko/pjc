// Function to read a hidden message from a BMP image
std::string readMessageFromBMP(std::string& filename) {
    std::ifstream file(filename, std::ios::binary); // Open the BMP file in binary mode
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m"); // Throw an error if the file cannot be opened
    }

    uint32_t width, height;       // Variables to store the width and height of the image
    uint16_t bitsPerPixel;    // Variable to store the number of bits per pixel
    uint32_t dataOffset = readBMPHeader(filename, width, height, bitsPerPixel, false); // Read the BMP header and get the data offset
    long fileSize = getFileSize(filename); // Get the size of the file

    std::vector<unsigned char> imageData(fileSize); // Vector to store the image data
    file.seekg(0, std::ios::beg);                 // Set the file pointer to the beginning of the file
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize); // Read the entire file data into the vector

    int n = 1; // Initialize n, which determines how often to check for embedded bits
    if (bitsPerPixel == 1) {
        n = 100; // For 1 bit per pixel, check every 100th byte
    }
    else if (bitsPerPixel == 2 || bitsPerPixel == 4) {
        n = 6; // For 2 or 4 bits per pixel, check every 6th byte.  This is valid for Windows CE
    }

    std::string binaryMessage = ""; // String to store the extracted binary message
    uint32_t bitIndex = 0;          // Index to track the number of bits read
    std::string message = "";       // String to store the decoded message
    bool endOfMessage = false;    // Flag to indicate the end of the message

    // Loop through the image data, starting from the data offset
    for (uint32_t i = dataOffset; i < fileSize && !endOfMessage; ++i) {
        if (i % n == 0) { // Check if the current byte is one that might contain a message bit
            for (int j = 0; j < 8 && !endOfMessage; ++j) {
                if (j == 0) { // Extract the least significant bit
                    if ((imageData[i] >> j) & 1) { // Check if the LSB is 1
                        binaryMessage += '1';     // Append '1' to the binary message
                    } else {
                        binaryMessage += '0';     // Append '0' to the binary message
                    }
                }
            }
            bitIndex++; // Increment the bit index
            if (bitIndex % 8 == 0) { // If 8 bits have been read, convert them to a character
                char c = 0;
                for (int k = 0; k < 8; ++k) {
                    if (binaryMessage[binaryMessage.length() - 8 + k] == '1') {
                        c |= (1 << (7 - k)); // Reconstruct the character from the binary representation
                    }
                }
                if (c == 0) { // Check for the null terminator (end of message marker)
                    endOfMessage = true;
                } else {
                    message += c; // Append the character to the message
                }
            }
        }
    }
    return message; // Return the extracted message
}