
#include <iostream>
#include <cctype>
#include <cstdlib>

#include "Point.h"
#include "Board.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

// Display the game board
void displayBoard(const Board& board,
                  const Snake& snake,
                  const NormalFood& normalFood,
                  const PoisonFood& poisonFood) {
    cout << "\n";

    for (int y = 0; y < board.getRows(); y++) {
        for (int x = 0; x < board.getCols(); x++) {
            Point current(x, y);

            if (snake.getHead() == current) {
                cout << 'O';
            }
            else if (snake.occupies(current)) {
                cout << 'o';
            }
            else if (normalFood.getPosition() == current) {
                cout << '*';
            }
            else if (poisonFood.getPosition() == current) {
                cout << 'X';
            }
            else {
                cout << '.';
            }
        }
        cout << '\n';
    }
}

// Display score and hearts
void displayStatus(int score, int hearts) {
    cout << "\nScore: " << score;
    cout << "\nHearts: ";

    for (int i = 0; i < hearts; i++) {
        cout << "<3 ";
    }

    cout << "\n";
}

// Read the player's input
bool handleInput(char input, Snake& snake) {
    switch (tolower(static_cast<unsigned char>(input))) {
        case 'w':
            snake.setDirection(Direction::Up);
            return true;

        case 's':
            snake.setDirection(Direction::Down);
            return true;

        case 'a':
            snake.setDirection(Direction::Left);
            return true;

        case 'd':
            snake.setDirection(Direction::Right);
            return true;

        case 'q':
            return false;

        default:
            cout << "Invalid input! Use W, A, S, D or Q.\n";
            return true;
    }
}

int main() {
    Board board(20, 30);

    Snake snake(Point(10, 10), 3, Direction::Right);

    NormalFood normalFood(Point(15, 10));
    PoisonFood poisonFood(Point(20, 10));

    int score = 0;
    int hearts = 3;
    bool gameOver = false;

    cout << "====================================\n";
    cout << "           SNAKE GAME\n";
    cout << "====================================\n";
    cout << "Controls:\n";
    cout << "W - Up | A - Left | S - Down | D - Right\n";
    cout << "Q - Quit\n";
    cout << "\nO = Snake Head | o = Body\n";
    cout << "* = Normal Food (+1 point)\n";
    cout << "X = Poison (-1 heart)\n";
    cout << "\nPress a key and then Enter to move.\n";

    while (!gameOver) {
        displayBoard(board, snake, normalFood, poisonFood);
        displayStatus(score, hearts);

        cout << "\nEnter your move (W/A/S/D/Q): ";

        char input;
        if (!(cin >> input)) {
            cout << "\nInput ended. Exiting game.\n";
            break;
        }

        // Quit the game
        if (tolower(static_cast<unsigned char>(input)) == 'q') {
            cout << "\nThanks for playing!\n";
            break;
        }

        // Keep a copy so an invalid move can be undone
        Snake previousSnake = snake;

        if (!handleInput(input, snake)) {
            break;
        }

        // Move the snake one step
        snake.move();

        Point head = snake.getHead();

        // Check wall collision
        if (!board.isInside(head)) {
            snake = previousSnake;
            hearts--;

            cout << "\nWall collision! You lost one heart.\n";
        }
        // Check collision with the snake's own body
        else if (snake.hitsItself()) {
            snake = previousSnake;
            hearts--;

            cout << "\nSelf-collision! You lost one heart.\n";
        }
        else {
            // Check normal food
            if (head == normalFood.getPosition()) {
                normalFood.applyEffect(snake, score, hearts);

                cout << "\nYou ate normal food! +1 point.\n";

                normalFood.respawn(board, snake);
            }

            // Check poison food
            else if (head == poisonFood.getPosition()) {
                poisonFood.applyEffect(snake, score, hearts);

                cout << "\nYou ate poison! -1 heart.\n";

                poisonFood.respawn(board, snake);
            }
        }

        // End the game when no hearts remain
        if (hearts <= 0) {
            hearts = 0;
            gameOver = true;
        }
    }

    cout << "\n====================================\n";

    if (hearts == 0) {
        cout << "             GAME OVER!\n";
    }

    cout << "Final Score: " << score << '\n';
    cout << "Hearts Remaining: " << hearts << '\n';
    cout << "Thanks for playing Snake!\n";
    cout << "====================================\n";

    return 0;
}
