#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

typedef pair<int, int> pii;  // Pair of (vertex, weight)

// Function to add an edge to the graph
void addEdge(vector<vector<pii>>& graph, int u, int v, int weight) {
    graph[u].push_back(make_pair(v, weight));
    graph[v].push_back(make_pair(u, weight));  // For undirected graph
}

// Dijkstra's algorithm for SSSP
void dijkstra(const vector<vector<pii>>& graph, int source, vector<int>& distances) {
    int numVertices = graph.size();  // Number of vertices

    // Priority queue to store vertices with their distances from the source
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    // Set all distances to infinity initially
    distances.assign(numVertices, numeric_limits<int>::max());

    // Distance of source vertex from itself is 0
    distances[source] = 0;

    pq.push(make_pair(0, source));

    while (!pq.empty()) {
        int currVertex = pq.top().second;
        pq.pop();

        // Visit all neighbors of currVertex
        for (const auto& neighbor : graph[currVertex]) {
            int nextVertex = neighbor.first;
            int weight = neighbor.second;

            // Relaxation step: If the distance to nextVertex through currVertex is shorter, update the distance
            if (distances[currVertex] + weight < distances[nextVertex]) {
                distances[nextVertex] = distances[currVertex] + weight;
                pq.push(make_pair(distances[nextVertex], nextVertex));
            }
        }
    }
}

// Utility function to print the distances
void printDistances(const vector<int>& distances) {
    cout << "Vertex\tDistance from Source\n";
    for (int i = 0; i < distances.size(); ++i) {
        cout << i << "\t" << distances[i] << "\n";
    }
}

int main() {
    int numVertices = 6;  // Number of vertices in the graph

    // Create an empty graph
    vector<vector<pii>> graph(numVertices);

    // Add edges to the graph
    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 15);
    addEdge(graph, 0, 5, 5);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 1, 3, 30);
    addEdge(graph, 2, 3, 12);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 5, 20);

    int source = 0;  // Source vertex for SSSP

    vector<int> distances(numVertices);
    dijkstra(graph, source, distances);

    // Print the shortest distances
    printDistances(distances);

    return 0;
}
