
#include <iostream>
#include <cctype>
#include <conio.h>
#include <windows.h>

#include "Point.h"
#include "Board.h"
#include "Snake.h"
#include "Food.h"
#include "Game.h"

//for file handling
#include <fstream>
#include <iostream>

using namespace std;

// Display the board
void displayBoard(
    const Board& board,
    const Snake& snake,
    const NormalFood& normalFood,
    const PoisonFood& poisonFood
) {
    cout << "SNAKE GAME\n";

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
void displayStatus(const Game& game) {
    cout << "\nScore: " << game.getScore();
    cout << "\nHearts: ";

    for (int i = 0; i < game.getHearts(); i++) {
        cout << "<3 ";
    }

    cout << "\nControls: W A S D | Q = Quit\n";
}

// Read input without waiting for Enter
bool handleInput(char input, Snake& snake) {
    switch (tolower(static_cast<unsigned char>(input))) {
        case 'w':
            snake.setDirection(Direction::Up);
            break;

        case 's':
            snake.setDirection(Direction::Down);
            break;

        case 'a':
            snake.setDirection(Direction::Left);
            break;

        case 'd':
            snake.setDirection(Direction::Right);
            break;

        case 'q':
            return false;
    }

    return true;
}


//for file handling - we will be storing high scores
int loadHighScore()
{
    std::ifstream file("highscore.txt");
    int highScore = 0;

    if (file >> highScore)
        return highScore;

    return 0;
}

void saveHighScore(int score)
{
    std::ofstream file("highscore.txt");

    if (!file)
    {
        std::cerr << "Could not save high score.\n";
        return;
    }

    file << score;
}

//change made here
void openHighScoreFile()
{
    system("start notepad highscore.txt");
}

int main() {
    Board board(20, 30);

    Snake snake(Point(10, 10), 3, Direction::Right);

    NormalFood normalFood(Point(15, 10));
    PoisonFood poisonFood(Point(20, 10));

//change made here
  Game game;
  bool running = true;

// Load the previously saved high score
int highScore = loadHighScore();

cout << "High score: " << highScore << '\n';
//till here^

    cout << "Starting Snake Game...\n";
    cout << "The snake moves automatically.\n";
    cout << "Press any key to begin.\n";
    _getch();

    while (running && !game.isGameOver()) {
        // Refresh the display
        system("cls");

        displayBoard(board, snake, normalFood, poisonFood);
        displayStatus(game);

        // Read a key only if one is available.
        // The game does not wait for keyboard input.
        if (_kbhit()) {
            char input = _getch();
            running = handleInput(input, snake);
        }

        if (!running) {
            break;
        }

        // Save the previous snake state for collision recovery.
        Snake previousSnake = snake;

        // Move automatically every tick.
        snake.move();

        Point head = snake.getHead();

        // Check wall collision
        if (!board.isInside(head)) {
            game.handleCollision();

            if (!game.isGameOver()) {
                snake = Snake(
                    Point(10, 10), 3, Direction::Right
                );
                game.recover();
            }
        }
        // Check self-collision
        else if (snake.hitsItself()) {
            game.handleCollision();

            if (!game.isGameOver()) {
                snake = Snake(
                    Point(10, 10), 3, Direction::Right
                );
                game.recover();
            }
        }
        else {
            // Normal food
            if (head == normalFood.getPosition()) {
                normalFood.applyEffect(snake, game);
                normalFood.respawn(board, snake);
            }

            // Poison food
            else if (head == poisonFood.getPosition()) {
                poisonFood.applyEffect(snake, game);

                if (!game.isGameOver()) {
                    poisonFood.respawn(board, snake);
                }
            }
        }

        // Control the snake's movement speed.
        Sleep(150);
    }

    system("cls");

    cout << "========== GAME OVER ==========\n";
    cout << "Final score: " << game.getScore() << '\n';
    cout << "Hearts remaining: " << game.getHearts() << '\n';

// Save the new high score if the player beats the record
if (game.getScore() > highScore)
{
    saveHighScore(game.getScore());
    cout << "New high score!\n";
}

    if (!game.isGameOver()) {
        cout << "You quit the game.\n";
    }

//change occured here
    // Save the new high score if the player beats the record
if (game.getScore() > highScore)
{
    saveHighScore(game.getScore());
    cout << "New high score!\n";
}

    cout << "Thanks for playing!\n";

    // Automatically open the high scores file
    openHighScoreFile(); //for calling function to open file that stores files
    return 0;
}
