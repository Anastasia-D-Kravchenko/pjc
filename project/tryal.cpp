#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h> // For file information
#include <ctime>   // For timestamp conversion
#include <algorithm> // For std::transform


// Function to read a message from a BMP image
std::string readMessageFromBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open BMP file for reading.");
    }

    uint32_t width, height;
    uint16_t bitsPerPixel;
    uint32_t dataOffset = readBMPHeader(file, width, height, bitsPerPixel);

    long fileSize = getFileSize(filename);
    if (fileSize == -1) {
         throw std::runtime_error("Could not get file size.");
    }
    std::vector<char> imageData(fileSize - dataOffset);
    file.seekg(dataOffset);
    file.read(imageData.data(), imageData.size());
    file.close();

    std::string binaryMessage = "";
    for (int i = 0; i < imageData.size(); ++i) {
         for(int j = 0; j < bitsPerPixel / 8; ++j){
            binaryMessage += (imageData[i * (bitsPerPixel/8) + j] & 1) ? '1' : '0'; //get the LSB
         }
    }

    std::string message = "";
    for (size_t i = 0; i < binaryMessage.length(); i += 8) {
        if (i + 8 > binaryMessage.length()) {
            break; //prevent reading past the end
        }
        std::string byte = binaryMessage.substr(i, 8);
        if (byte == "00000000")
        {
            if(i+8 < binaryMessage.length() && binaryMessage.substr(i+8,8) == "00000000")
                break; // End of message marker found
            else
                message += binaryToChar(byte);
        }
        else
            message += binaryToChar(byte);
    }
    return message;
}

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            displayHelp();
            return 0;
        }

        std::string flag = argv[1];
        std::string fileExtension;

        // Handle flags and arguments
        if (flag == "-i" || flag == "--info") {
            if (argc != 4) { // Check for the correct number of arguments
                std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            fileExtension = filename.substr(filename.find_last_of(".") + 1);
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
            if (fileExtension != "bmp" && fileExtension != "png") {
                std::cerr << "Error: Unsupported file format.  Only .bmp and .png are supported." << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, false)) {
                std::cerr << "Error: Cannot read the file or file does not exist." << std::endl;
                return 1;
            }
            displayFileInfo(filename);
        } else if (flag == "-e" || flag == "--encrypt") {
                if (argc != 4) { // Check for the correct number of arguments
                    std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
                    displayHelp();
                    return 1;
                }
            std::string filename = argv[2];
            std::string message = argv[3];
            fileExtension = filename.substr(filename.find_last_of(".") + 1);
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
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
        } else if (flag == "-d" || flag == "--decrypt") {
            if (argc != 4) { // Check for the correct number of arguments
                std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            fileExtension = filename.substr(filename.find_last_of(".") + 1);
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
            if (fileExtension != "bmp" && fileExtension != "png") {
                std::cerr << "Error: Unsupported file format.  Only .bmp and .png are supported." << std::endl;
                return 1;
            }
             if (!checkFilePermissions(filename, false)) {
                std::cerr << "Error: Cannot read the file or file does not exist." << std::endl;
                return 1;
            }
            std::string message;
            if (fileExtension == "bmp") {
                message = readMessageFromBMP(filename);
            } else if (fileExtension == "png") {
                message = readMessageFromPNG(filename);
            }
            std::cout << "Decrypted message: " << message << std::endl;
        } else if (flag == "-c" || flag == "--check") {
            if (argc != 4) { // Check for the correct number of arguments
                std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            std::string message = argv[3];
            fileExtension = filename.substr(filename.find_last_of(".") + 1);
            std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
            if (fileExtension != "bmp" && fileExtension != "png") {
                std::cerr << "Error: Unsupported file format. Only .bmp and .png are supported." << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, false)) {
                std::cerr << "Error: Cannot read the file or file does not exist." << std::endl;
                return 1;
            }
            bool canWrite = canWriteMessage(filename, message);
            if (canWrite) {
                std::cout << "The message can be written to the image." << std::endl;
            } else {
                std::cout << "The message cannot be written to the image." << std::endl;
            }
        } else if (flag == "-h" || flag == "--help") {
            displayHelp();
        } else {
            std::cerr << "Error: Invalid flag: " << flag << std::endl;
            displayHelp();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

//
//
// #include <iostream>
// #include <fstream>
// #include <vector>
// #include <iomanip>
//
// int main() {
//     const std::string filename = "palac.png";
//     std::ifstream file(filename, std::ios::binary);
//
//     if (!file.is_open()) {
//         std::cerr << "ERROR: Could not open file: " << filename << std::endl;
//         return 1;
//     }
//
//     // PNG Signature
//     unsigned char pngSignature[8];
//     file.read(reinterpret_cast<char*>(pngSignature), 8);
//
//     std::cout << "PNG Signature: ";
//     for (int i = 0; i < 8; ++i) {
//         std::cout << std::hex << std::uppercase << static_cast<int>(pngSignature[i]) << " ";
//     }
//     std::cout << std::dec << std::endl;
//
//     // IHDR Chunk
//     uint32_t ihdrLength;
//     char ihdrType[4];
//     file.read(reinterpret_cast<char*>(&ihdrLength), 4);
//     file.read(ihdrType, 4);
//
//     uint32_t width;
//     uint32_t height;
//     unsigned char bitDepth;
//     unsigned char colorType;
//     unsigned char compressionMethod;
//     unsigned char filterMethod;
//     unsigned char interlaceMethod;
//
//     file.read(reinterpret_cast<char*>(&width), 4);
//     file.read(reinterpret_cast<char*>(&height), 4);
//     file.read(reinterpret_cast<char*>(&bitDepth), 1);
//     file.read(reinterpret_cast<char*>(&colorType), 1);
//     file.read(reinterpret_cast<char*>(&compressionMethod), 1);
//     file.read(reinterpret_cast<char*>(&filterMethod), 1);
//     file.read(reinterpret_cast<char*>(&interlaceMethod), 1);
//
//     std::cout << "IHDR Length: " << ihdrLength << std::endl;
//     std::cout << "IHDR Type: " << std::string(ihdrType, 4) << std::endl;
//     std::cout << "Width: " << width << std::endl;
//     std::cout << "Height: " << height << std::endl;
//     std::cout << "Bit Depth: " << static_cast<int>(bitDepth) << std::endl;
//     std::cout << "Color Type: " << static_cast<int>(colorType) << std::endl;
//     std::cout << "Compression Method: " << static_cast<int>(compressionMethod) << std::endl;
//     std::cout << "Filter Method: " << static_cast<int>(filterMethod) << std::endl;
//     std::cout << "Interlace Method: " << static_cast<int>(interlaceMethod) << std::endl;
//
//     return 0;
// }
