#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h> // For file information
#include <ctime>   // For timestamp conversion
#include <algorithm> // For std::transform

#include "displayHelp.cpp"
#include "checkFilePermissions.cpp"
#include "printFileInfo.cpp"

// Function to read BMP file header and extract image data offset.
uint32_t readBMPHeader(auto& file, auto& width, auto& height, auto& bitsPerPixel) {
    // BMP Header Structure - same as bitmap - used to store images
    // 2 bytes: "BM" identifier
    // 4 bytes: File size
    // 4 bytes: Reserved (unused)
    // 4 bytes: Data offset (where the pixel data starts)
    // 4 bytes: Header size
    // 4 bytes: Image width
    // 4 bytes: Image height
    // 2 bytes: Number of color planes
    // 2 bytes: Bits per pixel

    file.seekg(0); // Go to the beginning of the file.
    std::cout << "Reading BMP header..." << std::endl;
    char magic[2];
    file.read(magic, 2);
    if (magic[0] != 'B' || magic[1] != 'M') {
        throw std::runtime_error("Not a valid BMP file.");
    }

    uint32_t fileSize;
    file.read(reinterpret_cast<char*>(&fileSize), 4);

    file.seekg(10); //seek to the data offset
    uint32_t dataOffset;
    file.read(reinterpret_cast<char*>(&dataOffset), 4);

    file.seekg(18); //seek to width
    file.read(reinterpret_cast<char*>(&width), 4);

    file.seekg(22); //seek to height
    file.read(reinterpret_cast<char*>(&height), 4);

    file.seekg(28); //seek to bits per pixel
    file.read(reinterpret_cast<char*>(&bitsPerPixel), 2);
    if (bitsPerPixel != 24 && bitsPerPixel != 32) {
        throw std::runtime_error("Only 24 and 32 bits per pixel are supported for BMP.");
    }

    return dataOffset;
}

// Function to get file size
long getFileSize(const std::string& filename) {
    struct stat stat_buf{};
    if (stat(filename.c_str(), &stat_buf) == 0) {
        return stat_buf.st_size;
    }
    return -1; // Error
}

// Function to convert a character to its binary representation (8 bits)
std::string charToBinary(const char c) {
    std::string binary;
    for (int i = 7; i >= 0; --i) {
        binary += ((c >> i) & 1) ? '1' : '0';
    }
    return binary;
}

// Function to write a message into a BMP image
void writeMessageToBMP(const std::string& filename, const std::string& message) {
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary); // Open for reading and writing in binary mode.
    if (!file.is_open()) {
        throw std::runtime_error("Could not open BMP file for writing.");
    }

    uint32_t width, height;
    uint16_t bitsPerPixel;
    uint32_t dataOffset = readBMPHeader(file, width, height, bitsPerPixel);

    long fileSize = getFileSize(filename);
    long messageSize = message.length();
    long availableBits = (fileSize - dataOffset) * 8 / bitsPerPixel;

    if (messageSize > availableBits / 8) {
        throw std::runtime_error("Message is too long to fit in the image.");
    }
    if (messageSize == 0) {
        return; // Do nothing
    }

    std::vector<char> imageData(fileSize - dataOffset);
    file.seekg(dataOffset, std::ios::beg);
    file.read(imageData.data(), imageData.size());

    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    // Add end of message marker (using a unique bit pattern)
    binaryMessage += "0000000000000000"; // 16 zero bits

    // Embed the message
    int bitIndex = 0;
    for (int i = 0; i < imageData.size(); ++i) {
        for (int j = 0; j < bitsPerPixel / 8; ++j) {
            if (bitIndex < binaryMessage.length()) {
                if (binaryMessage[bitIndex] == '1') {
                    imageData[i * (bitsPerPixel / 8) + j] |= 1; // Set LSB to 1
                } else {
                    imageData[i * (bitsPerPixel / 8) + j] &= ~1; // Set LSB to 0
                }
                bitIndex++;
            }
        }
    }

    // Write the modified image data back into the file.
    file.seekp(dataOffset, std::ios::beg); // Seek to the beginning of the dataOffset
    file.write(imageData.data(), imageData.size());

    file.close();
    std::cout << "Message written to BMP file" << std::endl;
}

// Function to read PNG file header and extract image data.
std::vector<char> readPNG(const std::string& filename, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    std::fstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open PNG file.");
    }

    // PNG Header (8 bytes): 89 50 4E 47 0D 0A 1A 0A
    unsigned char header[8];
    file.read(reinterpret_cast<char*>(header), 8);
    if (header[0] != 0x89 || header[1] != 0x50 || header[2] != 0x4E || header[3] != 0x47 ||
        header[4] != 0x0D || header[5] != 0x0A || header[6] != 0x1A || header[7] != 0x0A) {
        throw std::runtime_error("Not a valid PNG file.");
    }

    // Chunk reading loop
    while (true) {
        uint32_t length;
        char type[4];
        file.read(reinterpret_cast<char*>(&length), 4); //length of the chunk data
        //convert from big endian to little endian
        length = __builtin_bswap32(length);
        file.read(type, 4);

        if (std::string(type, 4) == "IHDR") {
            // IHDR chunk: Image header
            file.read(reinterpret_cast<char*>(&width), 4);
            width = __builtin_bswap32(width);
            file.read(reinterpret_cast<char*>(&height), 4);
            height = __builtin_bswap32(height);
            unsigned char bitDepth;
            file.read(reinterpret_cast<char*>(&bitDepth), 1);
            bitsPerPixel = bitDepth;

            unsigned char colorType;
            file.read(reinterpret_cast<char*>(&colorType), 1);
            if (colorType != 2 && colorType != 6) {
                throw std::runtime_error("Unsupported PNG color type.  Must be RGB or RGBA.");
            }
            if (bitsPerPixel != 8) {
                throw std::runtime_error("Unsupported PNG bit depth.  Must be 8.");
            }

            unsigned char compressionMethod, filterMethod, interlaceMethod;
            file.read(reinterpret_cast<char*>(&compressionMethod), 1);
            file.read(reinterpret_cast<char*>(&filterMethod), 1);
            file.read(reinterpret_cast<char*>(&interlaceMethod), 1);
            //std::cout << "Width: " << width << ", Height: " << height << ", Bit Depth: " << (int)bitDepth << ", Color Type: " << (int)colorType << std::endl;
        } else if (std::string(type, 4) == "IDAT") {
            // IDAT chunk: Image data
            std::vector<char> data(length);
            file.read(data.data(), length);
            //std::cout << "IDAT chunk length: " << length << std::endl;
            // Skip CRC (4 bytes)
            file.seekg(4, std::ios::cur);
            return data; // Return the data from the IDAT chunk
        } else if (std::string(type, 4) == "IEND") {
            // IEND chunk: Image end
            break; // End of PNG data
        } else {
            // Skip unknown chunk
            file.seekg(length + 4, std::ios::cur); // Skip data + CRC
        }
    }
    return {};
}

// Function to write a message into a PNG image
void writeMessageToPNG(const std::string& filename, const std::string& message) {
    std::fstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open PNG file for writing.");
    }
    std::cout << "Writing " << message << std::endl;

    uint32_t width, height;
    uint16_t bitsPerPixel;
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);

    long messageSize = message.length();
    long availableBits = imageData.size() * 8 / bitsPerPixel;
    if (messageSize > availableBits / 8) {
        throw std::runtime_error("Message is too long to fit in the image.");
    }
    if (messageSize == 0) {
        return; // Do nothing
    }

    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    // Add end of message marker (using a unique bit pattern)
    binaryMessage += "0000000000000000"; // 16 zero bits
    std::cout << "Writing " << binaryMessage << std::endl;

    // Embed the message
    int bitIndex = 0;
    for (int i = 0; i < imageData.size(); ++i) {
        for (int j = 0; j < bitsPerPixel / 8; ++j) { //iterate through the bytes of each pixel.
            if (bitIndex < binaryMessage.length()) {
                if (binaryMessage[bitIndex] == '1') {
                    imageData[i * (bitsPerPixel / 8) + j] |= 1; // Set LSB to 1
                } else {
                    imageData[i * (bitsPerPixel / 8) + j] &= ~1; // Set LSB to 0
                }
                bitIndex++;
            }
        }
    }

    // Reconstruct the PNG file with the modified IDAT data
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile) {
        throw std::runtime_error("Could not open PNG file for writing.");
    }

    // Write the PNG header
    unsigned char pngHeader[8] = {0x89, 0x50, 0x4E, 0x47, 0x0D, 0x0A, 0x1A, 0x0A};
    outfile.write(reinterpret_cast<char*>(pngHeader), 8);

    // IHDR chunk
    uint32_t ihdrLength = 13;
    char ihdrType[4] = {'I', 'H', 'D', 'R'};
    uint32_t width_big_endian = __builtin_bswap32(width);
    uint32_t height_big_endian = __builtin_bswap32(height);
    unsigned char bitDepth = bitsPerPixel;
    unsigned char colorType = (bitsPerPixel == 24) ? 2 : 6; // 2 for RGB, 6 for RGBA
    unsigned char compressionMethod = 0;
    unsigned char filterMethod = 0;
    unsigned char interlaceMethod = 0;
    uint32_t ihdrCrc = 0; // Placeholder,  CRC calculation is complex, and not required for the exercise.

    outfile.write(reinterpret_cast<char*>(&ihdrLength), 4);
    outfile.write(ihdrType, 4);
    outfile.write(reinterpret_cast<char*>(&width_big_endian), 4);
    outfile.write(reinterpret_cast<char*>(&height_big_endian), 4);
    outfile.write(reinterpret_cast<char*>(&bitDepth), 1);
    outfile.write(reinterpret_cast<char*>(&colorType), 1);
    outfile.write(reinterpret_cast<char*>(&compressionMethod), 1);
    outfile.write(reinterpret_cast<char*>(&filterMethod), 1);
    outfile.write(reinterpret_cast<char*>(&interlaceMethod), 1);
    outfile.write(reinterpret_cast<char*>(&ihdrCrc), 4); //write placeholder crc


    // IDAT chunk
    uint32_t idatLength = imageData.size();
    char idatType[4] = {'I', 'D', 'A', 'T'};
    uint32_t idatCrc = 0; // Placeholder CRC

    idatLength = __builtin_bswap32(idatLength);
    outfile.write(reinterpret_cast<char*>(&idatLength), 4);
    outfile.write(idatType, 4);
    outfile.write(imageData.data(), imageData.size());
    outfile.write(reinterpret_cast<char*>(&idatCrc), 4); // Write placeholder crc

    // IEND chunk
    uint32_t iendLength = 0;
    char iendType[4] = {'I', 'E', 'N', 'D'};
    uint32_t iendCrc = 0;
    outfile.write(reinterpret_cast<char*>(&iendLength), 4);
    outfile.write(iendType, 4);
    outfile.write(reinterpret_cast<char*>(&iendCrc), 4);

    outfile.close();
}

int main(int argc, char* argv[]) {
    // try {
        if (argc == 1) { // print help message
            displayHelp();
            return 0;
        }

        std::string flag = argv[1];
        std::string fileExtension;

    // Handle flags and arguments
    if (flag == "-i" || flag == "--info") {
        if (argc != 3) { // Check for the correct number of arguments
            std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
            displayHelp();
            return 1;
        }
        std::string filename = argv[2];
        fileExtension = filename.substr(filename.find_last_of('.') + 1);
        std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower); //to lower case
        if (fileExtension != "bmp" && fileExtension != "png") {
            std::cerr << "Error: Unsupported file format.  Only .bmp and .png are supported." << std::endl;
            return 1;
        }
        if (!checkFilePermissions(filename, false)) {
            std::cerr << "Error: Cannot read the file or file does not exist." << std::endl;
            return 1;
        }
        const char* file = argv[2];
        printFileInfo(file);
    } else if (flag == "-e" || flag == "--encrypt") {
        if (argc != 4) { // Check for the correct number of arguments
            std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
            displayHelp();
            return 1;
        }
    std::string filename = argv[2];
    std::string message = argv[3];
    fileExtension = filename.substr(filename.find_last_of('.') + 1);
    std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower); //to lower case
    if (fileExtension != "bmp" && fileExtension != "png") {
        std::cerr << "Error: Unsupported file format. Only .bmp and .png are supported." << std::endl;
        return 1;
    }
    if (!checkFilePermissions(filename, true)) {
        std::cerr << "Error: Cannot write to the file or file does not exist." << std::endl;
        return 1;
    }
    if (fileExtension == "bmp") {
        writeMessageToBMP(filename, message);
    } else if (fileExtension == "png") {
        writeMessageToPNG(filename, message);
    }
    std::cout << "Message successfully written to " << filename << std::endl;
    } // else if (flag == "-d" || flag == "--decrypt") {
    //         if (argc != 4) { // Check for the correct number of arguments
    //             std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
    //             displayHelp();
    //             return 1;
    //         }
    //         std::string filename = argv[2];
    //         fileExtension = filename.substr(filename.find_last_of(".") + 1);
    //         std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
    //         if (fileExtension != "bmp" && fileExtension != "png") {
    //             std::cerr << "Error: Unsupported file format.  Only .bmp and .png are supported." << std::endl;
    //             return 1;
    //         }
    //          if (!checkFilePermissions(filename, false)) {
    //             std::cerr << "Error: Cannot read the file or file does not exist." << std::endl;
    //             return 1;
    //         }
    //         std::string message;
    //         if (fileExtension == "bmp") {
    //             message = readMessageFromBMP(filename);
    //         } else if (fileExtension == "png") {
    //             message = readMessageFromPNG(filename);
    //         }
    //         std::cout << "Decrypted message: " << message << std::endl;
    //     } else if (flag == "-c" || flag == "--check") {
    //         if (argc != 4) { // Check for the correct number of arguments
    //             std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
    //             displayHelp();
    //             return 1;
    //         }
    //         std::string filename = argv[2];
    //         std::string message = argv[3];
    //         fileExtension = filename.substr(filename.find_last_of(".") + 1);
    //         std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
    //         if (fileExtension != "bmp" && fileExtension != "png") {
    //             std::cerr << "Error: Unsupported file format. Only .bmp and .png are supported." << std::endl;
    //             return 1;
    //         }
    //         if (!checkFilePermissions(filename, false)) {
    //             std::cerr << "Error: Cannot read the file or file does not exist." << std::endl;
    //             return 1;
    //         }
    //         bool canWrite = canWriteMessage(filename, message);
    //         if (canWrite) {
    //             std::cout << "The message can be written to the image." << std::endl;
    //         } else {
    //             std::cout << "The message cannot be written to the image." << std::endl;
    //         }
    //     } else if (flag == "-h" || flag == "--help") {
    //         displayHelp();
    //     } else {
    //         std::cerr << "Error: Invalid flag: " << flag << std::endl;
    //         displayHelp();
    //         return 1;
    //     }
    // } catch (const std::exception& e) {
    //     std::cerr << "An error occurred: " << e.what() << std::endl;
    //     return 1;
    // }

    return 0;
}

