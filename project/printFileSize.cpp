void printFileSize(const long int size) {
    try {
        std::cout << "Size: " << size << " bytes" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError printing file size: " << e.what() << "\033[0m" << std::endl;
    }
}