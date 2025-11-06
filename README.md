# Snake-Game-Project🐍
Building a Snake Game for C++ Project.

## Description

This project is a classic Snake game implemented in C++ for the console environment. The objective is to maneuver a growing snake around the game grid, collect food items to gain points, and avoid collisions with the walls or the snake's own body. This project demonstrates fundamental programming concepts including game logic, input handling, and data structures.

## Features

- Responsive console-based gameplay
- Dynamic snake growth upon eating food
- Random food 🍎 placement on the grid.
- Collision detection (walls 🧱 and self 🐍).
- Simple and modular code architecture

## Screenshots

Here is a preview of the game in action:

### Windows 

<img width="1920" height="1080" alt="Screenshot (768)" src="https://github.com/user-attachments/assets/48a2cda9-440b-4724-ba1e-48c7e2bac460" />
<img width="1920" height="1080" alt="Screenshot (769)" src="https://github.com/user-attachments/assets/8774bccf-d61c-4f08-81d0-52f505fca04f" />
<img width="1920" height="1080" alt="Screenshot (767)" src="https://github.com/user-attachments/assets/eed7216d-0539-4e40-95bd-fb815a3167a5" />


### Ubuntu

![WhatsApp Image 2025-11-06 at 16 19 53_5c227443](https://github.com/user-attachments/assets/31645aef-d780-4659-aa8b-eb6f6200e39f)
![WhatsApp Image 2025-11-06 at 16 19 53_57d8f208](https://github.com/user-attachments/assets/ae8764ec-b48a-44fb-bb19-e50d26c2fd94)
![WhatsApp Image 2025-11-06 at 16 19 44_a024c202](https://github.com/user-attachments/assets/83f0487a-1f5b-4aea-8726-dcc6e6428cb0)




## Controls
Move the snake using the following keys:
  - W (UP) ⬆️
  - A (LEFT) ⬅️
  - S (DOWN) ⬇️
  - D (RIGHT) ➡️

Press the respective keys during gameplay to control the snake’s movement.

## How It Works
The game runs directly in your system’s terminal or command prompt.
It uses basic console functions to render the grid, move the snake, and process keyboard input.
Each time the snake eats food:
  - The score increases 
  - The snake grows longer 🐍🟢
  - A new food item appears at a random position 🍎
The game ends if the snake hits a wall 🧱 or itself 🐍.

## Technologies Used

- C++ (Standard Library)
- Console input/output for game interaction

## Requirements

To run this project on your PC, you need:

- A modern operating system (Windows / Ubuntu)
- A C++ compiler supporting C++11 or later (e.g., g++, clang++, MSVC)
- Command line/terminal access to compile and run the executable
- MinGW (If you don't have MinGW installed, you can download it from [MinGW-w64](https://sourceforge.net/projects/mingw-w64/) and follow the installation instructions to set up the GCC compiler on your system).
- Basic familiarity with command line usage for compilation and execution

## Compilation and Execution Instructions

Follow these steps to run the project:
```
  g++ -c Snake.cpp -o Snake.o
  g++ -c Food.cpp -o Food.o
  g++ -c GameGrid.cpp -o GameGrid.o
  g++ -c SnakeGame.cpp -o SnakeGame.o

  g++ Snake.o Food.o GameGrid.o SnakeGame.o -o SnakeGame

  ./SnakeGame
```
or 
` SnakeGame.exe ` (For Windows)



  
## Future Improvements
  - Add increasing difficulty or speed levels
  - Add sound effects during gameplay
  - Include a high-score leaderboard

## Acknowledgments

- Inspired by the classic Snake game
- Developed as an educational project for learning C++ and game programming concepts
- Thanks to the C++ open-source community and relevant tutorials
