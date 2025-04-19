void printFilePermissions(const int mode) {
    try{
        std::cout << "File permissions: ";
        std::cout << "\nOwner: ";
        if (mode & S_IRUSR) std::cout << "Read "; else std::cout << "None ";
        if (mode & S_IWUSR) std::cout << "Write "; else std::cout << "None ";
        if (mode & S_IXUSR) std::cout << "Execute"; else std::cout << "None";
        std::cout << "\nGroup: ";
        if (mode & S_IRGRP) std::cout << "Read "; else std::cout << "None ";
        if (mode & S_IWGRP) std::cout << "Write "; else std::cout << "None ";
        if (mode & S_IXGRP) std::cout << "Execute"; else std::cout << "None";
        std::cout << "\nOthers: ";
        if (mode & S_IROTH) std::cout << "Read "; else std::cout << "None ";
        if (mode & S_IWOTH) std::cout << "Write "; else std::cout << "None ";
        if (mode & S_IXOTH) std::cout << "Execute"; else std::cout << "None";
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error printing file permissions: " << e.what() << std::endl;
    }
}