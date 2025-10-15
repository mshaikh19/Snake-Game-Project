#ifndef FOOD_H
#define FOOD_H

class Food {
private:
    int x, y;
    int gridWidth, gridHeight;
public:
    Food(int gridWidth, int gridHeight);
    void generateNewPosition();
    int getX() const;
    int getY() const;
};

#endif

