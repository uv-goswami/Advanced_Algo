
# 📌 The Minimum Spanning Tree (MST)

A **spanning tree** of a connected, undirected, and weighted graph is a subset of the graph that:

* Includes all the vertices
* Is connected
* Contains no cycles (is acyclic)

Among all the possible spanning trees of a graph, the **Minimum Spanning Tree (MST)** is the one with the **least total sum of edge weights**.

---

## 🔑 Key Features and Characteristics

* **Greedy Nature**: Kruskal's Algorithm is a greedy technique — it always chooses the smallest weight edge that does not form a cycle.
* **Edge-based Construction**: Kruskal's algorithm takes all the edges in a set, so connecting the edges becomes more efficient irrespective of the starting point.
* **Disjoint Set Union-Find Structure**: The disjoint set (union-find) data structure keeps track of connected components and ensures no cycles are introduced by checking if the edge is already in the union set.

---

## 🧭 Step-Wise Working

1. Store all edges with weights.
2. Sort all edges in non-decreasing order of their weights.
3. Initialize an empty MST and Disjoint Set for all vertices.
4. Iterate through sorted edges.
5. For each edge, check if the vertices lie in different sets.
6. If yes, add the edge to the MST and union the sets.
7. If not, skip the edge to avoid cycles.
8. Repeat until MST contains V-1 edges.

---

## 🧾 Pseudocode

```plaintext
Kruskal(G):
  MST = {}
  For each vertex v in G.V:
    Make-Set(v)
  For each edge (u,v) in G.E (in increasing weight):
    if Find-Set(u) != Find-Set(v):
      MST = MST U {(u,v)}
      Union(u,v)
  Return MST
```

---

## 🧩 Disjoint Set (Union-Find) Data Structure

The vital part of Kruskal's Algorithm is detecting cycles — this is achieved using the **disjoint set (or union-find)** data structure such that:

* Each vertex belongs to exactly one set at a time
* The `find` operation returns the root (representative) of the set
* The `union` operation merges two sets

### Core Operations:

* `Make-Set(x)`: Initializes a set containing only `x`.
* `Find-Set(x)`: Returns the representative element of the set containing `x`.
* `Union(x, y)`: Merges the sets containing `x` and `y`.

---

## 🧑‍💻 C++ Implementation

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;

    bool operator<(const Edge& other) const {
        return w < other.w;
    }
};

class DSU {
    vector<int> parent;

public:
    DSU(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return false;
        }
        parent[rootY] = rootX;
        return true;
    }
};

int KruskalMST(int numNodes, vector<Edge>& edges) {
    sort(edges.begin(), edges.end());

    DSU dsu(numNodes);
    int totalWeight = 0;
    cout << "Edges in the MST: \n";

    for (Edge& edge : edges) {
        if (dsu.unite(edge.u, edge.v)) {
            cout << edge.u << "-" << edge.v << "  Weight: " << edge.w << endl;
            totalWeight += edge.w;
        }
    }
    return totalWeight;
}

int main() {
    int vertices = 4;

    vector<Edge> edges = {
        {0, 1, 10},
        {0, 2, 5},
        {2, 3, 9},
        {0, 3, 3},
        {1, 2, 6}
    };

    int MST_weight = KruskalMST(vertices, edges);

    cout << MST_weight;

    return 0;
}
```

---

## ⏱️ Time Complexity

### 1. DSU Initialization

* **What happens**: Construct the parent vector of size `n`.
* **Cost**: `O(n)`
* **Why**: One assignment per vertex
* **Where**: Inside `DSU(int n)` constructor.

### 2. Sorting the Edges

* **What happens**: Call `sort(edges.begin(), edges.end())`
* **Cost**: `O(m log m)`
* **Why**: Comparison-based sorting algorithm

### 3. MST Construction Loop

* **What happens**: Iterate through all `m` edges and perform find & unite
* **Cost per edge**: `O(𝛼(n))`, where `𝛼` is the Inverse Ackermann Function
* **Total Cost**: `O(m 𝛼(n))`
* **Why**: Path compression and union by rank provide nearly constant time

### ✅ Overall Time Complexity

```cpp
O(n) + O(m log m) + O(m 𝛼(n)) = O(m log m)
```

---

## 💾 Space Complexity

* **Edge Vector**: `O(m)`
* **DSU Parent Array**: `O(n)`
* **Call Stack (find)**: `O(𝛼(n))`
* **Sorting**: `O(log m)` (if recursion used internally)

### ✅ Overall Space Complexity

```cpp
O(m + n)
```

---

## ✅ Advantages

* Simple and intuitive
* Efficient for **sparse graphs**
* Handles **sorted edges** optimally
* Widely applicable in real-world scenarios (networks, pipelines, etc.)

---

## ❌ Disadvantages

* Slower for **dense graphs** due to sorting overhead
* **Not suitable for directed graphs**
* Requires tracking **all edges**, which may be memory intensive

---

## 💡 When to Use Kruskal’s Algorithm

* The graph is **sparse** (`E ≅ O(V)`)
* Edges can be **quickly sorted**
* Cycle detection (Union-Find) is **easy to implement**

---

## 🚫 When NOT to Use Kruskal’s Algorithm

* The graph is **dense** (`E ≅ V²`)
* Adjacency matrix or vertex-based representation is preferred
* Memory overhead due to **storing all edges**

---

## ⚔️ Kruskal vs. Prim’s Algorithm

| Feature             | Kruskal’s Algorithm                    | Prim’s Algorithm                         |
| ------------------- | -------------------------------------- | ---------------------------------------- |
| **Approach**        | Greedy, edge-based                     | Greedy, vertex-based                     |
| **Data Structure**  | Disjoint Set (Union-Find)              | Priority Queue (Min-Heap)                |
| **Suitable For**    | Sparse graphs                          | Dense graphs                             |
| **Edge Selection**  | Picks globally smallest edge           | Picks smallest edge from the growing MST |
| **Graph Type**      | Works on disconnected graphs (forests) | Requires connected graphs                |
| **Time Complexity** | O(E log E)                             | O(E + V log V)                           |
| **Cycle Detection** | Explicit (Union-Find)                  | Not needed                               |
| **Parallelization** | Easier for edge sorting                | Harder to parallelize                    |
| **Output**          | MST / Forest                           | MST only                                 |

---

## 🌍 Real-World Applications

1. **Network Design** (Telecommunications, Electrical Grids): Connect all nodes with minimum wiring/cost
2. **Urban Infrastructure Planning**: Lay down roads/pipelines efficiently
3. **Clustering in Machine Learning & Data Science**: Hierarchical clustering via MST
4. **Image Segmentation & Computer Vision**: Partition pixels using similarity weights
5. **Approximation Algorithms for NP-Hard Problems**: Like TSP (Traveling Salesman Problem)

---

## 🛠️ Handling Special Cases and Edge Scenarios

1. **Disconnected Graph**: Kruskal computes **Minimum Spanning Forest**
2. **Negative Edge Weights**: Works well; sorting handles it correctly
3. **Multiple MSTs**: If multiple MSTs exist with same weight, the sorted edge order decides
4. **Edge Sorting Cost**: Can be high for dense graphs — use Prim’s Algorithm instead

---

> ✅ **Note**: Kruskal’s Algorithm is simple, intuitive, and efficient for sparse graphs. When edge sorting is manageable, and a forest-based approach is acceptable, it’s a go-to choice in graph theory.

---
