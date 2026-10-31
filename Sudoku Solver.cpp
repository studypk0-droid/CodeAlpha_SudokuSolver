#include <iostream>

using namespace std;

#define N 9

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    for (int r = 0; r < N; r++) {
        for (int c = 0; c < N; c++)
            cout << grid[r][c] << " ";
        cout << endl;
    }
}

// Function to check if a number can be placed safely
bool isSafe(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int d = 0; d < N; d++)
        if (grid[row][d] == num)
            return false;

    // Check column
    for (int r = 0; r < N; r++)
        if (grid[r][col] == num)
            return false;

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++)
        for (int d = 0; d < 3; d++)
            if (grid[r + startRow][d + startCol] == num)
                return false;

    return true;
}

// Backtracking function to solve Sudoku
bool solveSudoku(int grid[N][N], int row, int col) {
    // If we reach the end of the grid, it's solved
    if (row == N - 1 && col == N)
        return true;

    // Move to the next row if column reaches N
    if (col == N) {
        row++;
        col = 0;
    }

    // If cell already has a number, move to next column
    if (grid[row][col] != 0)
        return solveSudoku(grid, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            
            // Recurse for the next cell
            if (solveSudoku(grid, row, col + 1))
                return true;
        }
        // Backtrack if the number doesn't lead to a solution
        grid[row][col] = 0;
    }
    return false;
}

int main() {
    // Sample Sudoku puzzle (0 represents empty cells)
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    cout << "Original Sudoku Grid:\n";
    printGrid(grid);
    cout << "\n---------------------\n\n";

    if (solveSudoku(grid, 0, 0)) {
        cout << "Solved Sudoku Grid:\n";
        printGrid(grid);
    } else {
        cout << "No solution exists for this Sudoku.\n";
    }

    return 0;
}