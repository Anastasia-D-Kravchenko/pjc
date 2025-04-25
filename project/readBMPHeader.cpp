void readBMPHeader(std::ifstream& file, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: File is not open.\033[0m");
    }

    // BMP Header
    unsigned char bmpSignature[2];
    file.read(reinterpret_cast<char*>(bmpSignature), 2);
    if (bmpSignature[0] != 'B' || bmpSignature[1] != 'M') {
        throw std::runtime_error("\033[31mERROR: Not a valid BMP file.\033[0m");
    }

    uint32_t fileSize;
    file.read(reinterpret_cast<char*>(&fileSize), 4);
    file.seekg(10, std::ios::beg); // Skip reserved
    uint32_t dataOffset;
    file.read(reinterpret_cast<char*>(&dataOffset), 4);

    // DIB Header
    uint32_t dibHeaderSize;
    file.read(reinterpret_cast<char*>(&dibHeaderSize), 4);

    if (dibHeaderSize == 40) { //info header
        file.read(reinterpret_cast<char*>(&width), 4);
        file.read(reinterpret_cast<char*>(&height), 4);
        file.seekg(2, std::ios::cur); // Skip Planes
        file.read(reinterpret_cast<char*>(&bitsPerPixel), 2);
    }
    else {
        throw std::runtime_error("\033[31mERROR: Unsupported DIB Header Size.\033[0m");
    }
    if (bitsPerPixel != 8 && bitsPerPixel != 24 && bitsPerPixel != 32) {
        throw std::runtime_error("\033[31mERROR: Unsupported bits per pixel.\033[0m");
    }
}