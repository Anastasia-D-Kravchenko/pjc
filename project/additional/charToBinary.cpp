// Function to convert a character to its binary representation (8 bits)
std::string charToBinary(const char c) {
    std::string binary;
    for (int i = 7; i >= 0; --i) {
        binary += ((c >> i) & 1) ? '1' : '0'; // The right shift operator (>>). This shifts the bits
                                              // of the character c to the right by i positions.
    }
    return binary;
}