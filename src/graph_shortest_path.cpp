#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <climits>

using namespace std;

class Graph {
private:
    vector<list<pair<int, int>>> adjList;
    int vertices;

public:
    Graph(int v) : vertices(v), adjList(v) {}

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    void dijkstra(int start) {
        vector<int> distance(vertices, INT_MAX);
        distance[start] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentVertex = pq.top().second;
            pq.pop();

            for (auto &neighbor : adjList[currentVertex]) {
                int neighborVertex = neighbor.first;
                int edgeWeight = neighbor.second;
                if (currentDistance + edgeWeight < distance[neighborVertex]) {
                    distance[neighborVertex] = currentDistance + edgeWeight;
                    pq.push({distance[neighborVertex], neighborVertex});
                }
            }
        }

        cout << "Shortest distances from vertex " << start << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertex " << i << ": "
                 << (distance[i] == INT_MAX ? "Infinity" : to_string(distance[i])) << endl;
        }
    }
};

int main() {
    int vertices, edges;
    cin >> vertices >> edges;

    Graph graph(vertices);

    for (int i = 0; i < edges; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph.addEdge(u, v, weight);
    }

    int startVertex;
    cin >> startVertex;

    graph.dijkstra(startVertex);

    return 0;
}

#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

class Graph {
public:
    int V; // Number of vertices
    vector<vector<pair<int, int>>> adj; // Adjacency list

    Graph(int V) {
        this->V = V;
        adj.resize(V);
    }

    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w)); // Add edge from u to v with weight w
        adj[v].push_back(make_pair(u, w)); // Add edge from v to u (for undirected graph)
    }

    void dijkstra(int src) {
        vector<int> dist(V, numeric_limits<int>::max()); // Distance from src to each vertex
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // Min-heap

        dist[src] = 0;
        pq.push(make_pair(0, src)); // Push source vertex with distance 0

        while (!pq.empty()) {
            int u = pq.top().second; // Get vertex with minimum distance
            pq.pop();

            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                // Relaxation step
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push(make_pair(dist[v], v)); // Push updated distance to the priority queue
                }
            }
        }

        // Print shortest distances
        cout << "Vertex Distance from Source (" << src << "):\n";
        for (int i = 0; i < V; i++) {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }
};

int main() {
    Graph g(5); // Create a graph with 5 vertices
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 0, 7);
    g.addEdge(4, 1, 3);
    g.addEdge(4, 2, 9);
    g.addEdge(4, 3, 2);

    g.dijkstra(0); // Find shortest paths from vertex 0

    return 0;
}

