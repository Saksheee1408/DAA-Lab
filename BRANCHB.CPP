#include <iostream>
using namespace std;

const int MAX_ITEMS = 20;  // Maximum number of items we can handle

// Global variables
int bestSolution[MAX_ITEMS];  // To store best solution found
int maxValue = 0;            // Maximum value found so far

// Calculate bound for remaining items
int calculateBound(int values[], int weights[], int currentValue, 
                  int currentWeight, int capacity, int index, int n) {
    int boundValue = currentValue;
    int boundWeight = currentWeight;
    
    // Try to add remaining items
    for(int i = index; i < n; i++) {
        if(boundWeight + weights[i] <= capacity) {
            boundValue += values[i];
            boundWeight += weights[i];
        }
    }
    
    return boundValue;
}

// Recursive function to explore possibilities
void explore(int values[], int weights[], int currentSolution[], 
            int capacity, int currentValue, int currentWeight, 
            int index, int n) {
    // If we've reached the end
    if(index == n) {
        if(currentValue > maxValue) {
            maxValue = currentValue;
            // Save current solution
            for(int i = 0; i < n; i++) {
                bestSolution[i] = currentSolution[i];
            }
        }
        return;
    }
    
    // Calculate bound
    int bound = calculateBound(values, weights, currentValue, 
                             currentWeight, capacity, index, n);
    
    if(bound <= maxValue) {
        return;  // Skip if not promising
    }
    
    // Don't take current item
    explore(values, weights, currentSolution, capacity, 
           currentValue, currentWeight, index + 1, n);
    
    // Take current item if possible
    if(currentWeight + weights[index] <= capacity) {
        currentSolution[index] = 1;
        explore(values, weights, currentSolution, capacity,
               currentValue + values[index], 
               currentWeight + weights[index], 
               index + 1, n);
        currentSolution[index] = 0;  // Backtrack
    }
}

// Main function to solve knapsack
void solveKnapsack(int values[], int weights[], int n, int capacity) {
    int currentSolution[MAX_ITEMS] = {0};  // Start with nothing selected
    maxValue = 0;  // Reset maximum value
    
    // Initialize bestSolution array
    for(int i = 0; i < n; i++) {
        bestSolution[i] = 0;
    }
    
    // Start exploring solutions
    explore(values, weights, currentSolution, capacity, 0, 0, 0, n);
}

int main() {
    // Example problem
    int values[] = {60, 100, 120};    // Values of items
    int weights[] = {10, 20, 30};     // Weights of items
    int capacity = 50;                // Knapsack capacity
    int n = 3;                        // Number of items
    
    // Solve the knapsack problem
    solveKnapsack(values, weights, n, capacity);
    
    // Print results
    cout << "Maximum value: " << maxValue << endl;
    
    cout << "\nSelected items (1 = selected, 0 = not selected):\n";
    for(int i = 0; i < n; i++) {
        cout << "Item " << (i+1) << ": " << bestSolution[i] << endl;
    }
    
    cout << "\nDetailed solution:\n";
    for(int i = 0; i < n; i++) {
        if(bestSolution[i] == 1) {
            cout << "Take item " << (i+1) 
                 << " with value " << values[i] 
                 << " and weight " << weights[i] << endl;
        }
    }
    
    return 0;
}