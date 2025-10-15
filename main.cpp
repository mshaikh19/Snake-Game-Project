#include <iostream>
#include <conio.h>
#include <windows.h>
#include "snake.h"
#include "gamegrid.h"
#include "food.h"

using namespace std;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

int main() {
    GameGrid grid(20, 20);
    Snake snake(grid.getWidth() / 2, grid.getHeight() / 2);
    Food food(grid.getWidth(), grid.getHeight());

    Direction dir = STOP;
    bool gameOver = false;
    int score = 0;

    while (!gameOver) {
        // Draw
        system("cls");
        grid.drawGrid();

        // Display snake and food inside grid area
        for (int y = 0; y < grid.getHeight(); y++) {
            for (int x = 0; x < grid.getWidth(); x++) {
                if (x == snake.getX() && y == snake.getY()) {
                    cout << "O"; // Snake head
                }
                else if (x == food.getX() && y == food.getY()) {
                    cout << "F"; // Food
                }
                else {
                    // Check if part of tail
                    bool isTail = false;
                    for (int t = 0; t < snake.getTailLength(); t++) {
                        if (x == snake.getTailX(t) && y == snake.getTailY(t)) {
                            cout << "o";
                            isTail = true;
                            break;
                        }
                    }
                    if (!isTail) cout << " ";
                }
            }
            cout << "\n";
        }
        cout << "Score: " << score << "\n";

        // Input
        if (_kbhit()) {
            switch (_getch()) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = true;
                break;
            }
        }

        // Logic
        switch (dir) {
        case LEFT:
            snake.move(-1, 0);
            break;
        case RIGHT:
            snake.move(1, 0);
            break;
        case UP:
            snake.move(0, -1);
            break;
        case DOWN:
            snake.move(0, 1);
            break;
        }

        // Check collisions with walls
        if (snake.getX() < 0 || snake.getX() >= grid.getWidth() || snake.getY() < 0 || snake.getY() >= grid.getHeight()) {
            gameOver = true;
        }

        // Check food collision
        if (snake.getX() == food.getX() && snake.getY() == food.getY()) {
            score += 10;
            snake.grow();
            food.generateNewPosition();
        }

        // Check collision with tail
        for (int t = 0; t < snake.getTailLength(); t++) {
            if (snake.getX() == snake.getTailX(t) && snake.getY() == snake.getTailY(t)) {
                gameOver = true;
            }
        }

        Sleep(100); // Game speed
    }

    cout << "Game Over! Final score: " << score << "\n";
    system("pause");
    return 0;
}

