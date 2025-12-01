#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Edge {
    int src, dest, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
    vector<int> parent;
    vector<int> rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

int main() {
    int V, E;
    cout << "Enter vertices and edges: ";
    cin >> V >> E;
    
    Edge* edges = new Edge[E];
    cout << "Enter edges (src dest weight):\n";
    for (int i = 0; i < E; i++)
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    
    sort(edges, edges + E);
    
    UnionFind uf(V);
    int mstWeight = 0;
    
    cout << "MST Edges:\n";
    for (int i = 0; i < E; i++) {
        if (uf.find(edges[i].src) != uf.find(edges[i].dest)) {
            cout << edges[i].src << " - " << edges[i].dest 
                 << " : " << edges[i].weight << endl;
            mstWeight += edges[i].weight;
            uf.unite(edges[i].src, edges[i].dest);
        }
    }
    
    cout << "Total MST weight: " << mstWeight << endl;
    
    delete[] edges;
    return 0;
}
