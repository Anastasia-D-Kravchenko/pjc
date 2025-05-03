/*  how to use:
 * g++ -std=c++20 -o steganography main.cpp
 * ./steganography -i lynx.ppm --- or --- ./steganography -i dots.bmp
 * ./steganography -e lynx.ppm "Okay, let's write something connected with PPM"  --- or --- ./steganography -e dots.bmp "Okay, let's write something connected with BMP"
 * ./steganography -d lynx.ppm --- or --- ./steganography -d dots.bmp
 * ./steganography -c lynx.ppm "Checking"  --- or --- ./steganography -c dots.bmp "Checking"
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
#include "writeMessageToPPM.cpp"
#include "readMessageFromPPM.cpp"
#include "canWriteMessage.cpp"
#include "processPPM.cpp"
#include "processBMP.cpp"
#include "readMessageFromBMP.cpp"
#include "writeMessageToBMP.cpp"
// #include ".cpp"

// https://gist.github.com/vratiu/9780109
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
                std::cerr << "\033[31mError: Incorrect number of arguments for the given flag.\033[0m" << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            fileExtension = filename.substr(filename.find_last_of('.') + 1);
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower);
            if (fileExtension != "bmp" && fileExtension != "ppm") {
                std::cerr << "\033[31mError: Unsupported file format.  Only .bmp and .ppm are supported.\033[0m" << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, false)) {
                std::cerr << "\033[31mError: Cannot read the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            const char* file = argv[2];
            printFileInfo(file);
            if (fileExtension == "ppm") {
                processPPM(argv[2]);
            } else if (fileExtension == "bmp") {
                processBMP(argv[2]);
            } else {
                std::cerr << "\033[31mError: Unsupported image type: " << fileExtension << "\033[0m" << std::endl;
                return 1;
            }
        } else if (flag == "-e" || flag == "--encrypt") {
            if (argc != 4) {
                std::cerr << "\033[31mError: Incorrect number of arguments for the given flag.\033[0m" << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            std::string message = argv[3];
            fileExtension = filename.substr(filename.find_last_of('.') + 1);
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower);
            if (fileExtension != "bmp" && fileExtension != "ppm") {
                std::cerr << "\033[31mError: Unsupported file format. Only .bmp and .ppm are supported.\033[0m" << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, true)) {
                std::cerr << "\033[31mError: Cannot write to the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            if (fileExtension == "bmp") {
                writeMessageToBMP(filename, message, 0, 0, 0);
            } else if (fileExtension == "ppm") {
                writeMessageToPPM(filename, message);
            }
            std::cout << "\033[32mMessage successfully written to " << filename << "\033[0m" << std::endl;
        } else if (flag == "-d" || flag == "--decrypt") {
            if (argc != 3) {
                std::cerr << "\033[31mError: Incorrect number of arguments for the given flag.\033[0m" << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            fileExtension = filename.substr(filename.find_last_of('.') + 1);
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower); //to lower case
            if (fileExtension != "bmp" && fileExtension != "ppm") {
                std::cerr << "\033[31mError: Unsupported file format.  Only .bmp and .ppm are supported.\033[0m" << std::endl;
                return 1;
            }
             if (!checkFilePermissions(filename, false)) {
                std::cerr << "\033[31mError: Cannot read the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            std::string message;
            if (fileExtension == "bmp") {
                message = readMessageFromBMP(filename);
            } else if (fileExtension == "ppm") {
                message = readMessageFromPPM(filename);
            }
            std::cout << "Decrypted message: " << message << std::endl;
        } else if (flag == "-c" || flag == "--check") {
            if (argc != 4) {
                std::cerr << "\033[31mError: Incorrect number of arguments for the given flag.\033[0m" << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            std::string message = argv[3];
            fileExtension = filename.substr(filename.find_last_of('.') + 1);
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower); //to lower case
            if (fileExtension != "bmp" && fileExtension != "ppm") {
                std::cerr << "\033[31mError: Unsupported file format. Only .bmp and .ppm are supported.\033[0m" << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, false)) {
                std::cerr << "\033[31mError: Cannot read the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            bool canWrite = canWriteMessage(filename, message);
            if (canWrite) {
                std::cout << "The message can be written to the image." << std::endl;
            } else {
                std::cout << "\033[31mThe message cannot be written to the image.\033[0m" << std::endl;
            }
        } else if (flag == "-h" || flag == "--help") {
            displayHelp();
        } else {
            std::cerr << "\033[31mError: Invalid flag: " << flag << "\033[0m" << std::endl;
            displayHelp();
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[31mAn error occurred: " << e.what() << "\033[0m" << std::endl;
        return 1;
    }

    return 0;
}