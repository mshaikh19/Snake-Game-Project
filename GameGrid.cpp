#include "GameGrid.h"
#include "Snake.h"
#include "Food.h"

#include <windows.h>
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

void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100; 
    info.bVisible = FALSE; 
    SetConsoleCursorInfo(consoleHandle, &info);
}

void GameGrid::setCursorPosition(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hConsole, pos);
}

// Set console text color
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
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

// Drawing the Grid along with the initial position of the Snake on the terminal
void GameGrid::drawGameGrid(const Snake& snake, const Food& food, int score){
	setCursorPosition(0, 0);
	hideCursor();


	setColor(14);
	cout << "╔═══════════════════════════════════════════╗\n"
         << "║       ✨ 🐍 S N A K E   G A M E 🐍 ✨     ║\n"
         << "╠═══════════════════════════════════════════╣\n"
         << "║  💚 Score: ";
    
    setColor(15);
    printf("%05d", score);
    
    setColor(14);
    cout << "   │     ";
    setColor(10);
    cout << "🧭 Dir: ";
    setColor(15);
    cout << snake.getDirection() << "     ";
    setColor(14);
    cout << "   ║\n"
         << "╠═══════════════════════════════════════════╣\n"
         << "║  🎮 [W] UP [A] LEFT [S] DOWN [D] RIGHT    ║\n"
         << "║              [X] EXIT                     ║\n"
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
			
//			Rendering the Snake in the grid
			for(size_t k = 0; k < snake.getSnakeBody().size(); ++k){
				const Point& point = snake.getSnakeBody()[k];
				
				if(j == point.x && i == point.y){
					std::cout << (k == 0 ? "🐍" : "🟢");
					
					isDrawn = true;
					break;
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
			}
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
