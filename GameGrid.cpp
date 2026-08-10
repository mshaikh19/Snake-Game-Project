#include "GameGrid.h"
#include "Snake.h"
#include "Food.h"
#include <iostream>
#include <cstdio>
// #include <windows.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <termios.h>
    
#endif
#include <vector>


// Grid of NxN is defined
const int gridHeight = 10;
const int gridWidth = 20;

GameGrid::GameGrid(int w, int h) : width(w), height(h) {}

int GameGrid::getWidth() const{
	return width;
}
int GameGrid::getHeight() const{
	return height;
}

// void hideCursor() {
//     HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_CURSOR_INFO info;
//     info.dwSize = 100; 
//     info.bVisible = FALSE; 
//     SetConsoleCursorInfo(consoleHandle, &info);
// }

// Cross-platform hide cursor
void hideCursor() {
#ifdef _WIN32
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
#else
    cout << "\e[?25l" << flush;
#endif
}

// void GameGrid::setCursorPosition(int x, int y) {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     COORD pos = {(SHORT)x, (SHORT)y};
//     SetConsoleCursorPosition(hConsole, pos);
// }

// // Set console text color
// void setColor(int color) {
//     HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//     SetConsoleTextAttribute(hConsole, color);
// }

// Cross-platform set cursor position
void GameGrid::setCursorPosition(int x, int y) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hConsole, pos);
#else
    std::cout << "\033[" << (y+1) << ";" << (x+1) << "H" << std::flush;
#endif
}

// Cross-platform set text color
void setColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    // Using ANSI color codes for Linux
    // Common color mapping (simplified):
    // 0=black, 7=white, 8=gray, 10=green, 12=red, 13=magenta, 14=yellow, 15=bright white
    switch(color) {
        case 0: cout << "\e[30m"; break; // Black
        case 7: cout << "\e[37m"; break; // White
        case 8: cout << "\e[90m"; break; // Gray
        case 10: cout << "\e[32m"; break; // Green
        case 11: cout << "\e[36m"; break; // Cyan
        case 12: cout << "\e[31m"; break; // Red
        case 13: cout << "\e[35m"; break; // Magenta
        case 14: cout << "\e[33m"; break; // Yellow
        case 15: cout << "\e[97m"; break; // Bright white
        default: cout << "\e[0m"; break;  // Reset/default
    }
#endif
}

// Cross-platform clear screen
void GameGrid::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // system("clear");
    std::cout << "\033[H\033[2J\033[3J" << std::flush;
#endif
}

// void GameGrid::clearScreen() {
//     system("cls");
// }

// Cross-platform show cursor
void GameGrid::showCursor() {
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

// Drawing the empty grid
void GameGrid::drawGameGrid() {

//	Drawing the Top Boundry
//	The top left corner boundry
	cout << "🟦";
	
	//	The top boundry
	for(int i = 0; i < width; ++i){
		cout << "⬜";
	} 
	
	//	The top right corner boundry
	cout << "🟦";
	// cout << "|";
	cout << endl;
	
	for(int i = 0; i < height; i++){
//		The left boundry
		cout << "|";
		
//		The game area
		for(int j = 0; j < width; j++){			
			cout << ".";
		}
//		The right boundry
		cout << "|";
		cout << endl;
	}
}


// void GameGrid::showCursor() {
//     HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
//     CONSOLE_CURSOR_INFO info;
//     info.dwSize = 100;
//     info.bVisible = TRUE;
//     SetConsoleCursorInfo(consoleHandle, &info);
// }

// void GameGrid::clearScreen() {
//     system("cls");
// }

void GameGrid::showGameOver(int score1, int score2, int loser) {
    clearScreen();
    setCursorPosition(0, 0);
    hideCursor();
    
    cout << endl << endl;
    
    // ═══════════════════ GAME OVER TEXT ═══════════════════
    setColor(12); // Red
    
    cout << "    ██████╗  █████╗ ███╗   ███╗███████╗\n";
    cout << "   ██╔════╝ ██╔══██╗████╗ ████║██╔════╝\n";
    cout << "   ██║  ███╗███████║██╔████╔██║█████╗  \n";
    cout << "   ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  \n";
    cout << "   ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗\n";
    cout << "    ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝\n";
    
    cout << endl;
    
    cout << "    ██████╗ ██╗   ██╗███████╗██████╗ ██╗\n";
    cout << "   ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║\n";
    cout << "   ██║   ██║██║   ██║█████╗  ██████╔╝██║\n";
    cout << "   ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚═╝\n";
    cout << "   ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║██╗\n";
    cout << "    ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝\n";
    
    setColor(7);
    cout << endl << endl;
    
    // ═══════════════════ LOSER ANNOUNCEMENT ═══════════════════
    setColor(12); // Red
    cout << "  💀 Player " << loser << " lost!\n";
    setColor(7);
    cout << endl;
    
    // ═══════════════════ SCORE DISPLAY ═══════════════════
    setColor(14); // Yellow
    cout << "╔════════════════════════════════════╗\n";
    cout << "║                                    ║\n";
    
    cout << "║        ";
    setColor(11); // Cyan
    cout << "🏆 FINAL SCORES 🏆";
    setColor(14);
    cout << "          ║\n";
    
    cout << "║                                    ║\n";
    cout << "║  Player 1: ";
    setColor(15); // White
    printf("%06d", score1);
    setColor(14);
    cout << "               ║\n";
    
    cout << "║  Player 2: ";
    setColor(15);
    printf("%06d", score2);
    setColor(14);
    cout << "               ║\n";
    
    cout << "║                                    ║\n";
    cout << "╚════════════════════════════════════╝\n";
    
    cout << endl;
    
    // ═══════════════════ PLAY AGAIN PROMPT ═══════════════════
    setColor(12); // Red
    cout << "╔════════════════════════════════════╗\n";
    cout << "║                                    ║\n";
    cout << "║    ";
    setColor(14);
    cout << "Press [ENTER] to play again";
    setColor(12);
    cout << "     ║\n";
    
    cout << "║    ";
    setColor(14);
    cout << "Press [Q] to quit";
    setColor(12);
    cout << "               ║\n";
    
    cout << "║                                    ║\n";
    cout << "╚════════════════════════════════════╝\n";
    
    setColor(7);
    cout << endl;
    
    showCursor();
}

// Drawing the Grid along with both Snakes on the terminal
void GameGrid::drawGameGrid(const Snake& snake1, const Snake& snake2, const Food& food, int score1, int score2){
	setCursorPosition(0, 0);
	hideCursor();


	setColor(14);
	cout << "╔═══════════════════════════════════════════╗\n"
         << "║       ✨ 🐍 S N A K E   G A M E 🐍 ✨     ║\n"
         << "║       ✨ 🐍    by SnakeByte++   🐍 ✨     ║\n"
         << "╠═══════════════════════════════════════════╣\n"
         << "║  💚 P1: ";
    
    setColor(15);
    printf("%05d", score1);
    
    setColor(14);
    cout << "   │  🟡 P2: ";
    setColor(15);
    printf("%05d", score2);
    setColor(14);
    cout << "      ║\n"
         << "╠═══════════════════════════════════════════╣\n"
         << "║  🎮 P1:[↑↓←→]  P2:[W][A][S][D]  [X]:EXIT ║\n"
         << "╠═══════════════════════════════════════════╣\n"
         << "║  💡 TIP: Eat 🍎 apples to grow & score!   ║\n"
         << "║  ⚠️ WARNING: Don't hit 🧱 walls           ║\n"
         << "║              or 🐍🟢 yourself             ║\n"
		 << "╚═══════════════════════════════════════════╝\n" 
         << flush;
    
    setColor(7); // Reset


	// setColor(14); // Yellow
	// cout << "╔════════════════════════════════════════════╗\n";
	
	// cout << "║       ";
	// cout << "✨ 🐍 S N A K E   G A M E 🐍 ✨";
	// cout << "	     ║\n";
	
	// setColor(14);
	// cout << "╠════════════════════════════════════════════╣\n";
	
	// cout << "║  💚 Score: ";
	// setColor(15); // White
	// printf("%05d", score);
	
	// setColor(14);
	// cout << "   ║     ";
	// setColor(10);
	// cout << "🧭 Dir: ";
	// setColor(15);
	// cout << snake.getDirection() << "     ";
	// setColor(14);
	// cout << "    ║\n";

	// setColor(14);
	// cout << "╠════════════════════════════════════════════╣\n";

	// cout << "║  🎮 [W] UP [A] LEFT [S] DOWN [D] RIGHT  ";
	// cout << "   ║\n";
	
	// cout << "╚════════════════════════════════════════════╝\n";
	
	// setColor(7); // Reset
	// cout << endl;

//	clearScreen();
	// cout << "Score : " << score << "\t Current Direction : " << snake.getDirection() << endl;
	
//	Drawing the Top Boundry
//	The top left corner boundry
	cout << "🧱";

	
//	The top boundry
	for(int i = 0; i < width; ++i){
		cout << "🧱";

	} 
	
//	The top right corner boundry
	cout << "🧱";

	cout << endl;
	
	for(int i = 0; i < height; i++){
//		The left boundry
		cout << "🧱";

		
//		The game area
		for(int j = 0; j < width; j++){
			bool isDrawn = false;
			
//			Rendering Snake 1 in the grid
			for(size_t k = 0; k < snake1.getSnakeBody().size(); ++k){
				const Point& point = snake1.getSnakeBody()[k];
				
				if(j == point.x && i == point.y){
					std::cout << (k == 0 ? "🐍" : "🟢");
					
					isDrawn = true;
					break;
				}
			}

//			Rendering Snake 2 in the grid
			if(!isDrawn){
				for(size_t k = 0; k < snake2.getSnakeBody().size(); ++k){
					const Point& point = snake2.getSnakeBody()[k];
					
					if(j == point.x && i == point.y){
						std::cout << (k == 0 ? "🦊" : "🟡");
						
						isDrawn = true;
						break;
					}
				}
			}
			
//			Drawing the other empty spaces
			if(!isDrawn && j == food.getPosition().x && i == food.getPosition().y){
				cout << "🍎";
				isDrawn = true;
			}
			// if(!isDrawn){
			// 	cout << "⬛";;
			// }

			if(!isDrawn){

                #ifdef _WIN32
                    // Diagonal pattern for visual interest
                    if((i + j) % 3 == 0) {
                        setColor(8);
                        cout << "◾"; // Small square
                    } else if((i + j) % 3 == 1) {
                        setColor(8);
                        cout << "▪️"; // Tiny square
                    } else {
                        setColor(0);
                        cout << "⬛"; // Large square
                    }
                    setColor(7);

                #else 
                    setColor(8);
                    cout << "◾";
                #endif
			}
            
		
//		The right boundry
		cout << "🧱";

		
		cout << endl;
	}
	
//	Drawing the bottom boundry

//	The bottom left corner boundry
	cout << "🧱";

	
//	The bottom boundry
	for(int i = 0; i < width; ++i){
		cout << "🧱";
	} 
	
//	The bottom right corner boundry
	cout << "🧱";
	// cout << endl;

	
}
