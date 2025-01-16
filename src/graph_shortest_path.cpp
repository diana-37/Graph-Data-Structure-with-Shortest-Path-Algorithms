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
