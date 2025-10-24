#include "GameGrid.h"
#include "Snake.h"

#include <vector>

using namespace std;

// Grid of NxN is defined
const int gridHeight = 10;
const int gridWidth = 20;

// Clear the whole terminal screen for a cleaner look
void clearScreen(){
	#ifdef _WIN32
        system("cls");
    #endif
}

// Drawing the Grid along with the initial position of the Snake on the terminal
void drawGameGrid(const Snake& snake, int score){
	
	clearScreen();
	cout << "Score : " << score << "\t Current Direction : " << snake.getDirection() << endl;
	
//	Drawing the Top Boundry
//	The top left corner boundry
	cout << "|";
	
//	The top boundry
	for(int i = 0; i < gridWidth; ++i){
		cout << "-";
	} 
	
//	The top right corner boundry
	cout << "|";
	cout << endl;
	
//	Drawing the Game Area
	for(int i = 0; i < gridHeight; i++){
//		The left boundry
		cout << "|";
		
//		The game area
		for(int j = 0; j < gridWidth; j++){
			bool isDrawn = false;
			
//			Rendering the Snake in the grid
			for(size_t k = 0; k < snake.getBody().size(); ++k)			
			
			cout << ".";
		}
		
//		The right boundry
		cout << "|";
		
		cout << endl;
	}
	
//	Drawing the bottom boundry

//	The bottom left corner boundry
	cout << "|";
	
//	The bottom boundry
	for(int i = 0; i < gridWidth; ++i){
		cout << "-";
	} 
	
//	The bottom right corner boundry
	cout << "|";
	
	cout << endl;
}