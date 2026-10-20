

#ifndef GAME_H
#define GAME_H

class Game {
private:
    int score;
    int hearts;
    bool gameOver;
    bool collisionHandled;

public:
    // Constructor
    Game();

    // Getters
    int getScore() const;
    int getHearts() const;
    bool isGameOver() const;

    // Game logic
    void eatFood();
    void eatPoison();
    void handleCollision();
    void recover();
    void validate() const;
    void displayStatus() const;
};

#endif
