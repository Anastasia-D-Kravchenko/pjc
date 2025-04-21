// Function to get file size
long getFileSize(const std::string& filename) {
    struct stat size{};
    if (stat(filename.c_str(), &size) == 0) {
        return size.st_size;
    }
    return -1; // Error
}