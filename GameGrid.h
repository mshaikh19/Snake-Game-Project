#ifndef GAMEGRID_H
#define GAMEGRID_H

class GameGrid {
private:
    int width, height;
public:
    GameGrid(int w, int h);
    int getWidth() const;
    int getHeight() const;
    void drawGrid();
};

#endif

