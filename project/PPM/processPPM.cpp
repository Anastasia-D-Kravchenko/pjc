// https://courses.cs.washington.edu/courses/cse576/06sp/software/ppmman.html#:~:text=A%20ppm%20file's%20magic%20number,as%20ASCII%20characters%20in%20decimal.
void processPPM(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "\033[31mError: Could not open file: " << filename << "\033[0m" << std::endl;
        return;
    }

    std::string magicNumber;
    int width, height, maxColorValue;

    // P3 204 174 255
    // 254 254 255 25 ...
    // PPM Magic Number: P3
    // Width:  204
    // Height: 174
    // Max Color Value: 255

    // Read the PPM header
    std::getline(file, magicNumber); // Has all data in one place ( first row )
    file >> width >> height >> maxColorValue;
    file.ignore(); // Consume the newline character after reading the header

    // Output the PPM header information
    std::cout << "\033[35mPPM Magic Number: \033[0m" << magicNumber << std::endl;
    std::cout << "Width:  " << width << std::endl;
    std::cout << "Height: " << height << std::endl;
    std::cout << "Max Color Value: " << maxColorValue << std::endl;
}