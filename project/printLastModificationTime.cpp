void printLastModificationTime(const time_t time) {
    try{
        std::cout << "Last modification time: " << std::ctime(&time);
    } catch (const std::exception& e) {
        std::cerr << "Error printing last modification time: " << e.what() << std::endl;
    }
}