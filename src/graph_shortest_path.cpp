#include <iostream>

using namespace std;
int main() {
    int vertices = 5; // Number of vertices
    Graph graph(vertices);

    // Add edges (u, v, weight)
    graph.addEdge(0, 1, 2);
    graph.addEdge(0, 3, 6);
    graph.addEdge(1, 2, 3);
    graph.addEdge(1, 3, 8);
    graph.addEdge(1, 4, 5);
    graph.addEdge(2, 4, 7);
    graph.addEdge(3, 4, 9);
}
