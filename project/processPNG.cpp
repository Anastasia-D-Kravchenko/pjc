// Function to read and print PNG header information
// http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html
void processPNG(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "\033[31mError: Could not open file: " << filename << "\033[0m" << std::endl;
        return;
    }

    // PNG Signature
    unsigned char pngSignature[8]; // Array to store the 8-byte PNG signature
    file.read(reinterpret_cast<char*>(pngSignature), 8); // Read the first 8 bytes of the file into pngSignature
    // IHDR Chunk
    uint32_t IHDR_LENGTH; // Variable to store the length of the IHDR chunk data
    char CHUNK_TYPE[4];   // Array to store the 4-byte chunk type identifier
    uint32_t w, h;                 // Variables to store the width and height of the image
    unsigned char bitdepth;         // Variable to store the bit depth
    unsigned char colordepth;       // Variable to store the color type
    unsigned char compression_method; // Variable to store the compression method
    unsigned char filter_method;      // Variable to store the filter method
    unsigned char interlacce_method;  // Variable to store the interlace method

    auto num = sizeof(unsigned int);

    // Read the length of the IHDR chunk (first 4 bytes after the signature)
    file.read(reinterpret_cast<char*>(&IHDR_LENGTH), num);
    // Read the chunk type (next 4 bytes), which should be "IHDR"
    file.read(&CHUNK_TYPE[0], sizeof(char) * 4);
    // Read the image width (next 4 bytes)
    file.read(reinterpret_cast<char*>(&w), num);
    // Read the image height (next 4 bytes)
    file.read(reinterpret_cast<char*>(&h), num);

    num = sizeof(unsigned char);

    // Read the bit depth (next 1 byte)
    file.read(reinterpret_cast<char*>(&bitdepth), num);
    // Read the color type (next 1 byte)
    file.read(reinterpret_cast<char*>(&colordepth), num);
    // Read the compression method (next 1 byte)
    file.read(reinterpret_cast<char*>(&compression_method), num);
    // Read the filter method (next 1 byte)
    file.read(reinterpret_cast<char*>(&filter_method), num);
    // Read the interlace method (next 1 byte)
    file.read(reinterpret_cast<char*>(&interlacce_method), num);

    std::cout << "\033[35mPNG SIGN : \033[0m";
    for (size_t i = 0; i < 8; ++i) {std::cout << std::hex << std::uppercase << int(pngSignature[i]) << ' ';} // Print each byte in uppercase hexadecimal format, followed by a space
    std::cout << std::dec << '\n'; // Reset output to decimal and print a newline
    std::cout << "IHDR LENGTH = " << IHDR_LENGTH << '\n'; // Print the length of the IHDR chunk data
    std::cout << "CHUNK TYPE  = " << CHUNK_TYPE << " -> ";   // Print the chunk type (should be "IHDR")
    if (std::strncmp(CHUNK_TYPE, "IHDR", 4) == 0) std::cout << "CHUNK TYPE is valid: IHDR\n";
    else std::cerr << "\033[31mCHUNK TYPE is invalid. Expected IHDR. File will be processed, but data might be incorrect.\033[0m\n";
    std::cout << "Width  = " << w << '\n';   // Print the image width
    std::cout << "height = " << h << '\n';  // Print the image height
    std::cout << "bitdepth   = " << int(bitdepth) << '\n';         // Print the bit depth (cast to int for numerical output)
    std::cout << "colordepth = " << int(colordepth) << '\n';       // Print the color type (cast to int for numerical output)
    std::cout << "compression_method = " << int(compression_method) << '\n'; // Print the compression method (cast to int for numerical output)
    std::cout << "filter_method      = " << int(filter_method) << '\n';      // Print the filter method (cast to int for numerical output)
    std::cout << "interlacce_method  = " << int(interlacce_method) << '\n';  // Print the interlace method (cast to int for numerical output)
    file.close();

}