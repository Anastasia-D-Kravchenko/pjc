void printFilePermissions(const int mode) { // The permissions are not stored as simple characters like "rwx"; they're encoded as a set of bits within an integer
    try{
        // S_IRUSR = 100000000  (binary)  r--------              110101101
        // S_IWUSR = 010000000  (binary)  -w-------            & 100000000
        // S_IXUSR = 001000000  (binary)  --x------             -----------
        // S_IRGRP = 000100000  (binary)  ---r------             100000000   has read
        // S_IWGRP = 000010000  (binary)  ----w-----              110101101
        // S_IXGRP = 000001000  (binary)  -----x----            & 001000000
        // S_IROTH = 000000100  (binary)  ------r---             -----------
        // S_IWOTH = 000000010  (binary)  -------w--              000000000  dosn't have execute
        // S_IXOTH = 000000001  (binary)  --------x
        std::cout << "File permissions: "; // S_IR or S_IW or S_IX (rwx)
        std::cout << "\nOwner: "; // USR for current user
        if (mode & S_IRUSR) std::cout << "Read "; else std::cout << "None "; // If a specific bit is set (1) in both operands, the corresponding bit in the result is also 1; otherwise, it's 0
        if (mode & S_IWUSR) std::cout << "Write "; else std::cout << "None "; // 0 0 -> 0 | 1 1 -> 0 | 0 1 -> 0 We have a problem! 0 and 1 not the same false!
        if (mode & S_IXUSR) std::cout << "Execute"; else std::cout << "None";
        std::cout << "\nGroup: "; // GRP for user group
        if (mode & S_IRGRP) std::cout << "Read "; else std::cout << "None ";
        if (mode & S_IWGRP) std::cout << "Write "; else std::cout << "None ";
        if (mode & S_IXGRP) std::cout << "Execute"; else std::cout << "None";
        std::cout << "\nOthers: "; // OTH for other
        if (mode & S_IROTH) std::cout << "Read "; else std::cout << "None ";
        if (mode & S_IWOTH) std::cout << "Write "; else std::cout << "None ";
        if (mode & S_IXOTH) std::cout << "Execute"; else std::cout << "None";
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "\033[31mError printing file permissions: " << e.what() << "\033[0m" << std::endl;
    }
}