void printLastAccessTime(const time_t time) {
    try{
        std::cout << "Last access time: " << std::ctime(&time);
    } catch (const std::exception& e) {
        std::cerr << "Error printing last access time: " << e.what() << std::endl;
    }
}