#include "sudoku.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 9 // Sudoku grid size

int main() {
    Sudoku game;
    game.generateFullSudoku();
    game.saveToFile("sudoku_solution.txt");

    int difficulty;
    cout << "Select Difficulty Level:\n";
    cout << "1. Easy\n2. Medium\n3. Hard\n";
    cout << "Enter your choice (1-3): ";
    cin >> difficulty;

    if (difficulty < 1 || difficulty > 3) {
        cout << "Invalid choice! Defaulting to Medium difficulty.\n";
        difficulty = 2;
    }

    game.removeNumbers(difficulty);
    game.saveToFile("sudoku_puzzle.txt");

    cout << "A new Sudoku puzzle has been generated with difficulty level " << difficulty << ".\n";
    return 0;
}
