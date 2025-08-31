# The Minimum Spanning Tree(MST)
A spanning tree of a connected, undirected, and weighted graph is a subset of the graph that: 
  -Includes all the vertices,
  -Is connected.
  -Contains no cycles(is acyclic)
Among all the possible spanning tree of a graph, the Minimum Spanning Tree is the one with the least total sum of edge weights.

Key Features and Characteistics
  . Greedy Nature: Kruskal's Algorithm is a greedy technique-- it always chooses the smallest weight edge that does not form a cycle.
  .Edge-based Construction: Krushkal's algo takes all the edges in a set, so connecting the edging becomes more efficient irrespective of starting point.
  .Disjoint Set Union-Find Structure: disjoint set(union find) data structure, keeps track of connected components and ensure no cycles are introduced by checking if the edge is already in the union set.

Step-Wise Working :
1. Store all edges with weights.
2. Sort all edges in non-decreasing order of their weights.
3. Initialize an Empty MST and  Disjoint Set for all vertices
4. Iterate through sorted edges
5. For each edge, check if the vertices lie in different sets.
6. if yes, then add the edge to the MST and union the sets.
7. If not then skip the edge to avoid cycles
8. Repeat until MST contain V-1 edges.

---
#Pseudocode
```
Kruskal(G):
  MST = {}
  For each vertex V in G.V:
    Make-Set(v)
  For each edge(u,v) in G.E (in increasing weight):
    if Find-Set(u) != find-Set(v):
      MST = MST U {(u,v)}
      Union(u,v)
  Return MST
```
---
# Disjoint Set(Union-Find) Data Structure
The vital part of Kruskal's Algorithm is detecting cycles that is achieved using disjoint set(or union find) data Structure such that:
  . Each vertex belong to exactly one set at a time
  . The 'find' operation returns the root(starting point ) of the set.
  .The 'union' operation merges two sets.
Core Operations:
  . Make-Set(x): Initializes a set containing only x.
  . Find-Set(x): Returns the representative element of the set containing x.
  . Union(x,y): Merges the sets containing x and y.
---
# C++ Implementation
```
#include <iostream>
#include <vector>

```















