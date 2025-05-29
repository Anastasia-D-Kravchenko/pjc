// Function to write a message into a BMP image
void writeMessageToBMP(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }

    // Read the BMP file header
    uint32_t dataOffset = readBMPHeader(filename, width, height, bitsPerPixel, true);

    // Calculate the number of bytes available for the message
    long fileSize = getFileSize(filename);
    uint32_t dataSize = fileSize - dataOffset; // Calculates the size of the image data (excluding the header) in bytes
    uint32_t availableBytes = dataSize / 8; // Determines the number of bits available for embedding the message, considering the bits per pixel
    int n = 1;
    long messageBytes = message.length() + 2; // Calculates the total number of bits required to store the message (including two null as a marker)
    if (bitsPerPixel == 1) {n=100;std::cout << "Message size: " << messageBytes << ", available " << availableBytes/100 << std::endl;}
    else if (bitsPerPixel == 2 || bitsPerPixel == 4) {n=6;std::cout << "Message size: " << messageBytes << ", available " << availableBytes/6 << std::endl;} // legal on Windows CE
    else {std::cout << "Message size: " << messageBytes << ", available " << availableBytes << std::endl;}
    if (messageBytes > availableBytes/n) throw std::runtime_error("\033[31mERROR: Message is too long to fit in the image.\033[0m");

    // Read the entire image data
    std::vector<unsigned char> imageData(fileSize); // Creates a vector of unsigned characters to hold the entire content of the BMP file
    file.seekg(0, std::ios::beg); // Pointer.
    file.read(reinterpret_cast<char*>(imageData.data()), fileSize); // Reads the entire file content into the imageData vector

    std::string binaryMessage; // Initializes an empty string to store the binary representation of the message
    for (char c : message) binaryMessage += charToBinary(c);
    binaryMessage += "0000000000000000"; //16 zero bits !!! "end-of-message" marker !!!

    // Embed the message
    uint32_t bitIndex = 0; // Initialize the bit index to track the current bit being processed
    std::cout << "Bits per pixel: " << bitsPerPixel << std::endl;
    for (uint32_t i = dataOffset; i < fileSize && bitIndex < binaryMessage.length(); ++i) {
        if (i%n==0){ // Check if the current byte is one where we can embed data
            for (int j = 0; j < 8 && bitIndex < binaryMessage.length(); ++j) {
                if ( j == 0 ){ // Embed the data in the 7th bit
                    if (binaryMessage[bitIndex] == '1') {
                        imageData[i] |= 1; // Set the least significant bit to 1
                    } else {
                        imageData[i] &= ~1; // Set the least significant bit to 0
                    }
                    bitIndex++; // Move to the next bit of the message
                }
            }
        }
    }

    size_t lastSlash = filename.find_last_of('/');
    size_t startPos = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
    std::string fileName = filename.substr(startPos);
    // Write the modified image data back to the BMP file
    std::ofstream outfile("changedImages/bmp/ref_"+fileName); // Open the output file (prefixed with "ref_")

    if (!outfile.is_open()) throw std::runtime_error("\033[31mERROR: Could not open file for writing.\033[0m"); // Throws an error if the output file cannot be opened
    outfile.write(reinterpret_cast<char*>(imageData.data()), fileSize); // Writes the modified image data (including the embedded message) back to the file
}