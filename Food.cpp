#include "Food.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Food::Food(int width, int height) 
	: gridHeight(height), gridWidth(width) {
    static bool seeded = false;

	if (!seeded) {
		
        // Initialize the random number generator using the current time.
        srand(static_cast<unsigned int>(time(0)));
        
        // Set the flag to true so this block is skipped next time.
        seeded = true;
    }
}

void Food::randomFoodPosition(const vector<Point>& snakeBody) {
	Point newPosition;
	bool placed = false;
	
	while(!placed){
    	newPosition.x = rand() % gridWidth;
    	newPosition.y = rand() % gridHeight;
    	
    	bool onSnake = false;
    	
//    	Checking if the food overlaps with the snake
		for(const auto& segment : snakeBody){
			if(segment.x == newPosition.x && segment.y == newPosition.y){
				onSnake = true;
				break;
			}
		}
		
		if(!onSnake){
			position = newPosition;
			placed = true;
		}
	}
}

//int Food::getX() const {
//    return newPosition.x;
//}
//
//int Food::getY() const {
//    return newPosition.y;
//}
