#include <iostream>
#include <vector>
using namespace std;

// Initialize the Snake with initial direction and length
Snake::Snake(int width, int height, int startX, int startY, int length = 3)
    : currentDirection('D') {
    for (int i = 0; i < length; ++i) {
        body.push_back({startX - i, startY});
    }
}

// Set Direction of the snake according to the user input 
void Snake::setDirection(char newDirection){
	char snakeDirection = 0;
	
	if (newDirection == 'w' || newDirection == 'W') {
        snakeDirection = 'W';
    } else if (newDirection == 's' || newDirection == 'S') {
        snakeDirection = 'S';
    } else if (newDirection == 'a' || newDirection == 'A') {
        snakeDirection = 'A';
    } else if (newDirection == 'd' || newDirection == 'D') {
        snakeDirection = 'D';
    } else if (newDirection == 'q' || newDirection == 'Q') {
        // Quit Game Handling
        gameOver = true;
    } else {
        gameOver = true;
    }
	
	if ((snakeDirection == 'W' && currentDirection == 'S') ||
        (snakeDirection == 'S' && currentDirection == 'W') ||
        (snakeDirection == 'A' && currentDirection == 'D') ||
        (snakeDirection == 'D' && currentDirection == 'A'))
    {
        return;
    }
    currentDirection = snakeDirection;
}

Snake::void move(char direction, bool grow = false) {
	setDirection(direction);
    Point newHead = body[0];
    
//	Determine the position of the head based on the input of the user 
    switch (currenrDirection) {
        case 'W': newHead.y--; break;
        case 'S': newHead.y++; break;
        case 'A': newHead.x--; break;
        case 'D': newHead.x++; break;
    }
    
//  Adding the new head in front of the body of the snake
    body.insert(body.begin(), newHead);
    
//  Removing the tail in case the snake is not growing
    if (!grow){
        body.pop_back();
	}
}

Snake::bool isCollision() const {
    const Point& head = body[0];
    
//  Check the collision of the snake with the boundry
    if (head.x < 0 || head.x >= gridWidth || head.y < 0 || head.y >= gridHeight){
        return true;
	}
	
//	Check collision of the snake with itself
    for (int i = 1; i < body.size(); ++i){
        if (body[i].x == head.x && body[i].y == head.y){
            return true;
		}
	}
    return false;
}

    void draw() const {
        cout << "|";
        for (int i = 0; i < gridWidth; ++i) cout << "-";
        cout << "|\n";

        for (int y = 0; y < gridHeight; ++y) {
            cout << "|";
            for (int x = 0; x < gridWidth; ++x) {
                if (x == body[0].x && y == body[0].y) {
                    cout << "@";  // head
                } else {
                    bool isBody = false;
                    for (int k = 1; k < body.size(); ++k) {
                        if (body[k].x == x && body[k].y == y) {
                            cout << "o";  // body
                            isBody = true;
                            break;
                        }
                    }
                    if (!isBody)
                        cout << ".";
                }
            }
            cout << "|\n";
        }

        cout << "|";
        for (int i = 0; i < gridWidth; ++i) cout << "-";
        cout << "|\n";
    }
};

int main() {
    const int width = 20, height = 10;
    Snake snake(width, height, width / 2, height / 2);

    snake.draw();  // initial draw

    snake.move('R');
    snake.draw();

    snake.move('D');
    snake.draw();

    snake.move('L', true);  // grow
    snake.draw();

    if (snake.isCollision()) {
        cout << "Collision detected!\n";
    } else {
        cout << "No collision.\n";
    }
}