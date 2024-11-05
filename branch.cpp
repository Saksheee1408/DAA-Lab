#include <iostream>
#include <algorithm>
using namespace std;
class Item {
public:
    int weight;
    int value;
    Item(int w = 0, int v = 0) : weight(w), value(v) {}
};
class Node
{
public:
    int level;  // Level in the decision tree
    int profit; // Profit so far
    int weight; // Weight so far
    float bound; // Upper bound of profit in the subtree
    Node(int l = -1, int p = 0, int w = 0) : level(l), profit(p), weight(w), bound(0) {}
};
class Knapsack
{
private:
    int capacity;
    int numItems;
    Item items[100];  // Array to store items (replace vector)
    Node nodes[1000]; // Array to simulate a queue (replace queue)
    int front, rear;  // Queue pointers

public:
    Knapsack(int W, Item* itemList, int n) : capacity(W), numItems(n), front(0), rear(0) {
        for (int i = 0; i < n; i++) {
            items[i] = itemList[i];
        }
    }

    // Function to calculate the upper bound of profit in a subtree
    float bound(Node u) {
        if (u.weight >= capacity)
            return 0;

        float profit_bound = u.profit;
        int j = u.level + 1;
        int total_weight = u.weight;

        while (j < numItems && total_weight + items[j].weight <= capacity) {
            total_weight += items[j].weight;
            profit_bound += items[j].value;
            j++;
        }

        if (j < numItems)
            profit_bound += (capacity - total_weight) * items[j].value / (float)items[j].weight;

        return profit_bound;
    }

    // Function to sort items by value/weight ratio
    static bool compare(Item a, Item b) {
        double r1 = (double)a.value / a.weight;
        double r2 = (double)b.value / b.weight;
        return r1 > r2;
    }

    // Branch and Bound algorithm
    int knapsack() {
        sort(items, items + numItems, compare);

        Node u, v;
        u.level = -1;
        u.profit = u.weight = 0;
        nodes[rear++] = u;  // Enqueue the root node

        int maxProfit = 0;

        while (front < rear) {
            u = nodes[front++];  // Dequeue

            if (u.level == numItems - 1)
                continue;

            // Exploring the next level item by taking it
            v.level = u.level + 1;
            v.weight = u.weight + items[v.level].weight;
            v.profit = u.profit + items[v.level].value;

            if (v.weight <= capacity && v.profit > maxProfit)
                maxProfit = v.profit;

            v.bound = bound(v);

            if (v.bound > maxProfit)
                nodes[rear++] = v;  // Enqueue if bound is promising

            // Now explore the case of not taking the item
            v.weight = u.weight;
            v.profit = u.profit;
            v.bound = bound(v);

            if (v.bound > maxProfit)
                nodes[rear++] = v;  // Enqueue if bound is promising
        }

        return maxProfit;
    }
};

int main() {
    int W = 10;  // Knapsack capacity
    Item itemList[] = {{2, 40}, {3, 50}, {5, 100}, {7, 60}};
    int n = sizeof(itemList) / sizeof(itemList[0]);

    Knapsack knapsack(W, itemList, n);
    cout << "Maximum profit: " << knapsack.knapsack() << endl;

    return 0;
}
