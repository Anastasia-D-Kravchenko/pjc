/*  How to use:
 * g++ -std=c++20 -o steganography main.cpp
 * ./steganography -i images/ppm/lynx.ppm --- or --- ./steganography -i images/bmp/dots.bmp
 * ./steganography -e images/ppm/lynx.ppm "Okay, let's write something connected with PPM"  --- or --- ./steganography -e images/bmp/dots.bmp "Okay, let's write something connected with BMP"
 * ./steganography -d images/ppm/ref_lynx.ppm --- or --- ./steganography -d images/bmp/ref_dots.bmp
 * ./steganography -c images/ppm/lynx.ppm "Checking"  --- or --- ./steganography -c images/bmp/dots.bmp "Checking"
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

#include "additional/trim.cpp"
#include "additional/charToBinary.cpp"
#include "additional/binaryToChar.cpp"
#include "additional/displayHelp.cpp"
#include "additional/checkFilePermissions.cpp"
#include "FileInfo/printFileInfo.cpp"
#include "PPM/writeMessageToPPM.cpp"
#include "PPM/readMessageFromPPM.cpp"
#include "canWriteMessage.cpp"
#include "PPM/processPPM.cpp"
#include "BMP/processBMP.cpp"
#include "BMP/readMessageFromBMP.cpp"
#include "BMP/writeMessageToBMP.cpp"
// #include ".cpp"

// https://gist.github.com/vratiu/9780109
int main(int argc, char* argv[]) { // count, vector
    try {
        if (argc == 1) {
            displayHelp();
            return 0;
        }

        std::string flag = argv[1]; // -i -e -d ... could be word
        std::string fileExtension; // ONLY bmp, ppm

        if (flag == "-i" || flag == "--info") { // ---------------------------------------------------------------------
            if (argc != 3) {
                std::cerr << "\033[31mError: Incorrect number of arguments for the given flag.\033[0m" << std::endl;
                displayHelp();
                return 1;
            }
            std::string filename = argv[2];
            fileExtension = filename.substr(filename.find_last_of('.') + 1); // .bmp, .ppm
            std::ranges::transform(fileExtension, fileExtension.begin(), ::tolower); // bMp bMP Bmp BmP...
            if (fileExtension != "bmp" && fileExtension != "ppm") {
                std::cerr << "\033[31mError: Unsupported file format.  Only .bmp and .ppm are supported.\033[0m" << std::endl;
                return 1;
            }
            if (!checkFilePermissions(filename, false)) {
                std::cerr << "\033[31mError: CANNOT read the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            const char* file = argv[2];
            printFileInfo(file);
            if (fileExtension == "ppm") {
                processPPM(argv[2]);
            } else if (fileExtension == "bmp") {
                processBMP(argv[2]);
            }
        } else if (flag == "-e" || flag == "--encrypt") { // -----------------------------------------------------------
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
                std::cerr << "\033[31mError: CANNOT write to the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            if (fileExtension == "bmp") {
                writeMessageToBMP(filename, message, 0, 0, 0);
            } else if (fileExtension == "ppm") {
                writeMessageToPPM(filename, message, 0, 0, 0);
            }
            std::cout << "\033[32mMessage successfully written to " << "ref_" + filename << "\033[0m" << std::endl;
        } else if (flag == "-d" || flag == "--decrypt") { // -----------------------------------------------------------
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
                std::cerr << "\033[31mError: CANNOT read the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            std::string message;
            if (fileExtension == "bmp") {
                message = readMessageFromBMP(filename);
            } else if (fileExtension == "ppm") {
                message = readMessageFromPPM(filename);
            }
            std::cout << "\033[32mDecrypted message: \033[0m" << message << std::endl;
        } else if (flag == "-c" || flag == "--check") { // -------------------------------------------------------------
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
                std::cerr << "\033[31mError: CANNOT read the file or file does not exist.\033[0m" << std::endl;
                return 1;
            }
            bool canWrite = canWriteMessage(filename, message);
            if (canWrite) {
                std::cout << "\033[32mThe message can be written to the image.\033[0m" << std::endl;
            } else {
                std::cout << "\033[31mThe message CANNOT be written to the image.\033[0m" << std::endl;
            }
        } else if (flag == "-h" || flag == "--help") { // --------------------------------------------------------------
            displayHelp();
        } else { // ----------------------------------------------------------------------------------------------------
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