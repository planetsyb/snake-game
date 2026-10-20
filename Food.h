
#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"
#include "Board.h"
#include "Snake.h"

class Food : public GameObject {
public:
    explicit Food(Point startPosition);

    virtual void applyEffect(
        Snake& snake,
        int& score,
        int& hearts
    ) const = 0;

    void respawn(const Board& board, const Snake& snake);

    ~Food() override = default;
};

class NormalFood : public Food {
public:
    explicit NormalFood(Point startPosition = Point());

    void applyEffect(
        Snake& snake,
        int& score,
        int& hearts
    ) const override;

    char getSymbol() const override;
};

class PoisonFood : public Food {
public:
    explicit PoisonFood(Point startPosition = Point());

    void applyEffect(
        Snake& snake,
        int& score,
        int& hearts
    ) const override;

    char getSymbol() const override;
};

#endif
