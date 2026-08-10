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
        Snake snake1(grid.getWidth() * 3 / 4, grid.getHeight() / 2, 2, grid.getHeight(), grid.getWidth());
        Snake snake2(grid.getWidth() / 4, grid.getHeight() / 2, 2, grid.getHeight(), grid.getWidth());
        Food food(grid.getHeight(), grid.getWidth());
    
        food.randomFoodPosition(snake1.getSnakeBody(), snake2.getSnakeBody());
        
        char direction1 = 'A'; // P1 starts moving left (arrow keys)
        char direction2 = 'D'; // P2 starts moving right (WASD)
        bool gameOver = false;
        int score1 = 0;
        int score2 = 0;
        int loser = 0;
    
        
        while (!gameOver) {
            // Draw
            // grid.clearScreen();
            grid.drawGameGrid(snake1, snake2, food, score1, score2);
            
            // Input
            if (kbhit()) {
                char input = getch();
                if (input == 'x' || input == 'X'){
                    break;
                }
                // P2 controls: W A S D
                if (input == 'w' || input == 'W' || input == 'a' || input == 'A' ||
                    input == 's' || input == 'S' || input == 'd' || input == 'D') {
                    direction2 = toupper(input);
                }
                // P1 controls: Arrow keys (Windows: 224 then scan code)
                #ifdef _WIN32
                if (input == (char)224) {
                    char arrow = getch();
                    if (arrow == 72) direction1 = 'W'; // Up
                    else if (arrow == 80) direction1 = 'S'; // Down
                    else if (arrow == 75) direction1 = 'A'; // Left
                    else if (arrow == 77) direction1 = 'D'; // Right
                }
                #else
                // Linux/Mac: ESC [ A/B/C/D
                if (input == 27) {
                    if (kbhit()) {
                        char seq1 = getch();
                        if (seq1 == '[' && kbhit()) {
                            char seq2 = getch();
                            if (seq2 == 'A') direction1 = 'W'; // Up
                            else if (seq2 == 'B') direction1 = 'S'; // Down
                            else if (seq2 == 'D') direction1 = 'A'; // Left
                            else if (seq2 == 'C') direction1 = 'D'; // Right
                        }
                    }
                }
                #endif
            }
            
            snake1.move(direction1, false);
            snake2.move(direction2, false);
    
            if(snake1.isCollision()){
                loser = 1;
                gameOver = true;
                break;
            }
    
            if(snake2.isCollision()){
                loser = 2;
                gameOver = true;
                break;
            }

            // Check if snake1 head hits snake2 body
            {
                const Point& head1 = snake1.getSnakeBody()[0];
                for(const auto& seg : snake2.getSnakeBody()){
                    if(head1.x == seg.x && head1.y == seg.y){
                        loser = 1;
                        gameOver = true;
                        break;
                    }
                }
            }

            // Check if snake2 head hits snake1 body
            if(!gameOver){
                const Point& head2 = snake2.getSnakeBody()[0];
                for(const auto& seg : snake1.getSnakeBody()){
                    if(head2.x == seg.x && head2.y == seg.y){
                        loser = 2;
                        gameOver = true;
                        break;
                    }
                }
            }

            if(gameOver) break;
    
            // Check food collision for snake1
            if (snake1.getSnakeBody()[0].x == food.getPosition().x && snake1.getSnakeBody()[0].y == food.getPosition().y) {
                score1 += 10;
                snake1.move(direction1, true);
                food.randomFoodPosition(snake1.getSnakeBody(), snake2.getSnakeBody());
            }
            // Check food collision for snake2
            else if (snake2.getSnakeBody()[0].x == food.getPosition().x && snake2.getSnakeBody()[0].y == food.getPosition().y) {
                score2 += 10;
                snake2.move(direction2, true);
                food.randomFoodPosition(snake1.getSnakeBody(), snake2.getSnakeBody());
            }
    
           
            // Sleep(200); // Game speed

            sleep_ms(200);
        }
    

        if (playAgain) {  // Only show if not quit with 'X'
            grid.showGameOver(score1, score2, loser);
            
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
