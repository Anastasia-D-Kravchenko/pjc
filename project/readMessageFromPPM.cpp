#include "binaryToChar.cpp"

// Function to read a message from a PPM image
std::string readMessageFromPPM(const std::string& filename) {
    uint32_t width, height;
    uint16_t bitsPerPixel;
    // Read the PPM image data, including header information.
    std::vector<char> imageData = readPPM(filename, width, height, bitsPerPixel);

    std::string binaryMessage = "";  // Store the extracted binary message.
    std::string message = "";        // Store the final ASCII message.
    int bitIndex = 0;              // Track the current bit being read.

    // PPM stores data as RGB triples, so each byte is one component of a pixel.
    // We'll extract the LSB from each byte.

    // Loop through the image data, extracting one bit at a time.
    while (bitIndex < imageData.size() * 8) {
        size_t byteIndex = bitIndex / 8;
        int bitOffset = bitIndex % 8;

        // Extract the least significant bit.
        unsigned char currentByte = imageData[byteIndex];
        char lsb = ((currentByte >> (7 - bitOffset)) & 1) ? '1' : '0';
        binaryMessage += lsb;
        bitIndex++;

        // Check for the end-of-message marker ("00000000").
        if (binaryMessage.length() >= 8 && binaryMessage.substr(binaryMessage.length() - 8, 8) == "00000000") {
            binaryMessage = binaryMessage.substr(0, binaryMessage.length() - 8); // Remove the marker.
            break; // Exit the loop as the message end is found.
        }
    }

    // Convert the binary message to an ASCII string.
    for (size_t i = 0; i < binaryMessage.length(); i += 8) {
        if (i + 8 > binaryMessage.length()) break; // Make sure we don't read out of bounds.
        message += binaryToChar(binaryMessage.substr(i, 8));
    }
    return message; // Return the extracted ASCII message.
}