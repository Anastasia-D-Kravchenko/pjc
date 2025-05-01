#include "readPNG.cpp"
#include "charToBinary.cpp"

// Function to write a message into a PNG image
void writeMessageToPNG(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");}

    // Read the PNG file data into a vector of characters.
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel); // Return the vector containing the file's data.

    long messageSize = message.length()+2;
    long availableBytes = (imageData.size() - 8 - 4*4 - 13) / bitsPerPixel; // 8 for signature, 4 each for length type and 2x crc, 13 for ihdr.
    std::cout << "Message size: " << messageSize << ", available " << availableBytes << std::endl;
    if (messageSize > availableBytes) throw std::runtime_error("\033[31mMessage is too long to fit in the image.\033[0m");
    if (messageSize == 0) return; // Do nothing.

    std::string binaryMessage;
    for (char c : message) binaryMessage += charToBinary(c);
    binaryMessage += "0000000000000000"; // 16 zero bits !!! "end-of-message" marker !!!

    // Embed the message
    int bitIndex = 0;
    int dataOffset = 8 + 4*4 + 13; // Start writing after the header, length, type, 2x crc and ihdr.
    for (size_t i = dataOffset; i < imageData.size() && bitIndex < binaryMessage.length(); ++i) {

    }

    // Write the modified data back to the PNG file
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) throw std::runtime_error("\033[31mCould not open PNG file for writing.\033[0m");
    outfile.write(imageData.data(), imageData.size());
}
