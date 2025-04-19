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
        struct stat fileInfo;

        if (stat(filename, &fileInfo) != 0) {
            throw std::runtime_error(strerror(errno)); // Throw an exception with the error message
        }
        printFileName(filename);
        printFileSize(fileInfo.st_size); // Regular File: The number of data bytes in the file.
        printLastAccessTime(fileInfo.st_mtime);
        printLastModificationTime(fileInfo.st_mtime); // The most recent time the contents of the file were changed.
        printLastStatusChangeTime(fileInfo.st_ctime); // The most recent time the status of the file was changed.
        printFilePermissions(fileInfo.st_mode); // A bit string indicating the permissions and privileges of the file
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}