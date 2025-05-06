#include "Rectangle.hpp"

int Rectangle::area() const {
    return width * height;
}

void Rectangle::scale(int factor) {
    width *= factor;
    height *= factor;
}

void doubleSize(Rectangle& rect) {
    rect.width *= 2;
}