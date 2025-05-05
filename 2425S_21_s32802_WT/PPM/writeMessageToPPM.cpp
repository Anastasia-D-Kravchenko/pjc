#include "readPPM.cpp"
void writeMessageToPPM(const std::string& filename, const std::string& message, uint32_t width, uint32_t height, uint16_t bitsPerPixel) {
    std::vector<char> imageData; // Vector to store the image data
    std::string magicNumber, maxColorValueStr; // Variables to store PPM header information

    try {
        // Read the PPM image data and header information
        imageData = readPPM(filename, width, height, bitsPerPixel, magicNumber, maxColorValueStr);
    } catch (const std::runtime_error& e) {
        throw std::runtime_error("Error reading PPM data: " + std::string(e.what()));
    }

    // Determine image format and calculate available bits for message storage
    int bytesPerPixel = (magicNumber == "P6") ? 3 : 1; // 3 bytes per pixel for P6 (RGB), 1 for P3
    long availableBits = (magicNumber == "P6") ? width * height * bytesPerPixel * 8 : width * height * 8; // Calculate total available bits
    std::cout << "Message size: " << message.length() << ", available " << ((magicNumber == "P6") ? availableBits/(8*8) : availableBits/( 10 * 8)) << std::endl; // Output message size and available bits
    // Check if the message is too long to fit in the image data
    if (message.length() * 8 > ((magicNumber == "P6") ? availableBits/10 : availableBits/8)) { // Changed division for available bits check
        throw std::runtime_error("\033[31mERROR: Message is too long to fit in the image.\033[0m"); // Throw an error if the message is too long
    }
    if (message.empty()) return; // Return if the message is empty
    size_t dataSize = (magicNumber == "P6") ? width * height * 3 : imageData.size();
    if (dataSize == 0)throw std::runtime_error("No data read from the PPM file.");

    // Convert the message to binary
    std::string binaryMessage;
    for (char c : message) {
        binaryMessage += charToBinary(c); // Convert each character to its binary representation
    }
    binaryMessage += "0000000000000000"; //16 zero bits !!! "end-of-message" marker !!!

    // Embed the message into the image data
    uint32_t bitIndex = 0; // Initialize the bit index to track the current bit being processed
    if (magicNumber == "P6") { // Handle P6 (RGB) format
        for (uint32_t i = 0; i < dataSize && bitIndex < binaryMessage.length(); ++i) { // Iterate through each byte of the image data (except the last one)
            for (int j = 0; j < 8 && bitIndex < binaryMessage.length(); ++j) {
                if ( j == 0 ){ // Embed only in the first bit of the byte ( that'll be reversed )
                    if (binaryMessage[bitIndex] == '1') {
                        imageData[i] |= 1;         // Set the least significant bit to 1
                    }
                    else {
                        imageData[i] &= ~1;        // Set the least significant bit to 0
                    }
                    bitIndex++; // Move to the next bit of the message
                }
            }
        }
    } else { // Handle P3 format
        for (uint32_t i = 0; i < dataSize  && bitIndex < binaryMessage.length(); ++i) { // Iterate through the image data
             if (imageData[i] != 32 && imageData[i + 1] == 32){ //check for space
                if (binaryMessage[bitIndex] == '1'){
                    imageData[i] |= 1;
                }
                else{
                    imageData[i] &= ~1;
                }
                bitIndex++;
            }
        }
    }

    size_t lastSlash = filename.find_last_of('/');
    size_t startPos = (lastSlash == std::string::npos) ? 0 : lastSlash + 1;
    std::string fileName = filename.substr(startPos);
    // Write the modified image data back to the PPM file
    std::ofstream outfile("changedImages/ppm/ref_"+fileName); // Open the output file (prefixed with "ref_")

    if (!outfile) {
        throw std::runtime_error("\033[31mERROR: Could not open PPM file for writing.\033[0m"); // Throw an error if the file cannot be opened
    }
    // Write the PPM header to the output file
    outfile << magicNumber << std::endl;              // Write the magic number (P6 or P3)
    outfile << width << " " << height << std::endl;             // Write the width and height
    outfile << maxColorValueStr << std::endl;    // Write the maximum color value
    if (magicNumber == "P6") { // Write pixel data for P6 format
        outfile.write(reinterpret_cast<const char*>(imageData.data()), imageData.size()); // Write the entire image data
    } else { // Write pixel data for P3 format
        for (int i = 0; i < imageData.size(); ++i) {
            outfile << imageData[i];
        }
    }
    outfile.close(); // Close the output file
}