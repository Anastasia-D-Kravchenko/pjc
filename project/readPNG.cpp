// Function to read PNG file header and extract image data.
// http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html
// IHDR (Image Header): Contains essential information about the image, such as its width, height, bit depth, color type,
// compression method, filter method, and interlace method.  This chunk MUST be the first chunk in a PNG file.
// PLTE (Palette): Contains the color palette for indexed-color images.  This chunk is only present for certain color types.
// IDAT (Image Data): Contains the actual compressed image data.  A PNG file can contain multiple IDAT chunks, which are
// concatenated to form the complete image data.

// PNG Signature: The first 8 bytes of the file. This is not a chunk, but a special identifier that marks the file as a PNG file.
// IHDR Chunk:
    // IHDR chunk length (4 bytes)
    // IHDR chunk type (4 bytes, which should be "IHDR")
    // Image width (4 bytes)
    // Image height (4 bytes)
    // Bit depth (1 byte) ---- END
    // Color type (1 byte)
    // Compression method (1 byte)
    // Filter method (1 byte)
    // Interlace method (1 byte)
// Remaining File Data: The code then reads the entire rest of the file into a buffer.  This will include all the remaining
// chunks (IDAT, IEND, and any other ancillary chunks).  However, it reads them as a single block of data, without parsing
// the individual chunks.


std::vector<char> readPNG(const std::string& filename, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    std::ifstream file(filename, std::ios::binary); // std::ios::binary — open the file as binary;
    if (!file.is_open()) {throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");}

    // PNG Signature
    unsigned char pngSignature[8]; // Declare an unsigned char array to hold the PNG signature (8 bytes).
    file.read(reinterpret_cast<char*>(pngSignature), 8); // Read the first 8 bytes from the file into pngSignature.
                                                        // reinterpret_cast is used to treat the unsigned char array as a char array,
                                                        // which is what file.read expects.  This is necessary because file.read
                                                        // works with character arrays.

    // IHDR Chunk -  Image Header Chunk.  This chunk contains c-r-u-c-i-a-l information about the image.
    uint32_t ihdrLength;
    char ihdrType[4];
    file.read(reinterpret_cast<char*>(&ihdrLength), 4); // The length does NOT include the length of the chunk type field.
    file.read(ihdrType, 4);

    // Image dimensions
    file.read(reinterpret_cast<char*>(&width), 4);
    file.read(reinterpret_cast<char*>(&height), 4);

    // Read IHDR data
    unsigned char bitDepth;
    file.read(reinterpret_cast<char*>(&bitDepth), 1);
    bitsPerPixel = bitDepth; //sets the bitsPerPixel
    // std::cout << "Bits per pixel: " << bitsPerPixel << std::endl; // A single pixel can be represented by 8 bits (e.g., grayscale),
                                                                     // 24 bits (e.g., RGB), or some other number of bits.

    // Read the rest of the file and return the data.  This part reads the entire remaining file into a buffer.
    file.seekg(0, std::ios::end);       // Move the file read position to the end of the file.
    auto fileSize = file.tellg(); // Get the current file position (which is now the size of the file).
    file.seekg(0, std::ios::beg);       // Move the file read position back to the beginning of the file.

    std::vector<char> fileData(fileSize); // Create a vector of characters to store the entire file's data.
    file.read(fileData.data(), fileSize);  // Read the entire file's data into the fileData vector.
                                                // fileData.data() is a method of the std::vector that
                                                // returns a pointer to the beginning of the memory
                                                // where the vector's data is stored.
    return fileData;                     // Return the vector containing the file's data.
}