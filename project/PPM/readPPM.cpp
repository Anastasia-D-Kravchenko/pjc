// Function to read PPM file header and extract image data.
// PPM Header:
//  - Magic Number: "P6/P3" (for binary PPM)
//  - Width (ASCII integer)
//  - Height (ASCII integer)
//  - Maximum color value (ASCII integer, e.g., 255)
//  - Newline character after the header
// Image Data:
//  - Raw RGB pixel data, packed as bytes.  Each pixel is 3 bytes (red, green, blue).
// https://faculty.college.emory.edu/sites/weeks/graphics/mkppm.html#:~:text=PPM%20stands%20for%20%22Portable%20Pixel,exact%20color%20of%20each%20pixel.
// https://www.cs.rhodes.edu/~kirlinp/courses/cs1/f19/projects/proj8/
std::vector<char> readPPM(const std::string& filename, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel, std::string& magicNumber, std::string& maxColorValueStr) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");}

    // Read the PPM header
    std::getline(file, magicNumber);       // Read the magic number (P3 or P6) from the first line
    magicNumber = trim(magicNumber);       // Remove leading/trailing whitespace
    if (magicNumber != "P3" && magicNumber != "P6") { throw std::runtime_error("\033[31mERROR: Invalid PPM format. Only P3 and P6 are supported.\033[0m"); }
    file >> width >> height >> maxColorValueStr; // Read width, height, and maxColorValue
    file.ignore();                           // Consume the newline character after the header numbers

    // Convert maxColorValue to integer
    int maxColorValue;
    try { // The stoi() is a standard library function that turns a string into an integer
        maxColorValue = std::stoi(maxColorValueStr); // Convert the maxColorValue string to an integer
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
        throw std::runtime_error("\033[31mERROR: Invalid max color value in PPM header.\033[0m");
    }

    if (maxColorValue != 255) { // Warn the user if maxColorValue is not 255 (common, but not always handled)
        std::cerr << "\033[31mWARNING: Maximum color value is not 255. This is not fully supported.\033[0m" << std::endl;
    }
    bitsPerPixel = 24; // P3 and P6 are typically 24-bit

    // Calculate the expected number of bytes in the image data section
    // static_cast<size_t>(width) - telling the compiler that you're aware of the type conversion and you want it to happen
    // To prevent leading to integer overflow
    size_t expectedByteCount = (magicNumber == "P6") ? static_cast<size_t>(width) * height * 3 : static_cast<size_t>(width) * height * 3 * 4;
    std::vector<char> imageData;            // Vector to store the image data as raw bytes.
    imageData.reserve(expectedByteCount);
    // resize is used to allocate the exact required memory
    // reserve is used to allocate enough memory to avoid reallocations during the conversion
    // from ASCII to binary, but the vector is not resized to this large amount.
    if (magicNumber == "P6") { // 3 bytes per pixel for RGB
        // Read binary data for P6 format
        imageData.resize(static_cast<size_t>(width) * height * 3); // Pre-allocate the exact number of bytes
        file.read(imageData.data(), imageData.size()); // Read the raw bytes directly into the vector
/*std::istream::gcount*/if (file.gcount() != imageData.size()) { // Check if the expected number of bytes were read.
            throw std::runtime_error("Error reading image data from file.  Expected " + std::to_string(expectedByteCount) + " bytes.");
        }
    } else {
        // Read ASCII data for P3 format
        for (int i = 0; i < height; ++i) { // Iterate over each row of the image
            for (int j = 0; j < width; ++j) { // Iterate over each column (pixel) in the row
                int r, g, b; // Variables to store the red, green, and blue color components of a pixel
                file >> r >> g >> b; // Read the RGB components as integers from the file
                if (file.fail() || width <= 0 || height <= 0) { // Check if reading from the file failed.  This could indicate a truncated or corrupted file
                    throw std::runtime_error("\033[31mERROR: Error reading pixel data.  File may be truncated or corrupted.\033[0m"); // Throw an exception with a descriptive error message.
                }
                std::stringstream rStream, gStream, bStream; // Create stringstreams to convert the integer RGB values to strings
                rStream << r; gStream << g; bStream << b; // Convert the integer RGB values to strings
                std::string rStr = rStream.str(); // Get the red string
                std::string gStr = gStream.str(); // Get the green string
                std::string bStr = bStream.str(); // Get the blue string

                imageData.insert(imageData.end(), rStr.begin(), rStr.end()); // Append the red string to the imageData vector
                imageData.push_back(' '); // Add a space separator after the red value
                imageData.insert(imageData.end(), gStr.begin(), gStr.end()); // Append the green string to the imageData vector
                imageData.push_back(' '); // Add a space separator after the green value
                imageData.insert(imageData.end(), bStr.begin(), bStr.end()); // Append the blue string to the imageData vector
                imageData.push_back(' '); // Add a space separator after the blue value
            }
        }
    }
    return imageData;
}