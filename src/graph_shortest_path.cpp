#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;

class Graph {
private:
    vector<list<pair<int, int>>> adjList; // Adjacency list representation
    int vertices; // Number of vertices in the graph

public:
    // Constructor to initialize the graph with a given number of vertices
    Graph(int v) : vertices(v), adjList(v) {}

    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        if (u < 0 || v < 0 || u >= vertices || v >= vertices) {
            cerr << "Error: Invalid edge (" << u << ", " << v << ").\n";
            return;
        }
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Comment this line for directed graphs
    }

    // Dijkstra's Algorithm to find shortest paths from a start vertex
    void dijkstra(int start) {
        if (start < 0 || start >= vertices) {
            cerr << "Error: Invalid start vertex " << start << ".\n";
            return;
        }

        vector<int> distance(vertices, INT_MAX); // Initialize distances to infinity
        distance[start] = 0; // Distance to the start vertex is 0
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start}); // Push the start vertex to the priority queue

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentVertex = pq.top().second;
            pq.pop();

            // Skip if the distance in the queue is outdated
            if (currentDistance > distance[currentVertex]) continue;

            // Explore neighbors of the current vertex
            for (auto &neighbor : adjList[currentVertex]) {
                int neighborVertex = neighbor.first;
                int edgeWeight = neighbor.second;

                // Relaxation step
                if (currentDistance + edgeWeight < distance[neighborVertex]) {
                    distance[neighborVertex] = currentDistance + edgeWeight;
                    pq.push({distance[neighborVertex], neighborVertex});
                }
            }
        }

        // Print shortest distances
        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << ": "
                 << (distance[i] == INT_MAX ? "Infinity" : to_string(distance[i])) << endl;
        }
    }
};

int main() {
    int vertices, edges;

    // Get number of vertices with validation
    do {
        cout << "Enter the number of vertices: ";
        cin >> vertices;
        if (vertices <= 0) {
            cout << "Error: Number of vertices must be positive.\n";
        }
    } while (vertices <= 0);

    // Get number of edges with validation
    do {
        cout << "Enter the number of edges: ";
        cin >> edges;
        if (edges < 0) {
            cout << "Error: Number of edges cannot be negative.\n";
        }
    } while (edges < 0);

    Graph graph(vertices);

    // Input edges
    cout << "Enter the edges in the format (u v weight):\n";
    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;

        if (weight < 0) {
            cerr << "Error: Negative edge weights are not allowed in Dijkstra's Algorithm.\n";
            i--; // Retry this edge input
            continue;
        }

        graph.addEdge(u, v, weight);
    }

    // Input start vertex
    int startVertex;
    do {
        cout << "Enter the start vertex: ";
        cin >> startVertex;
        if (startVertex < 0 || startVertex >= vertices) {
            cout << "Error: Invalid start vertex. Please enter a value between 0 and " << vertices - 1 << ".\n";
        }
    } while (startVertex < 0 || startVertex >= vertices);

    // Run Dijkstra's Algorithm
    graph.dijkstra(startVertex);

    return 0;
}
