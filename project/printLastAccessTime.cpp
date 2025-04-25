void printLastAccessTime(const time_t time) {
    try{
        std::cout << "Last access time: " << std::ctime(&time); // representing the corresponding date and time in a human-readable format.
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError printing last access time: " << e.what() << "\033[0m" << std::endl;
    }
}