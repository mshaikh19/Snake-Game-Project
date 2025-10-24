#ifndef GAME_GRID_H
#define GAME_GRID_H

#include <iostream>
#include "Snake.h"
#include "Food.h"

class Snake;

extern const int gridHeight;
extern const int gridWidth;

class GameGrid{
	private:
		int width;
		int height;
		
		void clearScreen();
		
	public:
		GameGrid(int width, int height);
		
		int getWidth() const;
		int getHeight() const;
		
//		Draw Empty Grid
		void drawGameGrid();
		
//		Draw grid along with the snake and the score
		void drawGameGrid(const Snake& snake, const Food& food, int score);
		
		
};

#endif