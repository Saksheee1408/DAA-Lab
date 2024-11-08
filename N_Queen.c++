#include <iostream>
using namespace std;
#define N 8

void printSolution(int board[N][N]) {
    for (int i = 0; i < N; i++) 
    {
        for (int j = 0; j < N; j++) 
        {
            cout << (board[i][j] ? "Q" : ".");
        }
        cout << endl;
    }
    cout << endl;
}

bool isSafe(int board[N][N], int row, int col) {
    // Check this row on the left side
    for (int i = 0; i < col; i++) {
        if (board[row][i]) return false;
    }
    // Check the upper diagonal on the left side
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j]) return false;
    }
    // Check the lower diagonal on the left side
    for (int i = row, j = col; i < N && j >= 0; i++, j--) {
        if (board[i][j]) return false;
    }
    return true;
}

bool solveNQ(int board[N][N], int col) {
    // Base case: If all queens are placed
    if (col >= N) return true;

    // Try placing this queen in all rows in the current column
    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;  // Place queen

            // Recur to place the rest of the queens
            if (solveNQ(board, col + 1)) return true;

            // If placing queen here doesn't lead to a solution, backtrack
            board[i][col] = 0;
        }
    }
    return false;
}

bool solve() {
    int board[N][N] = {0};  // Initialize the board with 0s

    if (!solveNQ(board, 0)) {
        cout << "Solution does not exist" << endl;
        return false;
    }

    printSolution(board);  // Print the solution if one exists
    return true;
}

int main() {
    solve();
    return 0;
}
