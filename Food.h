#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"
#include <vector>

using namespace std;

class Food {
private:
	Point position;
public:
    Food();
    
    void randomFoodPosition(const vector<Point>& snakeBody);
    
    
    Point getPosition() const{
    	return position;
	}
};

#endif
