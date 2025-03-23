#include "sudoku.h"
#include <iostream>
using namespace std;
// Constructor to initialize the board with all zeros
Sudoku::Sudoku() {
    board = vector<vector<int>>(N, vector<int>(N, 0));
}

// Function to check if a number is valid at the given position
bool Sudoku::isValid(int row, int col, int num) {
    // Check the row and column for the same number
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num || board[i][col] == num) {
            return false;
        }
    }

    // Check the 3x3 sub-grid for the same number
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

// Function to solve the Sudoku puzzle using backtracking
bool Sudoku::solve() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 0) {  // Find an empty cell
                for (int num = 1; num <= 9; num++) {
                    if (isValid(row, col, num)) {
                        board[row][col] = num;  // Try placing the number
                        if (solve()) return true;  // Recurse if successful
                        board[row][col] = 0;  // Backtrack if not successful
                    }
                }
                return false;  // If no number fits, return false
            }
        }
    }
    return true;  // Puzzle solved
}

// Function to generate a full Sudoku puzzle
void Sudoku::generateFullSudoku() {
    srand(time(0));  // Seed the random number generator

    // Randomly place numbers on the board
    for (int i = 0; i < N; i++) {
        int num = (rand() % 9) + 1;  // Random number between 1 and 9
        int row = rand() % N;        // Random row
        int col = rand() % N;        // Random column

        // Ensure the cell is empty before placing the number
        while (board[row][col] != 0) {
            row = rand() % N;
            col = rand() % N;
        }

        if (isValid(row, col, num)) {
            board[row][col] = num;  // Place the number if valid
        }
    }

    solve();  // Solve the board to ensure it is a valid puzzle
}

// Function to remove numbers based on difficulty level
void Sudoku::removeNumbers(int difficulty) {
    int attempts;
    if (difficulty == 1) {
        attempts = 20; // Easy
    } else if (difficulty == 2) {
        attempts = 30; // Medium
    } else {
        attempts = 40; // Hard
    }

    // Randomly remove numbers from the board
    while (attempts > 0) {
        int row = rand() % N;
        int col = rand() % N;
        if (board[row][col] != 0) {
            board[row][col] = 0;  // Remove the number
            attempts--;
        }
    }
}

// Function to save the current board to a file
void Sudoku::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                file << board[i][j] << " ";  // Write each number
            }
            file << endl;
        }
        file.close();  // Close the file after writing
    } else {
        cout << "Unable to open file for writing!" << endl;
    }
}
