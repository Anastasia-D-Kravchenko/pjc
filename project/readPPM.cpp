// Function to read PPM file header and extract image data.
// PPM Header:
//  - Magic Number: "P6/P3" (for binary PPM)
//  - Width (ASCII integer)
//  - Height (ASCII integer)
//  - Maximum color value (ASCII integer, e.g., 255)
//  - Newline character after the header
// Image Data:
//  - Raw RGB pixel data, packed as bytes.  Each pixel is 3 bytes (red, green, blue).
#include "trim.cpp"
// https://faculty.college.emory.edu/sites/weeks/graphics/mkppm.html#:~:text=PPM%20stands%20for%20%22Portable%20Pixel,exact%20color%20of%20each%20pixel.
// https://www.cs.rhodes.edu/~kirlinp/courses/cs1/f19/projects/proj8/
std::vector<char> readPPM(const std::string& filename, uint32_t& width, uint32_t& height, uint16_t& bitsPerPixel) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("\033[31mERROR: Could not open file.\033[0m");
    }

    std::string magicNumber;
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

     // Convert maxColorValue to integer.
     int maxColorValue;
     try{
        maxColorValue = std::stoi(maxColorValueStr);
     } catch(const std::invalid_argument& e){
        throw std::runtime_error("\033[31mERROR: Invalid max color value in PPM header.\033[0m");
     }

    if (maxColorValue != 255) {
        std::cerr << "\033[31mWARNING: Maximum color value is not 255.  This is not fully supported.\033[0m" << std::endl;
    }

    bitsPerPixel = 24; // PPM P3 is also 24 bits per pixel, though stored as ASCII

    // Calculate the expected number of *characters* in the image data section.
    size_t expectedCharCount = static_cast<size_t>(width) * height * 3 * 4; // 3 values per pixel, max 3 digits + space.
    std::vector<char> imageData;
    imageData.reserve(expectedCharCount); //reserve memory

    // Read the image data.
     for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int r, g, b;
            file >> r >> g >> b;
             if (file.fail()) {
                throw std::runtime_error("\033[31mERROR: Error reading pixel data.  File may be truncated or corrupted.\033[0m");
             }
            std::stringstream rStream, gStream, bStream;
            rStream << r; gStream << g; bStream << b;
            std::string rStr = rStream.str();
            std::string gStr = gStream.str();
            std::string bStr = bStream.str();
            imageData.insert(imageData.end(), rStr.begin(), rStr.end());
            imageData.push_back(' ');
            imageData.insert(imageData.end(), gStr.begin(), gStr.end());
            imageData.push_back(' ');
            imageData.insert(imageData.end(), bStr.begin(), bStr.end());
            imageData.push_back(' ');
        }
    }
    std::cout << imageData.size() << std::endl;
    return imageData;
}