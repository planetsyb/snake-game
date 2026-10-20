
#ifndef BOARD_H
#define BOARD_H

#include "Point.h"

class Board {
private:
    int rows;
    int cols;

public:
    // Constructor with default dimensions
    Board(int rows = 30, int cols = 30);

    // Get board dimensions
    int getRows() const;
    int getCols() const;

    // Check whether a point is inside the board
    bool isInside(Point p) const;
};

#endif
