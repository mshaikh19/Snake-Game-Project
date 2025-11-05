#ifndef GAME_GRID_H
#define GAME_GRID_H

#include <iostream>
#include "Snake.h"
#include "Food.h"

class Snake;


class GameGrid{
	private:
		int width;
		int height;
		void setCursorPosition(int x, int y);
	public:
		GameGrid(int width, int height);
		
		int getWidth() const;
		int getHeight() const;
		
//		Draw Empty Grid
		void drawGameGrid();
		void clearScreen();
		// void drawHeader(int score, char direction);
		// void drawFooter();
		void showGameOver(int finalScore);
		void showCursor();
//		Draw grid along with the snake and the score
		void drawGameGrid(const Snake& snake, const Food& food, int score);
		
		
};

#endif
