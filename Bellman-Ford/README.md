# 📌 The Bellman-Ford Algorithm

The Bellman-Ford algorithm computes shortest paths from a single source vertex to all other vertices in a weighted, directed graph.  
It gracefully handles negative edge weights and can detect negative-weight cycles reachable from the source.

---

## 🔑 Key Features and Characteristics

- Relaxation-Based: Repeatedly relaxes edges to update distance estimates.  
- Negative Weights Supported: Finds shortest paths even if some edge weights are negative.  
- Cycle Detection: Identifies negative-weight cycles by performing one extra relaxation pass.  
- Simple Data Structures: Uses a list of edges and a distance array—all provided by the C++ STL.

---

## 🧭 Step-Wise Working

1. Initialize distance to source as 0 and all others as infinity.  
2. Repeat V–1 times, where V is the number of vertices:  
   - For each edge (u, v, w), if dist[u] + w < dist[v], update dist[v] = dist[u] + w.  
3. Perform one more pass over all edges to check for further relaxation:  
   - If any distance can still be reduced, a negative-weight cycle exists.  
4. Report distances and whether a negative cycle was detected.

---

## 🧾 Pseudocode

```plaintext
BellmanFord(G, source):
  for each vertex v in G.V:
    dist[v] = infinity
  dist[source] = 0

  for i from 1 to |V| - 1:
    for each edge (u, v, w) in G.E:
      if dist[u] + w < dist[v]:
        dist[v] = dist[u] + w

  for each edge (u, v, w) in G.E:
    if dist[u] + w < dist[v]:
      report "Negative cycle detected"
      break

  return dist[]
```

---

## 🧑‍💻 C++ Implementation

```cpp
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
```

---

## ⏱️ Time Complexity

- Initialization  
  - Sets up distance array of size V  
  - Cost: O(V)  

- Relaxation Phase  
  - V–1 passes over all E edges  
  - Cost per pass: O(E)  
  - Total: O(V·E)  

- Cycle Check  
  - One extra pass over E edges  
  - Cost: O(E)  

✅ Overall: O(V·E)

---

## 💾 Space Complexity

- Distance array: O(V)  
- Edge list: O(E)  

✅ Overall: O(V + E)

---

## ✅ Advantages

- Handles negative edge weights.  
- Detects negative-weight cycles.  
- Simpler data structures compared to priority-queue approaches.  
- Suitable for sparse or dense graphs when negative weights are present.

---

## ❌ Disadvantages

- Slower than Dijkstra for non-negative weights due to O(V·E) runtime.  
- Uses global edge list—less efficient if graph is dynamic.  
- May waste work relaxing edges that no longer improve distances.

---

## 💡 When to Use Bellman-Ford

- Graph contains negative edge weights.  
- Need to detect negative-weight cycles.  
- Vertex count V is small or edge count E is moderate.  

---

## 🚫 When NOT to Use Bellman-Ford

- All edge weights are non-negative and graph is large.  
- You require faster queries—Dijkstra or A* may be preferable.  
- Graph updates frequently and an incremental shortest-path is needed.

---

## ⚔️ Bellman-Ford vs. Dijkstra

| Feature                  | Bellman-Ford                      | Dijkstra                            |
| ------------------------ | --------------------------------- | ----------------------------------- |
| **Edge Weights**         | Can be negative                   | Must be non-negative                |
| **Time Complexity**      | O(V·E)                            | O(E + V·log V) with min-heap        |
| **Negative-Cycle Check** | Yes                               | No                                  |
| **Data Structure**       | Edge list + array                 | Adjacency list + min-heap/priority queue |
| **Use Case**             | General weighted graphs           | Non-negative weights, large graphs  |

---

## 🌍 Real-World Applications

1. Currency arbitrage detection in financial systems  
2. Routing protocols (e.g., RIP – Routing Information Protocol)  
3. Network latency optimization with negative cost metrics  
4. Finding shortest paths in temporal graphs with time penalties  

---

## 🛠️ Handling Special Cases and Edge Scenarios

- If graph is disconnected, unreachable vertices remain at INF.  
- If negative-weight cycles exist, distances become undefined.  
- For very large E·V, consider more efficient or specialized algorithms.  
- To speed up in practice, use early exit if no relaxation occurs in a pass.

---

> ✅ **Note**: Bellman-Ford trades speed for flexibility—use it when negative weights or cycle detection are critical.
