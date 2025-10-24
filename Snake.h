#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
using namespace std;

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
    
    bool isCollision() const;
    
    const vector<Point>& getSnakeBody() const{
    	return body;
	}
	char getDirection() const{
		return currentDirection;
	}
    
};


#endif