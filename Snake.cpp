using namespace std;
#include <iostream>
#include <vector>
#include "Snake.h"


// Initialize the Snake with initial direction and length
Snake::Snake(int startX, int startY, int length = 3)
    : currentDirection('D') {
    for (int i = 0; i < length; ++i) {
        body.push_back({startX - i, startY});
    }
}

// Set Direction of the snake according to the user input 
void Snake::setDirection(char newDirection){
	char snakeDirection = 0;
	
	if (newDirection == 'w' || newDirection == 'W') {
        snakeDirection = 'W';
    } else if (newDirection == 's' || newDirection == 'S') {
        snakeDirection = 'S';
    } else if (newDirection == 'a' || newDirection == 'A') {
        snakeDirection = 'A';
    } else if (newDirection == 'd' || newDirection == 'D') {
        snakeDirection = 'D';
    } else {
        return;
    }
	
	if ((snakeDirection == 'W' && currentDirection == 'S') ||
        (snakeDirection == 'S' && currentDirection == 'W') ||
        (snakeDirection == 'A' && currentDirection == 'D') ||
        (snakeDirection == 'D' && currentDirection == 'A'))
    {
        return;
    }
    currentDirection = snakeDirection;
}

Point Snake::move(char direction, bool grow) {
	setDirection(direction);
    Point newHead = body[0];
    
//	Determine the position of the head based on the input of the user 
    switch (currentDirection) {
        case 'W': newHead.y--; break;
        case 'S': newHead.y++; break;
        case 'A': newHead.x--; break;
        case 'D': newHead.x++; break;
    }
    
//  Store the old tail of the snake before it is removed
    Point oldTail = body.back();
    
//  Adding the new head in front of the body of the snake
    body.insert(body.begin(), newHead);
    
//  Removing the tail in case the snake is not growing
    if (!grow){
        body.pop_back();
	}
	
	return oldTail;
}

bool Snake::isCollision() const {
    const Point& head = body[0];
    
//  Check the collision of the snake with the boundry
    if (head.x < 0 || head.x >= gridWidth || head.y < 0 || head.y >= gridHeight){
        return true;
	}
	
//	Check collision of the snake with itself
    for (int i = 1; i < body.size(); ++i){
        if (body[i].x == head.x && body[i].y == head.y){
            return true;
		}
	}
    return false;
}
