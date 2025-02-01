# Tic Tac Toe Game

This is a simple command-line Tic Tac Toe game implemented in C using a combination of stacks, queues, and linked lists. The game supports two players (Player X and Player O), and allows players to make moves on a 3x3 grid, undo their last move, and check for a winner or a draw.

## Features

1. **Undo Move**: Players can undo their last move by entering the command 'u'.
2. **Board Display**: The game board is displayed after each move.
3. **Win Check**: The game automatically checks for a win after each move.
4. **Draw Condition**: If all cells are filled and no player wins, the game ends in a draw.
5. **Command-line Interface**: Players interact with the game via the terminal using cell numbers.

## Requirements

- A C compiler (e.g., GCC) to compile the code.

## Files in the Project

- **tic_tac_toe.c**: The main C file containing the implementation of the game.
- **README.md**: This README file.

## Code Structure

1. **Queue Implementation**: 
   - The queue is used to track the sequence of moves made by players.
   
2. **Stack Implementation**:
   - The stack stores move history to support the undo functionality.
   
3. **Game Logic**:
   - The `playGame` function handles the core game loop.
   - The `checkWin` function checks if a player has won after each move.
   - The `displayBoard` function shows the current state of the board.

4. **Game Features**:
   - Players take turns marking a cell on the 3x3 grid by entering the corresponding cell number.
   - Players can undo their last move by typing 'u'.
   - The game detects if a player has won or if the game results in a draw.

## How to Compile and Run

1. **Compile the Code**:
   Use a C compiler such as `gcc`:
   ```bash
   gcc TicTacToe.c -o TicTacToe
