// function to check file permissions (read and write ps:no execution)
// ifstream when you only need to read data from a file.
// ofstream when you only need to write data to a file.
// fstream when you need to both read and write data to the same file.
bool checkFilePermissions(const std::string& filename, bool write_access) {
    // 1. Check if the file can be opened for reading
    std::ifstream file(filename); // Use ifstream for reading
    if (!file.is_open()) {
        std::cerr << "\033[31mError: Cannot open file '" << filename << "' for reading.\033[0m" << std::endl;
        return false;
    }
    std::cout << "\033[33mFile '" << filename << "' can be opened for reading.\033[0m" << std::endl;
    file.close(); // Close the file after checking

    // 2. If write access is required, check if the file can be opened for writing
    if (write_access) {
        std::ofstream test_file(filename, std::ios::app); // Use ofstream for writing in append mode
        if (!test_file.is_open()) {
            std::cerr << "\033[31mError: Cannot open file '" << filename << "' for writing.\033[0m" << std::endl;
            return false;
        }
        std::cout << "\033[33mFile '" << filename << "' can be opened for writing.\033[0m" << std::endl;
        test_file.close();
    }
    return true;
}