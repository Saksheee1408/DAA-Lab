
#include <iostream>
#include <string>

using namespace std;

class Graph {
public:
    int V; // Number of vertices
    int adj[10][10]; // Adjacency matrix

    Graph(int V) {
        this->V = V;
       
        for (int i = 0; i < V; i++) {
           for(int j=0;j<V;j++)
           {
            adj[i][j]=0;
           }
        }
    }

    ~Graph() {
        for (int i = 0; i < V; i++) {
            delete[] adj[i];
        }
        delete[] adj;
    }

    void addEdge(int u, int v) {
        adj[u][v] = 1; // Add edge from u to v
        adj[v][u] = 1; // Since it's undirected, add edge from v to u
    }

    bool isValidColoring(string colors[]) {
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                if (adj[u][v] == 1 && colors[u] == colors[v]) {
                    return false; // Adjacent vertices have the same color
                }
            }
        }
        return true;
    }

    void generateColoringsUtil(int vertex, string colorNames[], string colors[]) {
        // Base case: if all vertices are colored
        if (vertex == V) {
            // Check if the current coloring is valid
            if (isValidColoring(colors)) {
                cout << "Valid coloring: ";
                for (int i = 0; i < V; i++) {
                    cout << colors[i] << " ";
                }
                cout << endl;
            }
            return;
        }

        // Try coloring the current vertex with all possible colors
        for (int i = 0; i < 3; i++) { // Assuming 3 colors
            colors[vertex] = colorNames[i]; // Assign color to vertex
            generateColoringsUtil(vertex + 1, colorNames, colors); // Recur for the next vertex
        }
    }

    void generateColorings(string colorNames[]) {
        string colors[V]; // Array to store colors of vertices
        generateColoringsUtil(0, colorNames, colors); // Start with the first vertex
    }
};

int main() {
    Graph g(3); // Create a graph with 4 vertices
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
   

    
     // Define colors
    g.generateColorings(colors); // Generate colorings

    return 0;
}
