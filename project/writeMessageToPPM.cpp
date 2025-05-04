#include "readPPM.cpp"
#include "charToBinary.cpp"
void writeMessageToPPM(const std::string& filename, const std::string& message) {
    uint32_t width, height;
    uint16_t bitsPerPixel;
    std::vector<char> imageData;
    std::string magicNumber;
    int maxColorValue;

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }
    std::string widthStr, heightStr, maxColorValueStr;

    // Read the PPM header.
    std::getline(file, magicNumber);
    magicNumber = trim(magicNumber);
    // Check for the P3 magic number
    if (magicNumber != "P3" && magicNumber != "P6") {
        throw std::runtime_error("\033[31mERROR: Invalid PPM format. Only P3 and P6 are supported.\033[0m");
    }
    file >> width >> height >> maxColorValueStr;
    file.ignore(); // Consume the newline character after the header.

    imageData = readPPM(filename, width, height, bitsPerPixel);

    int bytesPerPixel = (magicNumber == "P6") ? 3 : 1;
    long availableBits = (magicNumber == "P6") ? width * height * bytesPerPixel * 8 : width * height * 8;
    std::cout << "Message size: " << message.length() << ", available " << availableBits/(3*8) << std::endl;
    if (message.length() * 8 > availableBits/3) {
        throw std::runtime_error("\033[31mERROR: Message is too long to fit in the image.\033[0m");
    }
    if (message.empty()) return;

    // 3. Convert message to binary
    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += charToBinary(c);
    }
    binaryMessage += "0000000000000000"; // Null terminator

    // 4. Embed the message
    int bitIndex = 0;
    if (magicNumber == "P6") {
        for (size_t i = 0; i < imageData.size() && bitIndex < binaryMessage.length(); ++i) {
            imageData[i] = (imageData[i] & 0xFE) | ((binaryMessage[bitIndex] - '0') & 0x01);
            ++bitIndex;
        }
    } else {
        uint32_t bitIndex = 0;
        for (uint32_t i = 0; i < width * height * 3 - 1 && bitIndex < binaryMessage.length(); ++i){ //changed loop condition
            if (imageData[i] != 32 && imageData[i + 1] == 32){ // Changed comparison value
                if (binaryMessage[bitIndex] == '1'){
                    imageData[i] |= 1; //changed bit shift
                }
                else{
                    imageData[i] &= ~1; //changed bit shift
                }
                bitIndex++;
            }
        }
    }

    // 5. Write the modified image data back to the PPM file
    std::ofstream outfile("ref_"+filename);
    if (!outfile) {
        throw std::runtime_error("\033[31mERROR: Could not open PPM file for writing.\03[0m");
    }
    // Write the PPM header
    outfile << magicNumber << std::endl;
    outfile << std::endl;
    outfile << width << " " << height << std::endl;
    outfile << std::endl;
    outfile << maxColorValueStr << std::endl;
    outfile << std::endl;
    if (magicNumber == "P6") {
        outfile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size());
    } else {
        for (int i = 0; i < imageData.size(); ++i) {
            outfile << imageData[i];
        }
    }
}

