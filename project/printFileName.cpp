void printFileName(const char* filename) {
    try{
        std::cout << "File: " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError printing file name: " << e.what() << "\033[0m" << std::endl;
    }
}