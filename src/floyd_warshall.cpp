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

// Function to validate adjacency matrix input
void validateInput(vector<vector<int>> &graph, int i, int j, int value) {
    if (value < 0 && value != INF) {
        cerr << "Error: Negative weight detected at position (" << i << ", " << j << ").\n";
        exit(EXIT_FAILURE);
    }
    graph[i][j] = value;
}

// Floyd-Warshall Algorithm
vector<vector<int>> floydWarshall(const vector<vector<int>> &graph) {
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

    return dist; // Return the final distance matrix
}

int main() {
    int vertices;
    cout << "Enter the number of vertices in the graph: ";
    cin >> vertices;

    if (vertices <= 0) {
        cerr << "Error: The number of vertices must be positive.\n";
        return EXIT_FAILURE;
    }

    // Initialize the adjacency matrix
    vector<vector<int>> graph(vertices, vector<int>(vertices, INF));

    cout << "Enter the graph's adjacency matrix (use " << INF << " for no direct edge):\n";
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            int value;
            cin >> value;
            validateInput(graph, i, j, value);
        }
    }

    // Ensure diagonal values are 0 (distance to self)
    for (int i = 0; i < vertices; i++) {
        graph[i][i] = 0;
    }

    cout << "\nProcessing the graph using Floyd-Warshall Algorithm...\n";
    vector<vector<int>> result = floydWarshall(graph);

    // Output the result
    printMatrix(result);

    return 0;
}

