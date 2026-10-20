
#include "Food.h"
#include <cassert>
#include <iostream>

int main() {
    Board board(30, 30);
    Snake snake(Point(10, 10), 3);

    int score = 0;
    int hearts = 3;

    NormalFood normalFood;
    PoisonFood poisonFood;

    normalFood.respawn(board, snake);
    poisonFood.respawn(board, snake);

    assert(!snake.occupies(normalFood.getPosition()));
    assert(!snake.occupies(poisonFood.getPosition()));

    normalFood.applyEffect(snake, score, hearts);

    assert(snake.getLength() == 4);
    assert(score == 1);
    assert(hearts == 3);

    poisonFood.applyEffect(snake, score, hearts);

    assert(snake.getLength() == 3);
    assert(score == 1);
    assert(hearts == 2);

    std::cout << "All Member 3 tests passed!\n";
    return 0;
}
