#ifndef SUDOKU_H
#define SUDOKU_H

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

#define N 9 // Sudoku grid size

class Sudoku {
private:
    vector<vector<int>> board;

public:
    // Constructor
    Sudoku();

    // Function to check if a number is valid at the given position
    bool isValid(int row, int col, int num);

    // Function to solve the Sudoku puzzle using backtracking
    bool solve();

    // Function to generate a full Sudoku puzzle
    void generateFullSudoku();

    // Function to remove numbers from the generated Sudoku puzzle based on difficulty
    void removeNumbers(int difficulty);

    // Function to save the Sudoku board to a file
    void saveToFile(const string& filename);
};

#endif // SUDOKU_H
