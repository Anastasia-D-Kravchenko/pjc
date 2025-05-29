std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r"); // Include tabs and newlines
    // size_t guarantee: enough space + non-negative value
    if (std::string::npos == first) { // indicates "not found". It's typically the largest possible value for size_t
        return "";
    }
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, (last - first + 1));
}