#include <iostream>
#include <conio.h>
#include <windows.h>
#include <io.h>     
#include <fcntl.h> 

#include "Snake.h"
#include "GameGrid.h"
#include "Food.h"

using namespace std;

int main() {
    // _setmode(_fileno(stdout), _O_U16TEXT);
    system("chcp 65001");
    system("cls");
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

    cout << "Game Over! Final score: " << score << "\n";
    system("pause");
    return 0;
}
