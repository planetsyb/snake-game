
#ifndef POINT_H
#define POINT_H

class Point {
public:
    int x;  // Column position
    int y;  // Row position

    // Default constructor
    Point();

    // Parameterized constructor
    Point(int x, int y);

    // Overloaded addition operator
    Point operator+(const Point& other) const;

    // Overloaded equality operator
    bool operator==(const Point& other) const;
};

#endif
