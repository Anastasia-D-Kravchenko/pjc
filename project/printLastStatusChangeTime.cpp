void printLastStatusChangeTime(const time_t time) {
    try{
        std::cout << "Last status change time: " << std::ctime(&time);
    } catch (const std::exception& e) {
        std::cerr << "Error printing last status change time: " << e.what() << std::endl;
    }
}