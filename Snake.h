#ifndef SNAKE_H
#define SNAKE_H

class Snake {
private:
    int x, y;
    int tailX[100], tailY[100];
    int tailLength;
public:
    Snake(int startX, int startY);
    void move(int dx, int dy);
    void grow();
    int getX() const;
    int getY() const;
    int getTailLength() const;
    int getTailX(int index) const;
    int getTailY(int index) const;
};

#endif

