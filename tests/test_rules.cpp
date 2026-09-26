#include <iostream>
#include <cassert>
#include <vector>
#include "../Snake.h"
#include "../Food.h"

// Rule 1: Snake dies when its head enters its own body
void test_rule1_self_collision() {
    // Create snake of length 5 at (5, 5) heading Right ('D')
    // Body starts at: (5,5), (4,5), (3,5), (2,5), (1,5)
    Snake snake(5, 5, 5, 20, 20);
    
    // Move Up ('W'): head -> (5,4)
    snake.move('W');
    assert(!snake.isCollision());

    // Move Left ('A'): head -> (4,4)
    snake.move('A');
    assert(!snake.isCollision());

    // Move Down ('S'): head -> (4,5), which collides with body segment at (4,5)
    snake.move('S');
    assert(snake.isCollision() && "Rule 1 test failed: Snake should collide with itself!");
    std::cout << "[PASS] Rule 1: Snake dies when its head enters its own body\n";
}

// Rule 2: Snake dies when its head leaves the board
void test_rule2_boundary_collision() {
    // Create snake near top edge at (5, 0) in a 20x20 grid (initial dir 'D')
    Snake snake(5, 0, 2, 20, 20);

    // Move Up ('W'): head -> (5, -1), which is out of bounds (y < 0)
    snake.move('W');
    assert(snake.isCollision() && "Rule 2 test failed: Snake should collide with boundary!");
    std::cout << "[PASS] Rule 2: Snake dies when its head leaves the board\n";
}

// Rule 4: Fruit never appears on a cell occupied by the snake
void test_rule4_food_not_on_snake() {
    Snake snake(10, 10, 5, 20, 20);
    Food food(20, 20);

    // Generate random food position multiple times to test invariant
    for (int i = 0; i < 50; ++i) {
        food.randomFoodPosition(snake.getSnakeBody());
        Point fPos = food.getPosition();

        for (const auto& segment : snake.getSnakeBody()) {
            assert(!(segment.x == fPos.x && segment.y == fPos.y) && "Rule 4 test failed: Food placed on snake segment!");
        }
    }
    std::cout << "[PASS] Rule 4: Fruit never appears on a cell occupied by the snake\n";
}

#include "../InputSource.h"

class StubInputSource : public InputSource {
private:
    std::vector<char> inputs;
    size_t index = 0;
public:
    StubInputSource(const std::vector<char>& keys) : inputs(keys) {}

    bool hasInput() override {
        return index < inputs.size();
    }

    char getInput() override {
        if (index < inputs.size()) {
            return inputs[index++];
        }
        return 0;
    }
};

// Rule 5: Player steers with W/A/S/D; X quits
void test_rule5_player_steering_and_quit() {
    char direction = 'D';
    StubInputSource inputSource({'w', 'a', 'x'});

    // Process first input 'w' -> direction changes to 'W'
    bool continueGame = processGameInput(inputSource, direction);
    assert(continueGame == true && "Rule 5 test failed: 'w' key should continue game!");
    assert(direction == 'W' && "Rule 5 test failed: 'w' key should set direction to 'W'!");

    // Process second input 'a' -> direction changes to 'A'
    continueGame = processGameInput(inputSource, direction);
    assert(continueGame == true && "Rule 5 test failed: 'a' key should continue game!");
    assert(direction == 'A' && "Rule 5 test failed: 'a' key should set direction to 'A'!");

    // Process third input 'x' -> signals quit (false)
    continueGame = processGameInput(inputSource, direction);
    assert(continueGame == false && "Rule 5 test failed: 'x' key should signal quit!");

    std::cout << "[PASS] Rule 5: Player steers with W/A/S/D; X quits\n";
}

int main() {
    std::cout << "--- Running Unit Tests ---\n";
    test_rule1_self_collision();
    test_rule2_boundary_collision();
    test_rule4_food_not_on_snake();
    test_rule5_player_steering_and_quit();
    std::cout << "--- All unit tests PASSED ---\n";
    return 0;
}
