#include <iostream>
using namespace std;

// Function to solve the 0/1 Knapsack problem
int knapsack(int W, int weights[], int profits[], int n) {
    // Create a 2D array to store the maximum profit for each subproblem
    int dp[n + 1][W + 1];

    // Iterate over all items
    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0) {
                // Base case: if no item or no capacity, profit is 0
                dp[i][w] = 0;
            } else if (weights[i - 1] <= w) {
                // If the item can fit in the knapsack, choose the maximum profit
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + profits[i - 1]);
            } else {
                // Otherwise, don't include the item
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Return the maximum profit for the given capacity
    return dp[n][W];
}

int main() {
    int n;  // Number of items
    int W;  // Maximum capacity of the knapsack
    
    // Input number of items and maximum capacity
    cout << "Enter number of items: ";
    cin >> n;
    cout << "Enter the maximum capacity of the knapsack: ";
    cin >> W;
    
    int weights[n], profits[n];
    
    // Input weights and profits of the items
    cout << "Enter the weights of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> weights[i];
    }

    cout << "Enter the profits of the items: ";
    for (int i = 0; i < n; ++i) {
        cin >> profits[i];
    }
    
    // Call the knapsack function and display the result
    int maxProfit = knapsack(W, weights, profits, n);
    cout << "Maximum profit: " << maxProfit << endl;

    return 0;
}
