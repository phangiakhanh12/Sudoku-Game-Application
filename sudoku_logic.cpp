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
    Sudoku() {
        board = vector<vector<int>>(N, vector<int>(N, 0));
    }

    bool isValid(int row, int col, int num) {
        for (int i = 0; i < N; i++) {
            if (board[row][i] == num || board[i][col] == num) {
                return false;
            }
        }

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

    bool solve() {
        for (int row = 0; row < N; row++) {
            for (int col = 0; col < N; col++) {
                if (board[row][col] == 0) {
                    for (int num = 1; num <= 9; num++) {
                        if (isValid(row, col, num)) {
                            board[row][col] = num;
                            if (solve()) return true;
                            board[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    void generateFullSudoku() {
        srand(time(0));

        for (int i = 0; i < N; i++) {
            int num = (rand() % 9) + 1;
            int row = rand() % N;
            int col = rand() % N;
            while (board[row][col] != 0) {
                row = rand() % N;
                col = rand() % N;
            }
            if (isValid(row, col, num)) {
                board[row][col] = num;
            }
        }

        solve();
    }

    void removeNumbers(int difficulty) {
        int attempts;
        if (difficulty == 1) {
            attempts = 20; // Easy
        } else if (difficulty == 2) {
            attempts = 30; // Medium
        } else {
            attempts = 40; // Hard
        }

        while (attempts > 0) {
            int row = rand() % N;
            int col = rand() % N;
            if (board[row][col] != 0) {
                board[row][col] = 0;
                attempts--;
            }
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                file << board[i][j] << " ";
            }
            file << endl;
        }
        file.close();
    }
};

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
