#include "readPNG.cpp"
#include "charToBinary.cpp"

// Function to write a message into a PNG image
void writeMessageToPNG(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {throw std::runtime_error("ERROR: Could not open file.");}
    file.close();

    // Read the PNG file data into a vector of characters.
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel); // Return the vector containing the file's data.

    long messageSize = message.length();
    long availableBits = (imageData.size() - 8 - 4*4 - 13) * 8 / bitsPerPixel; //8 for signature, 4 each for length type and 2x crc, 13 for ihdr.
    if (messageSize > availableBits / 8) {
        throw std::runtime_error("Message is too long to fit in the image.");
    }
    std::cout << "Message size: " << messageSize << ", available " << availableBits << std::endl;
    if (messageSize == 0) {
        return; //do nothing
    }

    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    // Add end of message marker
    binaryMessage += "0000000000000000"; //16 zero bits // !!! "end-of-message" marker !!!

    // Embed the message
    int bitIndex = 0;
    int dataOffset = 8 + 4*4 + 13; //start writing after the header, length, type, 2x crc and ihdr.
    for (int i = dataOffset; i < imageData.size(); ++i) {
        for (int j = 0; j < 8; ++j) { // iterates through the bits of the byte, from the most significant bit (7) to the least significant bit (0).
            if (bitIndex < binaryMessage.length()) {
                if (binaryMessage[bitIndex] == '1') { // 0 or 1 and 1 or 1 will give 1
                    imageData[i] |= (1 << (7 - j)); // set j-th bit to 1
                } else { // not 1 and 1 so always 0
                    imageData[i] &= ~(1 << (7 - j)); // set j-th bit to 0
                }
                bitIndex++;
            }
        }
    }

    // Write the modified data back to the PNG file
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        throw std::runtime_error("Could not open PNG file for writing.");
    }
    outfile.write(imageData.data(), imageData.size());
    outfile.close();
}