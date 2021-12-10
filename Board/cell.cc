#include "cell.h"

Cell::Cell(const int x, const int y) : type{0}, filled{false}, x{x}, y{y} {}

void Cell::setType(const char c) {
    type = c;
    if (!filled) {
        filled = true;
    }
}