// Function to read BMP file header and extract image data.
// http://www.ue.eti.pg.gda.pl/fpgalab/zadania.spartan3/zad_vga_struktura_pliku_bmp_en.html

// BMP Header:
//  - Signature: The first 2 bytes of the file.  For a standard BMP, this is "BM".
//  - File Size:  A 4-byte value indicating the total size of the BMP file.
//  - Reserved:  A 4-byte value reserved for future use (usually 0).
//  - Data Offset: A 4-byte value indicating the starting address of the pixel data.
// Example: [BMP Header] (14 bytes) | [DIB Header] (40 bytes) | [Color Palette] (if present) | [Data Offset = 54] |

// DIB Header (following the BMP Header):
//  - Header Size: A 4-byte value indicating the size of the DIB header.  Commonly 40 (for BITMAPINFOHEADER).
//  - Image Width: A 4-byte value specifying the width of the image in pixels.
//  - Image Height: A 4-byte value specifying the height of the image in pixels.
//  - Planes:  A 2-byte value, typically 1.
//  - Bits Per Pixel: A 2-byte value specifying the number of bits per pixel (e.g., 8, 24, 32).
//  - Compression: A 4-byte value specifying the compression method used (0 for none).
//  - Image Size: A 4-byte value specifying the size of the image data in bytes.  Can be 0 if no compression.
//  - X Pixels Per Meter: A 4-byte value for horizontal resolution.
//  - Y Pixels Per Meter: A 4-byte value for vertical resolution.
//  - Colors Used: A 4-byte value indicating the number of colors in the color palette (0 for all).
//  - Important Colors: A 4-byte value indicating the number of important colors (0 for all).

uint32_t readBMPHeader(const std::string& filename, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary); // std::ios::binary — open the file as binary;
    if (!file.is_open()) {throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");}

    // BMP Header
    unsigned char bmpSignature[2];
    uint32_t fileSize;
    uint32_t dataOffset;

    file.read(reinterpret_cast<char*>(bmpSignature), 2);
    if (bmpSignature[0] != 'B' || bmpSignature[1] != 'M') throw std::runtime_error("\033[31mERROR: Not a valid BMP file.\033[0m");
    file.read(reinterpret_cast<char*>(&fileSize), 4); // For pointer conversion.
    file.seekg(10, std::ios::beg); // Skip reserved. Where to go, start position. file.seekg(4, std::ios::cur);
    file.read(reinterpret_cast<char*>(&dataOffset), 4);

    // DIB Header
    uint32_t dibHeaderSize;

    file.read(reinterpret_cast<char*>(&dibHeaderSize), 4);
    // if (dibHeaderSize == dibHeaderSize) { //info header
        file.read(reinterpret_cast<char*>(&width), 4);
        file.read(reinterpret_cast<char*>(&height), 4);
        file.seekg(2, std::ios::cur); // Skip Planes
        file.read(reinterpret_cast<char*>(&bitsPerPixel), 2);
        // ... no need in further intel.
    // }
    // else throw std::runtime_error("\033[31mERROR: Unsupported DIB Header Size.\033[0m");
    std::string yes;
    std::cout << "\033[31mERROR: Unsupported bits per pixel. Image can be embedded with text, but it may change the image itself.\033[0m Want to continue?(Y/n)" << std::endl;
    std::cin >> yes;
    if (!(yes == "Y" or yes == "y")) if (bitsPerPixel != 8 && bitsPerPixel != 24 && bitsPerPixel != 32) throw std::runtime_error("\033[31mERROR: Unsupported bits per pixel.\033[0m");
    return dataOffset;
}