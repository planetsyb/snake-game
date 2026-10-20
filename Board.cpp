
#include "Board.h"
#include <stdexcept>

// Constructor
Board::Board(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument(
            "Board dimensions must be positive."
        );
    }

    this->rows = rows;
    this->cols = cols;
}

// Return number of rows
int Board::getRows() const {
    return rows;
}

// Return number of columns
int Board::getCols() const {
    return cols;
}

// Check if a point is inside the board
bool Board::isInside(Point p) const {
    return p.x >= 0 && p.x < cols &&
           p.y >= 0 && p.y < rows;
}
