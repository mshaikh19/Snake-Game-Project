#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
using namespace std;


struct Point{
	int x, y;	
};


class Snake {
	private:
	
	int gridHeight;
	int gridWidth;
    vector<Point> body;
    char currentDirection;
public:
    Snake(int startX, int startY, int length, int width, int height);
    
    void setDirection(char newDirection);
    
	Point move(char direction, bool grow = false);
    
    bool isCollision() const;
    
    const vector<Point>& getSnakeBody() const{
    	return body;
	}
	char getDirection() const{
		return currentDirection;
	}
};
#endif
