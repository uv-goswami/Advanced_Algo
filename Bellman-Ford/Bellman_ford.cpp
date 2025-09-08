#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Edge {
  int u, v, w;
};

vector<int> bellmanFord(int V, int source, const vector<Edge>& edges) {
  const int INF = numeric_limits<int>::max();
  vector<int> dist(V, INF);
  dist[source] = 0;

  for (int i = 1; i <= V - 1; ++i) {
    for (auto& e : edges) {
      if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
        dist[e.v] = dist[e.u] + e.w;
      }
    }
  }

  for (auto& e : edges) {
    if (dist[e.u] != INF && dist[e.u] + e.w < dist[e.v]) {
      cout << "Graph contains a negative-weight cycle\n";
      break;
    }
  }

  return dist;
}

int main() {
  int V = 5;
  vector<Edge> edges = {
    {0, 1, 6}, {0, 2, 7}, {1, 2, 8},
    {1, 3, 5}, {1, 4, -4}, {2, 3, -3},
    {2, 4, 9}, {3, 1, -2}, {4, 3, 7}
  };

  int source = 0;
  auto dist = bellmanFord(V, source, edges);

  cout << "Vertex   Distance from Source\n";
  for (int i = 0; i < V; ++i) {
    if (dist[i] == numeric_limits<int>::max()) {
      cout << i << "        INF\n";
    } else {
      cout << i << "        " << dist[i] << "\n";
    }
  }

  return 0;
}