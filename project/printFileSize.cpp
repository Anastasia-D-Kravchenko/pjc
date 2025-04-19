void printFileSize(const long int size) {
    try {
        std::cout << "Size: " << size << " bytes" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error printing file size: " << e.what() << std::endl;
    }
}