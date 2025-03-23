import tkinter as tk
from tkinter import messagebox

class SudokuGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Sudoku Game")

        self.attempts = 3  # Player gets 3 chances
        self.puzzle, self.solution = self.load_sudoku("sudoku_puzzle.txt", "sudoku_solution.txt")
        self.cells = [[None for _ in range(9)] for _ in range(9)]

        self.create_grid()
        self.create_buttons()

    def load_sudoku(self, puzzle_file, solution_file):
        def read_file(filename):
            with open(filename, "r") as f:
                return [list(map(int, line.split())) for line in f.readlines()]

        return read_file(puzzle_file), read_file(solution_file)

    def create_grid(self):
        for row in range(9):
            for col in range(9):
                value = self.puzzle[row][col]
                entry = tk.Entry(self.root, width=3, font=("Arial", 16), justify="center")

                if value != 0:
                    entry.insert(0, str(value))
                    entry.config(state="disabled")  # Pre-filled values are not editable

                entry.grid(row=row, column=col, padx=5, pady=5)
                self.cells[row][col] = entry

    def create_buttons(self):
        check_button = tk.Button(self.root, text="Check Solution", command=self.check_solution)
        check_button.grid(row=9, column=0, columnspan=4, pady=10)

        quit_button = tk.Button(self.root, text="Quit", command=self.root.quit)
        quit_button.grid(row=9, column=5, columnspan=4, pady=10)

    def check_solution(self):
        user_solution = [[int(self.cells[row][col].get()) if self.cells[row][col].get().isdigit() else 0
                          for col in range(9)] for row in range(9)]

        if user_solution == self.solution:
            messagebox.showinfo("Congratulations!", "You solved the Sudoku correctly!")
            self.root.quit()
        else:
            self.attempts -= 1
            if self.attempts > 0:
                messagebox.showwarning("Try Again", f"Incorrect solution! You have {self.attempts} attempts left.")
            else:
                messagebox.showinfo("Game Over", "You've used all attempts! Here is the correct solution.")
                self.show_solution()

    def show_solution(self):
        for row in range(9):
            for col in range(9):
                self.cells[row][col].config(state="normal")  # Allow editing to insert solution
                self.cells[row][col].delete(0, tk.END)
                self.cells[row][col].insert(0, str(self.solution[row][col]))
                self.cells[row][col].config(state="disabled")  # Lock it again after inserting

if __name__ == "__main__":
    root = tk.Tk()
    app = SudokuGUI(root)
    root.mainloop()
