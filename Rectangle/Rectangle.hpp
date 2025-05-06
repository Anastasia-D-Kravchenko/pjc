#pragma once
struct Rectangle {
    int width = 0;
    int height = 0;

    // Returns the calculated area of the rectangle.
    int area() const;

    // Scales the width and height of the rectangle by the given factor.
    void scale(int factor);
};

// Doubles the area of the given rectangle. The specific method of doubling
// (e.g., doubling width, doubling height) is implementation-defined
// in the corresponding .cpp file.
void doubleSize(Rectangle& rect);