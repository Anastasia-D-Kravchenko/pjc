#include "printFileName.cpp"
#include "printFileSize.cpp"
#include "printLastAccessTime.cpp"
#include "printLastModificationTime.cpp"
#include "printLastStatusChangeTime.cpp"
#include "printFilePermissions.cpp"

// https://www.oreilly.com/library/view/c-cookbook/0596007612/ch10s07.html
// https://www.ibm.com/docs/en/i/7.3.0?topic=ssw_ibm_i_73/apis/stat.htm
void printFileInfo(const char* filename) {
    try {
        struct stat fileInfo; // struct stat is a C structure (defined in <sys/stat.h>) that holds various information about a file, such as: File size, File permissions, Timestamps (last access, modification, etc.), File type (regular file, directory, etc.)

        if (stat(filename, &fileInfo) != 0) { // Stat() will fill this struct with the file's details
            throw std::runtime_error(strerror(errno)); // Throw an exception with the error message
        }
        printFileName(filename);
        printFileSize(fileInfo.st_size); // For Regular File: The number of data bytes in the file
        printLastAccessTime(fileInfo.st_atime); // The most recent time the contents of the file were accessed
        printLastModificationTime(fileInfo.st_mtime); // The most recent time the contents of the file were changed
        printLastStatusChangeTime(fileInfo.st_ctime); // The most recent time the status of the file was changed
        printFilePermissions(fileInfo.st_mode); // A bit string indicating the permissions and privileges of the file
    } catch (const std::runtime_error& e) {
        std::cerr << "\033[31mError: " << e.what() << "\033[0m" << std::endl;
    }
}