#include <iostream>
#include <climits>

using namespace std;

const int N = 4; // Number of cities

int minCost = INT_MAX; // Initialize minimum cost to maximum possible value
int path[N + 1]; // Array to store the final path

// Function to find the minimum cost edge connected to a city
int findMinEdge(int adj[N][N], int city) {
    int min = INT_MAX;
    for (int i = 0; i < N; i++) {
        if (adj[city][i] < min && city != i) {
            min = adj[city][i];
        }
    }
    return min;
}

// Recursive function to solve TSP using branch and bound
void tspBranchAndBound(int adj[N][N], int currentCost, int currentPath[], int level) {
    if (level == N) { // Base case: If all cities have been visited
        int totalCost = currentCost + adj[currentPath[level - 1]][0]; // Add cost to return to the starting city
        if (totalCost < minCost) { // Update minimum cost and path if a better solution is found
            minCost = totalCost;
            for (int i = 0; i <= N; i++) {
                path[i] = currentPath[i];
            }
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (adj[currentPath[level - 1]][i] != 0) { // Check if there is an edge from the current city to city i
            int newCost = currentCost + adj[currentPath[level - 1]][i];
            int newBound = newCost + (N - level) * min(findMinEdge(adj, currentPath[level - 1]), findMinEdge(adj, i));
            if (newBound < minCost) { // Only continue if the new bound is less than the current minimum cost
                currentPath[level] = i;
                tspBranchAndBound(adj, newCost, currentPath, level + 1);
            }
        }
    }
}

int main() {
    // Define adjacency matrix with distances between cities
    int adj[N][N] = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };

    int currentPath[N + 1];
    currentPath[0] = 0; // Start from the first city

    tspBranchAndBound(adj, 0, currentPath, 1); // Call the recursive function to solve the TSP

    // Output the minimum cost and the path taken
    cout << "Minimum cost: " << minCost << endl;
    cout << "Path Taken: ";
    for (int i = 0; i <= N; i++) {
        cout << path[i] << " ";
    }
    cout << endl;

    return 0;
}