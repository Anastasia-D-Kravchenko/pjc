#include "binaryToChar.cpp"

// Function to read a message from a PNG image
std::string readMessageFromPNG(const std::string& filename) {
    uint32_t width, height;
    uint16_t bitsPerPixel;
    // Read the PNG image data, including header information. 
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);

    std::string binaryMessage = "";  // Store the extracted binary message.
    std::string message = "";        // Store the final ASCII message.
    int bitIndex = 0;              // Track the current bit being read.

    // Calculate the offset to the start of the pixel data within the imageData vector.
    // This calculation is specific to how the PNG data is structured after the header and IHDR chunk.
    int dataOffset = 8 + 4*4 + 13; // Start reading after header, length, type, 2x crc, and ihdr.

    // Loop through the image data, extracting bits until the "end-of-message" marker is found.
    while (bitIndex + 8 <= imageData.size() * 8) {
        std::string currentByteBits = ""; // Store the binary representation of the current byte.
        // Extract 8 bits (1 byte) from the image data.
        for (int i = dataOffset + (bitIndex / 8); i < dataOffset + (bitIndex / 8) + 1; ++i) {
            for (int j = 0; j < 8; ++j) {
                // Extract each bit from the current byte and append it to currentByteBits.
                currentByteBits += ((imageData[i] >> (7 - j)) & 1) ? '1' : '0';
            }
        }
        binaryMessage += currentByteBits; // Append the extracted byte's bits to the binary message.
        bitIndex += 8; // Move to the next byte.

        // Check if enough bits have been read to check for the end-of-message marker.
        if (binaryMessage.length() >= 16)
        {
            // Check for the end-of-message marker ("0000000000000000").
            if (binaryMessage.substr(binaryMessage.length() - 16, 16) == "0000000000000000") {
                binaryMessage = binaryMessage.substr(0, binaryMessage.length() - 16); // Remove the marker.
                break; // Exit the loop as the message end is found.
            }
        }

    }
    // Convert the binary message to an ASCII string.
    for (size_t i = 0; i < binaryMessage.length(); i += 8)
    {
        message += binaryToChar(binaryMessage.substr(i, 8)); // Convert each 8-bit segment to a character.
    }
    return message; // Return the extracted ASCII message.
}