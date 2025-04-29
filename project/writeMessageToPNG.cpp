#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <stdexcept>
#include "readPNG.cpp"
#include "charToBinary.cpp"

// Function to calculate CRC
unsigned int calculateCRC(const unsigned char* type, const std::vector<unsigned char>& data) {
    unsigned int crc = 0xFFFFFFFF;
    std::vector<unsigned char> crcData(type, type + 4);
    crcData.insert(crcData.end(), data.begin(), data.end());
    for (unsigned char byte : crcData) {
        for (int i = 7; i >= 0; --i) {
            crc = (crc & 0x80000000) ? (crc << 1) ^ 0x04C11DB7 : (crc << 1);
            crc ^= ((byte >> i) & 1) << 31;
        }
    }
    return crc ^ 0xFFFFFFFF;
}

// Placeholder for compress data -  DO NOT USE THIS IN REAL CODE
std::vector<unsigned char> compressData(const std::vector<unsigned char>& data) {
    std::cout << data << std::endl;
    return data; //  Return the original data as is (no compression)
}

// Placeholder for decompress data -  DO NOT USE THIS IN REAL CODE
std::vector<unsigned char> decompressData(const std::vector<unsigned char>& data, uint32_t width, uint32_t height) {
    return data; // Return the original data as is (no decompression)
}

// Function to write chunk
void writeChunk(std::ofstream& file, unsigned int length, const unsigned char* type, const std::vector<unsigned char>& data, unsigned int crc) {
    // Write the length in big-endian order
    file.write(reinterpret_cast<char*>(&length), 4);
    // Write the chunk type
    file.write(reinterpret_cast<const char*>(type), 4);
    // Write the chunk data
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    // Write the CRC in big-endian order
    file.write(reinterpret_cast<char*>(&crc), 4);
}

// Function to write a message into a PNG image
void writeMessageToPNG(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }

    // Read the PNG file data into a vector of characters.
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);

    // Find the starting position of the IDAT chunk.  This is crucial.
    size_t idatOffset = 0;
    for (size_t i = 8; i < imageData.size() - 4; ++i) {
        if (imageData[i] == 'I' && imageData[i + 1] == 'D' && imageData[i + 2] == 'A' && imageData[i + 3] == 'T') {
            idatOffset = i - 4; //  4 bytes for the length
            break;
        }
    }

    if (idatOffset == 0) {
        throw std::runtime_error("\033[31mERROR: IDAT chunk not found.\033[0m");
    }
    // Extract the IDAT data
    uint32_t idatLength;
    std::memcpy(&idatLength, imageData.data() + idatOffset, 4);
    idatLength = __builtin_bswap32(idatLength); // Convert from big-endian

    std::vector<unsigned char> compressedIdatData(imageData.begin() + idatOffset + 8, imageData.begin() + idatOffset + 8 + idatLength); //+8 to skip length and type

    // Decompress the IDAT data
    std::vector<unsigned char> decompressedData = decompressData(compressedIdatData, width, height);

    // Convert the message to binary
    std::string binaryMessage = "";
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    // Add end of message delimiter
    binaryMessage += "0000000000000000";

    // Check if the message can fit into the image data
    if (binaryMessage.length() > decompressedData.size() * 8) {
        throw std::runtime_error("\033[31mERROR: Message is too long to fit in the image.\033[0m");
    }

    int bitIndex = 0;
    // Embed the message into the decompressed image data
    for (size_t i = 0; i < binaryMessage.length(); ++i) {
        // Get the bit from the binary message
        char bit = binaryMessage[i];

        // Modify the LSB of the byte
        if (bit == '0') {
            decompressedData[bitIndex / 8] &= 0xfe; // Clear the LSB
        } else {
            decompressedData[bitIndex / 8] |= 0x01; // Set the LSB
        }
        bitIndex++;
    }
    // Recompress the data
    std::vector<unsigned char> recompressedData = compressData(decompressedData);
    uint32_t recompressedIdatLength = recompressedData.size();
    unsigned char idatType[4] = {'I', 'D', 'A', 'T'};
    unsigned int recompressedIdatCrc = calculateCRC(idatType, recompressedData);

    // Construct the new image data
    std::vector<char> newImageData;
    // Copy the PNG signature
    newImageData.insert(newImageData.end(), imageData.begin(), imageData.begin() + 8);
    // Copy the IHDR chunk (assuming it's before the IDAT chunk)
    size_t ihdrEnd = idatOffset - 4; // -4 for the length bytes of the IDAT chunk
    for (size_t i = 8; i < ihdrEnd; ++i)
        newImageData.push_back(imageData[i]);

    // Write the new IDAT chunk
    unsigned char lengthBytes[4];
    lengthBytes[0] = (recompressedIdatLength >> 24) & 0xFF;
    lengthBytes[1] = (recompressedIdatLength >> 16) & 0xFF;
    lengthBytes[2] = (recompressedIdatLength >> 8) & 0xFF;
    lengthBytes[3] = recompressedIdatLength & 0xFF;
    newImageData.insert(newImageData.end(), lengthBytes, lengthBytes + 4);
    newImageData.insert(newImageData.end(), idatType, idatType + 4);
    newImageData.insert(newImageData.end(), recompressedData.begin(), recompressedData.end());
    unsigned char crcBytes[4];
    crcBytes[0] = (recompressedIdatCrc >> 24) & 0xFF;
    crcBytes[1] = (recompressedIdatCrc >> 16) & 0xFF;
    crcBytes[2] = (recompressedIdatCrc >> 8) & 0xFF;
    crcBytes[3] = recompressedIdatCrc & 0xFF;
    newImageData.insert(newImageData.end(), crcBytes, crcBytes + 4);

    // Copy the IEND chunk (and any other chunks after IDAT)
    size_t iendStart = idatOffset + 8 + idatLength + 4;
    newImageData.insert(newImageData.end(), imageData.begin() + iendStart, imageData.end());

    // Create a new PNG file with the embedded message
    std::string outputFilename = "stego_" + filename;
    std::ofstream outputFile(outputFilename, std::ios::binary);
    if (!outputFile.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not create output file.\033[0m");
    }

    // Write the modified image data to the new file
    outputFile.write(newImageData.data(), newImageData.size());
    outputFile.close();
    std::cout << "Message successfully embedded into " << outputFilename << std::endl;
}
