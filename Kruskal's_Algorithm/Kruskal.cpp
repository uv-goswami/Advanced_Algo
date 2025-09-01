#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    int u, v, w;

    bool operator<(const Edge& other) const{
        return w <other.w ;
    }
};

class DSU{
    vector<int> parent;

    public:
        DSU(int n){
            parent.resize(n);
            for(int i = 0; i < n; ++i){
                parent[i] = i;
            }
        }   

        int find(int x){
            if(parent[x] != x){
                parent[x] = find(parent[x]);
            }
            return parent[x];
        }

        bool unite(int x, int y){
            int rootX = find(x);
            int rootY = find(y);
            if(rootX == rootY){
                return false;
            }
            parent[rootY] = rootX;
            return true;
        }
};

int KruskalMST(int numNodes, vector<Edge>& edges){
    sort(edges.begin(), edges.end());

    DSU dsu(numNodes);
    int totalWeight = 0;
    cout<< "Edges in the MST: \n";

    for(Edge& edge : edges){
        if(dsu.unite(edge.u, edge.v)){
            cout<<edge.u << "-" << edge.v << "  Weight: " << edge.w <<endl;
            totalWeight += edge.w;
        }
    }
    return totalWeight;
}

int main(){

    int vertices = 4;

        vector<Edge> edges = {
            {0, 1, 10},
            {0, 2, 5},
            {2, 3, 9},
            {0, 3, 3},
            {1, 2 , 6}
        };

        int MST_weight = KruskalMST(vertices, edges);

        cout<< MST_weight;




    return 0;
}