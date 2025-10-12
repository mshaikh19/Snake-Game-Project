#include <iostream>
#include <vector>
using namespace std;

struct Point {
    int x, y;
};

class Snake {
    vector<Point> body;
    int gridWidth, gridHeight;

public:
    Snake(int w, int h, int startX, int startY, int length = 3)
        : gridWidth(w), gridHeight(h) {
        for (int i = 0; i < length; ++i) {
            body.push_back({startX - i, startY});
        }
    }

    void move(char direction, bool grow = false) {
        Point newHead = body[0];
        switch (direction) {
            case 'U': newHead.y--; break;
            case 'D': newHead.y++; break;
            case 'L': newHead.x--; break;
            case 'R': newHead.x++; break;
        }
        body.insert(body.begin(), newHead);
        if (!grow)
            body.pop_back();
    }

    bool isCollision() const {
        const Point& head = body[0];
        if (head.x < 0 || head.x >= gridWidth || head.y < 0 || head.y >= gridHeight)
            return true;
        for (int i = 1; i < body.size(); ++i)
            if (body[i].x == head.x && body[i].y == head.y)
                return true;
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

