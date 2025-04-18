#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h> // For file information
#include <ctime>   // For timestamp conversion
#include <algorithm> // For std::transform

void displayHelp() {
    std::cout << "Usage: steganography [flag] [arguments]" << std::endl;
    std::cout << "Supported file extensions: .bmp, .png" << std::endl;
    std::cout << "Flags:" << std::endl;
    std::cout << "  -i, --info <file_path>        : Display information about the image file." << std::endl;
    std::cout << "  -e, --encrypt <file_path> <message>: Encrypt the message into the image file." << std::endl;
    std::cout << "  -d, --decrypt <file_path>        : Decrypt the message from the image file." << std::endl;
    std::cout << "  -c, --check <file_path> <message>  : Check if the message can be written to the image file." << std::endl;
    std::cout << "  -h, --help                   : Display this help information." << std::endl;
    std::cout << "  Running the program without any flags is equivalent to using the -h flag." << std::endl;
}

// Function to check file permissions (read and write)
bool checkFilePermissions(const std::string& filename, bool write_access) {
    std::ifstream file(filename);
    if (!file.good()) {
        return false; // File doesn't exist or cannot be opened
    }
    file.close();

    if (write_access) {
        std::ofstream test_file(filename, std::ios::app); //open in append mode to not overwrite
        if (!test_file.good()) {
            return false; // Cannot write to the file
        }
        test_file.close();
    }
    return true;
}

// Function to get file size
long getFileSize(const std::string& filename) {
    struct stat stat_buf;
    if (stat(filename.c_str(), &stat_buf) == 0) {
        return stat_buf.st_size;
    }
    return -1; // Error
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

// Function to display file information
void displayFileInfo(const std::string& filename) {
    long size = getFileSize(filename);
    std::string lastModified = getLastModifiedTime(filename);

    if (size == -1 || lastModified == "Error") {
        std::cerr << "Error: Could not retrieve file information." << std::endl;
        return;
    }

    std::cout << "File: " << filename << std::endl;
    std::cout << "Size: " << size << " bytes" << std::endl;
    std::cout << "Last modified: " << lastModified << std::endl;
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
    } // else if (flag == "-e" || flag == "--encrypt") {
    //             if (argc != 4) { // Check for the correct number of arguments
    //                 std::cerr << "Error: Incorrect number of arguments for the given flag." << std::endl;
    //                 displayHelp();
    //                 return 1;
    //             }
    //         std::string filename = argv[2];
    //         std::string message = argv[3];
    //         fileExtension = filename.substr(filename.find_last_of(".") + 1);
    //         std::transform(fileExtension.begin(), fileExtension.end(), fileExtension.begin(), ::tolower); //to lower case
    //         if (fileExtension != "bmp" && fileExtension != "png") {
    //             std::cerr << "Error: Unsupported file format. Only .bmp and .png are supported." << std::endl;
    //             return 1;
    //         }
    //         if (!checkFilePermissions(filename, true)) {
    //             std::cerr << "Error: Cannot write to the file or file does not exist." << std::endl;
    //             return 1;
    //         }
    //         if (fileExtension == "bmp") {
    //             writeMessageToBMP(filename, message);
    //         } else if (fileExtension == "png") {
    //             writeMessageToPNG(filename, message);
    //         }
    //         std::cout << "Message successfully written to " << filename << std::endl;
    //     } else if (flag == "-d" || flag == "--decrypt") {
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

