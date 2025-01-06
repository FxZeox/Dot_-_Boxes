# Dots and Boxes Game

This is a simple implementation of the **Dots and Boxes** game in C++. 
It allows two players to play on a customizable board where they take turns drawing lines between adjacent dots to form boxes. 
The player who completes a box earns a point, and the game continues until all possible boxes are completed.

## Game Rules

1. Players take turns drawing a single horizontal or vertical line between two unconnected adjacent dots.
2. If a player completes a box by drawing the final line, they earn a point and take another turn.
3. The game ends when all boxes have been completed.
4. The player with the most boxes at the end of the game wins.

## Features

- Supports board sizes from **2x2** to **8x8**.
- Interactive gameplay for two players, switching turns automatically.
- Colored output to differentiate between the two players (Player A and Player B).
- Basic input validation to prevent invalid moves.

## Getting Started

### Prerequisites

To compile and run this game, you will need:

- A C++ compiler (e.g., `g++`)


### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/dots-and-boxes.git
   cd dots-and-boxes

    Compile the code:

   g++   dots_and_boxes.cpp  -o dots_and_boxes

Run the game:

    ./dots_and_boxes

Gameplay

    You will be prompted to enter the size of the board. Choose a value between 2 and 8.
    Players will take turns entering their moves in the format r1 c1 r2 c2, where:
        (r1, c1) and (r2, c2) represent the coordinates of the dots you want to connect.
        Example: 1 2 1 3 will draw a horizontal line between the dots (1, 2) and (1, 3).
    If a player completes a box, they earn a point and take another turn.
    The game ends when all boxes are completed.

Sample Game Interaction


Choose board size (2-8): 3
--Dots and Boxes Game--

              0   1   2   3  
           0  *   *   *   *  
              |   |   |   |  
           1  *   *   *   *  
              |   |   |   |  
           2  *   *   *   *  
              |   |   |   |  
           3  *   *   *   *  

Player A, enter your move (r1 c1 r2 c2) or 'q' to quit: 0 0 0 1
Player B, enter your move (r1 c1 r2 c2) or 'q' to quit: 0 1 0 2
...
Game Over! Player A: 2 points, Player B: 1 points.
Player A wins!

Exit the Game

    To exit the game at any time, enter q when prompted for a move.

Code Overview

    Board Representation: The board is represented using a 2D array of characters for dots and a 2D array of booleans for lines.
    Line Placement: Horizontal and vertical lines are tracked separately to check if a box is completed.
    Game Flow: The game alternates between Player A and Player B, allowing them to input moves until the game is over.
    Score Tracking: Each player's score is updated when they complete a box.
