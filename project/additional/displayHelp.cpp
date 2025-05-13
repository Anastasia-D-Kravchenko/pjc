// intel how to use
void displayHelp() {
    std::cout << "Usage: steganography [flag] [arguments]" << std::endl;
    std::cout << "Supported file extensions: .bmp, .ppm" << std::endl;
    std::cout << "Flags:" << std::endl;
    std::cout << "  -i, --info <file_path>      : Display information about the image file." << std::endl;
    std::cout << "  -e, --encrypt <file_path> <message>:  Encrypt the message into the image file." << std::endl;
    std::cout << "  -d, --decrypt <file_path>       : Decrypt the message from the image file." << std::endl;
    std::cout << "  -c, --check <file_path> <message>  : Check if the message can be written to the image file." << std::endl;
    std::cout << "  -h, --help                  : Display this help information." << std::endl;
    std::cout << "  Running the program without any flags is equivalent to using the -h flag." << std::endl;
}