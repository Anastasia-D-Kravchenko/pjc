/*  how to use:
 * g++ -std=c++20 -o steganography main.cpp
 * ./steganography -i palac.png
 * ./steganography -e palac.png "Okay, let's wright something really long"
 * ./steganography -d palac.png
 * ./steganography -c palac.png "Okay, let's wright something really long"
 * ./steganography -h
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h>
#include <ctime>
#include <algorithm>

#include "displayHelp.cpp"
#include "checkFilePermissions.cpp"
#include "printFileInfo.cpp"
#include "writeMessageToPNG.cpp"
#include "readMessageFromPNG.cpp"
#include "canWriteMessage.cpp"
// #include ".cpp"

// Function to read BMP file header and extract image data offset.
// http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
// http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html
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

int main(int argc, char* argv[]) {
    try {
        if (argc == 1) {
            displayHelp();
            return 0;
        }

        std::string flag = argv[1];
        std::string fileExtension;

        if (flag == "-i" || flag == "--info") {
            if (argc != 3) {
                std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            fileExtension = filename.substr(filename.find_last_of('.') + 1);
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower);
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
            if (fileExtension == "png") {
                const std::string filename = argv[2];
                std::ifstream file(filename, std::ios::binary);
                if (!file) {std::cerr << "Error: Could not open file: " << filename << std::endl; return 1; }
                // PNG Signature
                unsigned char pngSignature[8];
                file.read(reinterpret_cast<char*>(pngSignature), 8);

                std::cout << "PNG SIGN : ";
                for (size_t i = 0; i < 8; ++i)
                    std::cout << std::hex << std::uppercase << int(pngSignature[i]) << ' ';
                std::cout << std::dec << '\n';

                // IHDR Chunk
                uint32_t IHDR_LENGTH;
                char CHUNK_TYPE[4];
                file.read(reinterpret_cast<char*>(&IHDR_LENGTH), sizeof(unsigned int));
                file.read(reinterpret_cast<char*>(&CHUNK_TYPE[0]), sizeof(char) * 4);

                uint32_t w, h;
                unsigned char bitdepth;
                unsigned char colordepth;
                unsigned char compression_method;
                unsigned char filter_method;
                unsigned char interlacce_method;

                file.read(reinterpret_cast<char*>(&w), sizeof(unsigned int));
                file.read(reinterpret_cast<char*>(&h), sizeof(unsigned int));
                file.read(reinterpret_cast<char*>(&bitdepth), sizeof(unsigned char));
                file.read(reinterpret_cast<char*>(&colordepth), sizeof(unsigned char));
                file.read(reinterpret_cast<char*>(&compression_method), sizeof(unsigned char));
                file.read(reinterpret_cast<char*>(&filter_method), sizeof(unsigned char));
                file.read(reinterpret_cast<char*>(&interlacce_method), sizeof(unsigned char));

                std::cout << "IHDR LENGTH = " << IHDR_LENGTH << '\n';
                std::cout << "CHUNK TYPE  = " << CHUNK_TYPE << '\n';

                std::cout << "Width  = " << w << '\n';
                std::cout << "height = " << h << '\n';

                std::cout << "bitdepth   = " << int(bitdepth) << '\n';
                std::cout << "colordepth = " << int(colordepth) << '\n';
                std::cout << "compression_method = " << int(compression_method) << '\n';
                std::cout << "filter_method      = " << int(filter_method) << '\n';
                std::cout << "interlacce_method  = " << int(interlacce_method) << '\n';
            }
        } else if (flag == "-e" || flag == "--encrypt") {
            if (argc != 4) {
                std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            std::string message = argv[3];
            fileExtension = filename.substr(filename.find_last_of('.') + 1);
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower);
            if (fileExtension != "bmp" && fileExtension != "png") {
                std::cerr << "Error: Unsupported file format. Only .bmp and .png are supported." << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, true)) {
                std::cerr << "Error: Cannot write to the file or file does not exist." << std::endl;
                return 1;
            }
            if (fileExtension == "bmp") {
                uint32_t width, height;
                uint16_t bitsPerPixel;
                std::ifstream file(filename, std::ios::binary);
                if (!file) {std::cerr << "Error: Could not open file: " << filename << std::endl; return 1; }
                // readBMPHeader(file, width, height, bitsPerPixel);
                // file.close();
                // writeMessageToBMP(filename, message, width, height, bitsPerPixel);
            } else if (fileExtension == "png") {
                //read png metadata
                writeMessageToPNG(filename, message, 0, 0, 0);
            }
            std::cout << "Message successfully written to " << filename << std::endl;
        } else if (flag == "-d" || flag == "--decrypt") {
            if (argc != 3) {
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
            std::string message;
            if (fileExtension == "bmp") {
                // message = readMessageFromBMP(filename);
            } else if (fileExtension == "png") {
                message = readMessageFromPNG(filename);
            }
            std::cout << "Decrypted message: " << message << std::endl;
        } else if (flag == "-c" || flag == "--check") {
            if (argc != 4) {
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

