// function to check file permissions (read and write ps:no execution)
bool checkFilePermissions(const std::string& filename, bool write_access) {
    std::fstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    std::cout << "Opening file '" << filename << "'." << std::endl;
    file.close();
    if (write_access) {
        std::fstream test_file(filename, std::ios::app); // std::ios::app — go to the end of the file on each write operation;
        if (!test_file.is_open()) {
            std::cout << "Error writing to file '" << filename << "' cannot write to the file" << std::endl;
            return false;
        }
        std::cout << "Writing to file '" << filename << "' - possible" << std::endl;
        test_file.close();
    }
    return true;
}