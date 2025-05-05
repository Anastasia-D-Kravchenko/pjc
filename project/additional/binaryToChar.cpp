// Function to convert a binary string to a character
char binaryToChar(const std::string& binary) {
    if (binary.length() != 8) {
        throw std::runtime_error("\033[31mBinary string must be 8 bits long.\033[0m");
    }
    char c = 0;
    for (int i = 0; i < 8; ++i) {
        if (binary[i] == '1') {
            c |= (1 << (7 - i));
        }
    }
    return c;
}