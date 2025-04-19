#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h> // For file information
#include <ctime>   // For timestamp conversion
#include <algorithm> // For std::transform

// Function to convert a binary string (8 bits) to a character
char binaryToChar(const std::string& binary) {
    if (binary.length() != 8) {
        throw std::runtime_error("Binary string must be 8 bits long");
    }
    char c = 0;
    for (int i = 0; i < 8; ++i) {
        if (binary[i] == '1') {
            c |= (1 << (7 - i));
        }
    }
    return c;
}

// Function to get last modification time
std::string getLastModifiedTime(const std::string& filename) {
    struct stat stat_buf;
    if (stat(filename.c_str(), &stat_buf) == 0) {
        std::time_t t = stat_buf.st_mtime;
        std::string time_str = std::ctime(&t);
        // Remove the trailing newline character
        time_str.erase(time_str.find_last_not_of("\n") + 1);
        return time_str;
    }
    return "Error";
}


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

// Function to read a message from a PNG image
std::string readMessageFromPNG(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open PNG file for reading.");
    }
     uint32_t width, height;
    uint16_t bitsPerPixel;
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);


    std::string binaryMessage = "";
    for (int i = 0; i < imageData.size(); ++i) {
        for(int j = 0; j < bitsPerPixel / 8; ++j){
             binaryMessage += (imageData[i * (bitsPerPixel/8) + j] & 1) ? '1' : '0';
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

// Function to check if a message can be written to an image
bool canWriteMessage(const std::string& filename, const std::string& message) {
    long fileSize = getFileSize(filename);
    if (fileSize == -1) {
        throw std::runtime_error("Could not get file size.");
    }

    std::string fileExtension = filename.substr(filename.find_last_of(".") + 1);
    std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case

     if (fileExtension == "bmp") {
        std::ifstream file(filename, std::ios::binary);
        uint32_t width, height;
        uint16_t bitsPerPixel;
        uint32_t dataOffset = readBMPHeader(file, width, height, bitsPerPixel);
        file.close();
        long availableBits = (fileSize - dataOffset) * 8 / bitsPerPixel;
        long messageBits = (message.length() + 2) * 8; // +2 for the two null terminators.
        return messageBits <= availableBits;
    } else if (fileExtension == "png") {
         uint32_t width, height;
        uint16_t bitsPerPixel;
        std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);
        long availableBits = imageData.size() * 8 / bitsPerPixel;
        long messageBits = (message.length() + 2) * 8;
        return messageBits <= availableBits;
    }
    else {
        throw std::runtime_error("Unsupported file format.");
    }
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

