#ifndef FOOD_H
#define FOOD_H

#include "Snake.h"
#include <vector>


class Food {
private:
    int gridWidth;
    int gridHeight;
    Point position;
public:
    Food(int width, int height);
    void randomFoodPosition(const vector<Point>& snakeBody);

    Point getPosition() const {
        return position;
    }
};

#endif
