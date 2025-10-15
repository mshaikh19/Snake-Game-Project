#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

extern const int gridHeight;
extern const int gridWidth;

struct Point{
	int x, y;	
};

class Snake {
private:
    vector<Point> body;
    char currentDirection;
public:
    Snake(int startX, int startY, int length);
    
    void setDirection(char newDirection);
    
	void move(char direction, bool grow = false);
    
    bool isCollision();
    
    const vector<Point>& getSnakeBody() {
    	return body;
	}
	char getDirection(){
		return currentDirection;
	}
    
};

#endif
