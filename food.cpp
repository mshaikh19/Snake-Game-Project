#include "food.h"
#include <cstdlib>
#include <ctime>

Food::Food(int width, int height) : gridWidth(width), gridHeight(height) {
    std::srand(std::time(0));
    generateNewPosition();
}

void Food::generateNewPosition() {
    x = std::rand() % gridWidth;
    y = std::rand() % gridHeight;
}

int Food::getX() const {
    return x;
}

int Food::getY() const {
    return y;
}
