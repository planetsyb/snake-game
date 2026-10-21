
#include "Food.h"

#include <random>
#include <stdexcept>
#include <vector>


Food::Food(Point startPosition)
    : GameObject(startPosition) {
}


NormalFood::NormalFood(Point startPosition)
    : Food(startPosition) {
}

//change occured here
void NormalFood::applyEffect(
    Snake& snake,
    Game& game
) const {
    snake.grow(1);
    game.eatFood();
}

char NormalFood::getSymbol() const {
    return '*';
}


PoisonFood::PoisonFood(Point startPosition)
    : Food(startPosition) {
}

//change occured here
void PoisonFood::applyEffect(
    Snake& snake,
    Game& game
) const {
    snake.shrink(1);
    game.eatPoison();
}

char PoisonFood::getSymbol() const {
    return 'X';
}


void Food::respawn(const Board& board, const Snake& snake) {
    std::vector<Point> availablePositions;

    for (int y = 0; y < board.getRows(); y++) {
        for (int x = 0; x < board.getCols(); x++) {
            Point candidate(x, y);

            if (!snake.occupies(candidate)) {
                availablePositions.push_back(candidate);
            }
        }
    }

    if (availablePositions.empty()) {
        throw std::runtime_error(
            "Cannot spawn food: no unoccupied cells remain."
        );
    }

    static std::mt19937 generator(std::random_device{}());

    std::uniform_int_distribution<std::size_t> distribution(
        0,
        availablePositions.size() - 1
    );

    setPosition(availablePositions[distribution(generator)]);
}
