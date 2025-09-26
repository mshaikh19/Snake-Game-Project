#include <iostream>
#include <vector>

using namespace std;


// Grid of NxN is defined
const int gridHeight = 10;
const int gridWidth = 20;

void drawGameGrid(){
	
//	Drawing the Top Boundry

//	The top left corner boundry
	cout << "|";
	
//	The top boundry
	for(int i = 0; i <= gridWidth; ++i){
		cout << "-";
	} 
	
//	The top right corner boundry
	cout << "|";
	
	cout << endl;
	
//	Drawing the Game Area
	for(int i = 0; i <= gridHeight; i++){
//		The left boundry
		cout << "|";
		
//		The game area
		for(int j = 0; j <= gridWidth; j++){
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
	for(int i = 0; i <= gridWidth; ++i){
		cout << "-";
	} 
	
//	The bottom right corner boundry
	cout << "|";
	
	cout << endl;
}

int main(){
	drawGameGrid();
}


