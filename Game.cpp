

#include "Game.h"

#include <iostream>
#include <stdexcept>

using namespace std;

// Initialize game state
Game::Game()
    : score(0),
      hearts(3),
      gameOver(false),
      collisionHandled(false) {
}

// Getters
int Game::getScore() const {
    return score;
}

int Game::getHearts() const {
    return hearts;
}

bool Game::isGameOver() const {
    return gameOver;
}

// Increase score for safe food
void Game::eatFood() {
    if (!gameOver) {
        score += 10;
    }
}

// Handle poison food
void Game::eatPoison() {
    handleCollision();
}

// Handle wall and self-collisions
void Game::handleCollision() {
    if (gameOver || collisionHandled) {
        return;
    }

    collisionHandled = true;
    hearts--;

    cout << "Collision detected!\n";
    cout << "Hearts remaining: " << hearts << '\n';

    if (hearts <= 0) {
        hearts = 0;
        gameOver = true;
        cout << "GAME OVER!\n";
    }
}

// Reset collision protection after safe recovery
void Game::recover() {
    if (!gameOver) {
        collisionHandled = false;
    }
}

// Validate game state
void Game::validate() const {
    if (hearts < 0 || hearts > 3) {
        throw logic_error("Invalid heart count!");
    }

    if (score < 0) {
        throw logic_error("Invalid score!");
    }
}

// Display current game status
void Game::displayStatus() const {
    cout << "Score: " << score << '\n';
    cout << "Hearts: " << hearts << '\n';
    cout << "Game Over: "
         << (gameOver ? "Yes" : "No") << '\n';
}

