#include <iostream>
#include <conio.h>
#include <windows.h>
#include <io.h>     
#include <fcntl.h> 
#include <thread>
#include <chrono>
#include "Snake.h"
#include "GameGrid.h"
#include "Food.h"

using namespace std;
void showCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


int main() {
    system("chcp 65001");
    // Sleep(5000);
    system("cls");

    bool playAgain = true;

    while(playAgain){

        GameGrid grid(20, 20);
        Snake snake(grid.getWidth() / 2, grid.getHeight() / 2, 2, grid.getHeight(), grid.getWidth());
        Food food(grid.getHeight(), grid.getWidth());
    
        food.randomFoodPosition(snake.getSnakeBody());
        
        char direction = 'D';
        bool gameOver = false;
        int score = 0;
    
        
        while (!gameOver) {
            // Draw
            grid.drawGameGrid(snake, food, score);
            
            // Input
            if (_kbhit()) {
                char input = _getch();
                if (input == 'x' || input == 'X'){
                    break;
                }
                if (input == 'w' || input == 'W' || input == 'a' || input == 'A' ||
                    input == 's' || input == 'S' || input == 'd' || input == 'D') {
                    direction = toupper(input);
                }
            }
            
            snake.move(direction, false);
    
            // auto head = snake.getSnakeBody()[0];
            // cout << "Snake head at (" << head.x << "," << head.y << ")" << endl;
    
            if(snake.isCollision()){
                gameOver = true;
                break;
            }
    
            // Check food collision
            if (snake.getSnakeBody()[0].x == food.getPosition().x && snake.getSnakeBody()[0].y == food.getPosition().y) {
                score += 10;
                snake.move(direction, true);
                food.randomFoodPosition(snake.getSnakeBody());
            }
    
           
            Sleep(200); // Game speed
        }
    

        if (playAgain) {  // Only show if not quit with 'X'
            grid.showGameOver(score);
            
            // Wait for user choice
            bool validInput = false;
            while (!validInput) {
                if (_kbhit()) {
                    char choice = _getch();
                    
                    if (choice == '\r' || choice == '\n') {  // ENTER key
                        playAgain = true;
                        validInput = true;
                        system("cls");
                    } else if (choice == 'q' || choice == 'Q') {  // Q key
                        playAgain = false;
                        validInput = true;
                    }
                }
                Sleep(50);  // Small delay to prevent CPU overuse
            }
        }
        // cout << "Game Over! Final score: " << score << "\n";
        // system("pause");
    }

    system("cls");
    
    cout << "\n\n";
    cout << "    ╔════════════════════════════════════════╗\n";
    cout << "    ║                                        ║\n";
    cout << "    ║    Thanks for playing Snake Game! 🐍   ║\n";
    cout << "    ║                                        ║\n";
    cout << "    ╚════════════════════════════════════════╝\n";
    cout << "\n";
    return 0;
}
