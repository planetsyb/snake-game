
#include "Point.h"

// Default constructor
Point::Point() {
    x = 0;
    y = 0;
}

// Parameterized constructor
Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

// Addition operator
Point Point::operator+(const Point& other) const {
    return Point(x + other.x, y + other.y);
}

// Equality operator
bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y;
}
