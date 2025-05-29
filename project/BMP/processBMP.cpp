// Function to read and print BMP header information
// http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html
void processBMP(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "\033[31mError: Could not open file: " << filename << "\033[0m" << std::endl;
        return;
    }

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

    unsigned char bmpSignature[2];  // 2 bytes: "BM" identifier
    uint32_t fileSize;      // 4 bytes: File size
    uint32_t reserved;      // 4 bytes: Reserved (unused)
    uint32_t dataOffset;    // 4 bytes: Data offset (where the pixel data starts)
    uint32_t headerSize;    // 4 bytes: Header size
    uint32_t width;         // 4 bytes: Image width
    uint32_t height;        // 4 bytes: Image height
    uint16_t colorPlanes;   // 2 bytes: Number of color planes
    uint16_t bitsPerPixel;  // 2 bytes: Bits per pixel

    auto num = sizeof(unsigned int); // 4 bytes

    file.read(reinterpret_cast<char*>(bmpSignature), 2);
    file.read(reinterpret_cast<char*>(&fileSize), num);
    file.read(reinterpret_cast<char*>(&reserved), num);
    file.read(reinterpret_cast<char*>(&dataOffset), num);
    file.read(reinterpret_cast<char*>(&headerSize), num);
    file.read(reinterpret_cast<char*>(&width), num);
    file.read(reinterpret_cast<char*>(&height), num);
    file.read(reinterpret_cast<char*>(&colorPlanes), 2);
    file.read(reinterpret_cast<char*>(&bitsPerPixel), 2);

    // Print the BMP header information
    std::cout << "\033[35mBMP Signature:\033[0m " << bmpSignature[0] << bmpSignature[1] << '\n';
    std::cout << "File Size: " << fileSize << '\n';
    std::cout << "Reserved: " << reserved << '\n';
    std::cout << "Data Offset: " << dataOffset << '\n';
    std::cout << "Header Size: " << headerSize << '\n';
    std::cout << "Width: " << width << '\n';
    std::cout << "Height: " << height << '\n';
    std::cout << "Color Planes: " << colorPlanes << '\n';
    std::cout << "Bits per Pixel: " << bitsPerPixel << '\n';
    file.close();
}