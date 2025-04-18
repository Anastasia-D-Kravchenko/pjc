#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <sys/stat.h> // For file information
#include <ctime>   // For timestamp conversion
#include <algorithm> // For std::transform

// Function to convert a character to its binary representation (8 bits)
std::string charToBinary(const char c) {
    std::string binary;
    for (int i = 7; i >= 0; --i) {
        binary += ((c >> i) & 1) ? '1' : '0';
    }
    return binary;
}

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

// Function to read BMP file header and extract image data offset.
uint32_t readBMPHeader(std::ifstream& file, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    // BMP Header Structure (simplified for this project)
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



// Function to read PNG file header and extract image data.
std::vector<char> readPNG(const std::string& filename, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
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
            if (bitsPerPixel != 8)
            {
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



// Function to write a message into a BMP image
void writeMessageToBMP(const std::string& filename, const std::string& message) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open BMP file for writing.");
    }

    uint32_t width, height;
    uint16_t bitsPerPixel;
    uint32_t dataOffset = readBMPHeader(file, width, height, bitsPerPixel);


    long fileSize = getFileSize(filename);
    long messageSize = message.length();
    long availableBits = (fileSize - dataOffset) * 8 / bitsPerPixel; //number of available bytes * 8, divide by bits per pixel.

    if (messageSize > availableBits / 8 ) {
        throw std::runtime_error("Message is too long to fit in the image.");
    }
     if (messageSize == 0)
    {
        return; //do nothing
    }

    std::vector<char> imageData(fileSize - dataOffset);
    file.seekg(dataOffset);
    file.read(imageData.data(), imageData.size());
    file.close();

    std::string binaryMessage = "";
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    // Add end of message marker (using a unique bit pattern)
    binaryMessage += "0000000000000000"; //16 zero bits

    // Embed the message
    int bitIndex = 0;
    for (int i = 0; i < imageData.size(); ++i) {
        for(int j = 0; j < bitsPerPixel / 8; ++j){ //iterate through the bytes of each pixel.
            if (bitIndex < binaryMessage.length()) {
                if (binaryMessage[bitIndex] == '1') {
                    imageData[i * (bitsPerPixel/8) + j] |= 1; // Set LSB to 1
                } else {
                    imageData[i * (bitsPerPixel/8) + j] &= ~1; // Set LSB to 0
                }
                bitIndex++;
            }
        }
    }
    std::ofstream outfile(filename, std::ios::binary);
    if(!outfile){
        throw std::runtime_error("Could not open file for writing.");
    }
    //write the header
    file.seekg(0);
    outfile << file.rdbuf();
    // Write the modified image data
    outfile.seekp(dataOffset);
    outfile.write(imageData.data(), imageData.size());
    outfile.close();
}

// Function to write a message into a PNG image
void writeMessageToPNG(const std::string& filename, const std::string& message) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Could not open PNG file for writing.");
    }

    uint32_t width, height;
    uint16_t bitsPerPixel;
    std::vector<char> imageData = readPNG(filename, width, height, bitsPerPixel);

    long messageSize = message.length();
    long availableBits = imageData.size() * 8 / bitsPerPixel;
     if (messageSize > availableBits / 8 ) {
        throw std::runtime_error("Message is too long to fit in the image.");
    }
      if (messageSize == 0)
    {
        return; //do nothing
    }

    std::string binaryMessage = "";
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    // Add end of message marker (using a unique bit pattern)
    binaryMessage += "0000000000000000"; //16 zero bits

    // Embed the message
    int bitIndex = 0;
    for (int i = 0; i < imageData.size(); ++i) {
       for(int j = 0; j < bitsPerPixel / 8; ++j){ //iterate through the bytes of each pixel.
            if (bitIndex < binaryMessage.length()) {
                if (binaryMessage[bitIndex] == '1') {
                    imageData[i * (bitsPerPixel/8) + j] |= 1; // Set LSB to 1
                } else {
                    imageData[i * (bitsPerPixel/8) + j] &= ~1; // Set LSB to 0
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

// Function to display help information
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

