
#include <iostream>
#include "Point.h"
#include "GameObject.h"
#include "Board.h"

using namespace std;

int main() {
    // Test 1: Point constructors
    Point a(5, 3);
    Point b(1, 0);

    // Test 2: Operator overloading
    Point c = a + b;

    cout << "New point: ("
         << c.x << ", " << c.y << ")\n";

    cout << "Points equal? "
         << (a == b) << "\n";

    // Test 3: GameObject
    GameObject obj(Point(4, 2));

    Point pos = obj.getPosition();

    cout << "Object position: ("
         << pos.x << ", " << pos.y << ")\n";

    cout << "Object symbol: "
         << obj.getSymbol() << "\n";

    // Test 4: Board
    Board board(20, 30);

    cout << "Board rows: "
         << board.getRows() << "\n";

    cout << "Board columns: "
         << board.getCols() << "\n";

    cout << "Is (29, 19) inside? "
         << board.isInside(Point(29, 19)) << "\n";

    cout << "Is (30, 19) inside? "
         << board.isInside(Point(30, 19)) << "\n";

    return 0;
}
