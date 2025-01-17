#include <iostream>
#include <vector>
#include <iomanip>
#include <climits>

using namespace std;

// Define a constant for infinity
const int INF = INT_MAX;

// Function to print the distance matrix
void printMatrix(const vector<vector<int>> &matrix) {
    int n = matrix.size();
    cout << "\nShortest Distance Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INF)
                cout << setw(7) << "INF";
            else
                cout << setw(7) << matrix[i][j];
        }
        cout << endl;
    }
}

// Floyd-Warshall Algorithm
void floydWarshall(const vector<vector<int>> &graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph; // Copy of the input graph to store distances

    // Main algorithm
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative weight cycles
for (int i = 0; i < n; i++) {
    if (dist[i][i] < 0) {
        cout << "Graph contains a negative weight cycle.\n";
        return;
    }
}

    // Output the result
    printMatrix(dist);
}

int main() {
    int vertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;

    // Initialize the adjacency matrix
    vector<vector<int>> graph(vertices, vector<int>(vertices, INF));

    cout << "Enter the graph's adjacency matrix (use " << INF << " for no direct edge):\n";
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cin >> graph[i][j];
            if (i == j) graph[i][j] = 0; // Set distance to itself as 0
        }
    }

    cout << "\nProcessing the graph using Floyd-Warshall Algorithm...\n";
    floydWarshall(graph);

    return 0;
}
