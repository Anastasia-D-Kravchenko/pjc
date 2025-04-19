void printFileName(const char* filename) {
    try{
        std::cout << "File: " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error printing file name: " << e.what() << std::endl;
    }
}