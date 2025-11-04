#include <iostream>
#include <limits.h>
#include <vector>
using namespace std;

struct Edge {
    int src, dest, weight;
};

void bellmanFord(vector<Edge>& edges, int V, int source) {
    int* dist = new int[V];
    
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[source] = 0;
    
    // Relax edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (const Edge& e : edges) {
            if (dist[e.src] != INT_MAX && 
                dist[e.src] + e.weight < dist[e.dest]) {
                dist[e.dest] = dist[e.src] + e.weight;
            }
        }
    }
    
    // Check for negative cycles
    for (const Edge& e : edges) {
        if (dist[e.src] != INT_MAX && 
            dist[e.src] + e.weight < dist[e.dest]) {
            cout << "Graph contains negative weight cycle\n";
            delete[] dist;
            return;
        }
    }
    
    cout << "Vertex\tDistance from Source " << source << endl;
    for (int i = 0; i < V; i++)
        cout << i << "\t" << (dist[i] == INT_MAX ? "INF" : to_string(dist[i])) << endl;
    
    delete[] dist;
}

int main() {
    int V, E, source;
    cout << "Enter vertices and edges: ";
    cin >> V >> E;
    
    vector<Edge> edges(E);
    cout << "Enter edges (src dest weight):\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    
    cout << "Enter source vertex: ";
    cin >> source;
    
    bellmanFord(edges, V, source);
    
    return 0;
}
