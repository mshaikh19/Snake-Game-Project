#include <iostream>
#include <vector>
#include <cstdio>

#include <locale>
#include <clocale>
// #include <conio.h>
// #include <windows.h>
// #include <io.h>     
// #include <fcntl.h> 
// #include <thread>
// #include <chrono>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
    #include <fcntl.h>
    #include <sys/ioctl.h>
#endif

#include "Snake.h"
#include "GameGrid.h"
#include "Food.h"

using namespace std;

// Cross-platform sleep function (milliseconds)
void sleep_ms(int ms) {
    #ifdef _WIN32
        Sleep(ms);
    #else
        usleep(ms * 1000);
    #endif
}


void showCursor() {
    // HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    // CONSOLE_CURSOR_INFO info;
    // info.dwSize = 100;
    // info.bVisible = TRUE;
    // SetConsoleCursorInfo(consoleHandle, &info);

    #ifdef _WIN32
        HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_CURSOR_INFO info;
        info.dwSize = 100;
        info.bVisible = TRUE;
        SetConsoleCursorInfo(consoleHandle, &info);
    #else
        cout << "\e[?25h" << flush;  // ANSI escape to show cursor
    #endif
}

// Cross-platform kbhit() and getch()
#ifdef _WIN32
    // Use _kbhit() and _getch() directly
    #define kbhit _kbhit
    #define getch _getch
#else
    int kbhit() {
        static const int STDIN = 0;
        static bool initialized = false;

        if (!initialized) {
            termios term;
            tcgetattr(STDIN, &term);
            term.c_lflag &= ~ICANON;  // Disable line buffering
            term.c_lflag &= ~ECHO;    // Turn off echo
            tcsetattr(STDIN, TCSANOW, &term);
            setbuf(stdin, NULL);
            initialized = true;
        }

        int bytesWaiting;
        ioctl(STDIN, FIONREAD, &bytesWaiting);
        return bytesWaiting > 0;
    }

    int getch() {
        return getchar();
    }
#endif

// Cross-platform clear screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // system("clear");
    std::cout << "\033[H\033[2J\033[3J" << std::flush;
#endif
}

// void clearScreen() {
//     system("cls");
// }

int main() {
    // system("chcp 65001");
    // Sleep(5000);
    // system("cls");

    clearScreen();

    #ifdef _WIN32
        system("chcp 65001"); // Enable UTF-8 console on Windows
    #else
        setlocale(LC_ALL, "");
        std::locale::global(std::locale(""));
    #endif  
    // Cross-platform clear screen
    
    // clearScreen();
    

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
            // grid.clearScreen();
            grid.drawGameGrid(snake, food, score);
            
            // Input
            if (kbhit()) {
                char input = getch();
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
    
           
            // Sleep(200); // Game speed

            sleep_ms(200);
        }
    

        if (playAgain) {  // Only show if not quit with 'X'
            grid.showGameOver(score);
            
            // Wait for user choice
            bool validInput = false;
            while (!validInput) {
                if (kbhit()) {
                    char choice = getch();
                    
                    if (choice == '\r' || choice == '\n') {  // ENTER key
                        playAgain = true;
                        validInput = true;
                        // system("cls");

                        clearScreen();
                    } else if (choice == 'q' || choice == 'Q') {  // Q key
                        playAgain = false;
                        validInput = true;
                    }
                }
                // Sleep(50);  // Small delay to prevent CPU overuse
                sleep_ms(50);
            }
        }
        // cout << "Game Over! Final score: " << score << "\n";
        // system("pause");
    }

    // system("cls");
    clearScreen();
    
    cout << "\n\n";
    cout << "    ╔══════════════════════════════════════════════════════╗\n";
    cout << "    ║                                                      ║\n";
    cout << "    ║    Thanks for playing Snake Game by SnakeByte++! 🐍  ║\n";
    cout << "    ║                                                      ║\n";
    cout << "    ╚══════════════════════════════════════════════════════╝\n";
    cout << "\n";
    return 0;
}
