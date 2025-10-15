#include "snake.h"

Snake::Snake(int startX, int startY) {
    x = startX;
    y = startY;
    tailLength = 0;
}

void Snake::move(int dx, int dy) {
    // Move tail segments
    for (int i = tailLength - 1; i > 0; i--) {
        tailX[i] = tailX[i - 1];
        tailY[i] = tailY[i - 1];
    }
    if (tailLength > 0) {
        tailX[0] = x;
        tailY[0] = y;
    }
    // Move head
    x += dx;
    y += dy;
}

void Snake::grow() {
    tailLength++;
}

int Snake::getX() const {
    return x;
}

int Snake::getY() const {
    return y;
}

int Snake::getTailLength() const {
    return tailLength;
}

int Snake::getTailX(int index) const {
    return tailX[index];
}

int Snake::getTailY(int index) const {
    return tailY[index];
}

