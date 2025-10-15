#include "gamegrid.h"
#include <iostream>

GameGrid::GameGrid(int w, int h) : width(w), height(h) {}

int GameGrid::getWidth() const {
    return width;
}

int GameGrid::getHeight() const {
    return height;
}

void GameGrid::drawGrid() {
    for (int i = 0; i < width+2; i++) std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        std::cout << "#";
        for (int j = 0; j < width; j++) {
            std::cout << " ";
        }
        std::cout << "#" << std::endl;
    }

    for (int i = 0; i < width+2; i++) std::cout << "#";
    std::cout << std::endl;
}

