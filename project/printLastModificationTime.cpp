void printLastModificationTime(const time_t time) {
    try{
        std::cout << "Last modification time: " << std::ctime(&time); // representing the corresponding date and time in a human-readable format.
    } catch (const std::exception& e) {
        std::cerr << "Error printing last modification time: " << e.what() << std::endl;
    }
}