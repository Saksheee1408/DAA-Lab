#include<iostream>
using namespace std;

class Fractional {
public:
    int n; // number of items
    int weight[100]; // weights of items (max 100 items for simplicity)
    int profit[100]; // profits of items (max 100 items)
    double frac[100]; // profit/weight ratio
    int size; // size of knapsack

    // Function to swap integers
    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // Function to swap doubles
    void swap(double &a, double &b) {
        double temp = a;
        a = b;
        b = temp;
    }

    // Function to take input from the user
    void input() {
        cout << "Enter the number of items you are going to add: ";
        cin >> n;

        cout << "Enter the weights of the items:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> weight[i];
        }

        cout << "Enter the profits of the items:" << endl;
        for (int i = 0; i < n; i++) {
            cin >> profit[i];
        }

        cout << "Enter the size of the knapsack: ";
        cin >> size;
    }

    // Function to calculate profit-to-weight ratios and sort items in descending order of ratio
    void sortItems() {
        for (int i = 0; i < n; i++) {
            frac[i] = (double)profit[i] / weight[i];
        }

        for (int i = 0; i < n-1; i++) {
            for (int j = i+1; j < n; j++) {
                if (frac[i] < frac[j]) {
                    swap(frac[i], frac[j]);
                    swap(weight[i], weight[j]);
                    swap(profit[i], profit[j]);
                }
            }
        }
    }

    // Function to solve the knapsack problem
    void solution() {
        sortItems();

        double currentWeight = 0.0;
        double totalProfit = 0.0;

        cout << "Selected items for the knapsack:\n";
        for (int i = 0; i < n; i++) {
            if (currentWeight + weight[i] <= size) {
                // If the item can be fully added
                currentWeight += weight[i];
                totalProfit += profit[i];
                cout << "Item " << i + 1 << ": Fully added (Weight: " << weight[i] << ", Profit: " << profit[i] << ")\n";
            } else {
                // If the item can only be partially added
                int remainingWeight = size - currentWeight;
                double fraction = (double)remainingWeight / weight[i];
                totalProfit += profit[i] * fraction;
                currentWeight += remainingWeight;
                cout << "Item " << i + 1 << ": Partially added (" << fraction * 100 << "% of weight)\n";
                break; // Knapsack is full
            }
        }

        // Output total profit
        cout << "Total profit earned: " << totalProfit << endl;
    }
};

int main() {
    Fractional knapsack; // Create an object of Fractional class
    knapsack.input();    // Take input from the user
    knapsack.solution(); // Calculate and display the solution
    return 0;
}
