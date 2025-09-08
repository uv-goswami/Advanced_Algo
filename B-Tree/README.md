# 📌 B-Tree

A **B-Tree** is a balanced, multi-way search tree optimized for systems that read and write large blocks of data (e.g., databases, file systems). It generalizes binary search trees by allowing nodes to have more than two children, keeping the tree height low and reducing disk I/O.

---

## 🔑 Key Features and Characteristics

* **Minimum Degree (t):** Each node (except root) has between *t–1* and *2t–1* keys.  
* **Balanced Structure:** All leaves appear at the same depth.  
* **Multi-way Nodes:** Each internal node with *k* keys has *k+1* children.  
* **Efficient Disk Access:** Nodes map to pages; high fan-out reduces tree height.  
* **Fast Operations:** Search, insert, and delete in *O(log n)* time.

---

## 🧭 Step-Wise Working: Insertion

Insert sequence example (t = 3, so each node can hold 2→5 keys):

Keys to insert: 10, 20, 5, 6, 12, 30, 7, 17  

1. Insert 10 → root = [10]  
2. Insert 20 → root = [10 | 20]  
3. Insert 5  → root = [5 | 10 | 20]  
4. Insert 6  → root = [5 | 6 | 10 | 20]  
5. Insert 12 → root = [5 | 6 | 10 | 12 | 20] (now full)  
6. Next insert 30:  
   - Root full → split into two nodes:  
     • left = [5 | 6]  
     • middle key = 10 → new root = [10]  
     • right = [12 | 20]  
   - Insert 30 into right → right = [12 | 20 | 30]  
7. Insert 7 → goes to left child → left = [5 | 6 | 7]  
8. Insert 17 → goes to right child → right = [12 | 17 | 20 | 30]  

Final tree:
```
            [10]
           /    \
     [5 | 6 | 7]  [12 | 17 | 20 | 30]
```
![B-Tree](https://github.com/uv-goswami/Advanced_Algo/blob/f4ab6a4be5cb8c25d80770e1f1a8f1c9b7d2923f/B-Tree/B-Tree.png)
---

## 🧾 Pseudocode

```plaintext
BTreeInsert(T, k):
  r = T.root
  if r.n == 2t−1:                   // root is full
    s = allocate_node()
    T.root = s
    s.leaf = false
    s.n = 0
    s.C[0] = r
    BTreeSplitChild(s, 0)
    BTreeInsertNonFull(s, k)
  else:
    BTreeInsertNonFull(r, k)

BTreeSplitChild(x, i):
  y = x.C[i]
  z = allocate_node()
  z.leaf = y.leaf
  z.n = t−1
  for j = 1 to t−1:
    z.key[j] = y.key[j+t]
  if not y.leaf:
    for j = 1 to t:
      z.C[j] = y.C[j+t]
  y.n = t−1
  for j = x.n+1 downto i+1:
    x.C[j+1] = x.C[j]
  x.C[i+1] = z
  for j = x.n downto i:
    x.key[j+1] = x.key[j]
  x.key[i] = y.key[t]
  x.n = x.n + 1

BTreeInsertNonFull(x, k):
  i = x.n
  if x.leaf:
    while i ≥ 1 and k < x.key[i]:
      x.key[i+1] = x.key[i]
      i = i−1
    x.key[i+1] = k
    x.n = x.n + 1
  else:
    while i ≥ 1 and k < x.key[i]:
      i = i−1
    i = i + 1
    if x.C[i].n == 2t−1:
      BTreeSplitChild(x, i)
      if k > x.key[i]:
        i = i + 1
    BTreeInsertNonFull(x.C[i], k)
```

---

## 🧑‍💻 C++ Implementation

```cpp
#include <iostream>
#include <vector>

template<typename Key>
struct BTreeNode {
  bool leaf;
  int n;                         // current number of keys
  std::vector<Key> key;         // size = 2*t - 1
  std::vector<BTreeNode*> C;    // size = 2*t

  BTreeNode(int t, bool leaf)
    : leaf(leaf), n(0),
      key(2*t - 1), C(2*t, nullptr) {}
};

template<typename Key>
class BTree {
  BTreeNode<Key>* root;
  int t;  // minimum degree

public:
  explicit BTree(int _t) : root(nullptr), t(_t) {}

  void traverse(BTreeNode<Key>* x) {
    int i;
    for (i = 0; i < x->n; ++i) {
      if (!x->leaf) traverse(x->C[i]);
      std::cout << x->key[i] << " ";
    }
    if (!x->leaf) traverse(x->C[i]);
  }

  void traverse() {
    if (root) traverse(root);
    std::cout << "\n";
  }

  BTreeNode<Key>* search(BTreeNode<Key>* x, Key k) {
    int i = 0;
    while (i < x->n && k > x->key[i]) ++i;
    if (i < x->n && x->key[i] == k) return x;
    if (x->leaf) return nullptr;
    return search(x->C[i], k);
  }

  void insert(Key k) {
    if (!root) {
      root = new BTreeNode<Key>(t, true);
      root->key[0] = k;
      root->n = 1;
      return;
    }

    if (root->n == 2*t - 1) {
      BTreeNode<Key>* s = new BTreeNode<Key>(t, false);
      s->C[0] = root;
      splitChild(s, 0);
      root = s;
      insertNonFull(s, k);
    } else {
      insertNonFull(root, k);
    }
  }

private:
  void splitChild(BTreeNode<Key>* x, int i) {
    BTreeNode<Key>* y = x->C[i];
    BTreeNode<Key>* z = new BTreeNode<Key>(t, y->leaf);
    z->n = t - 1;

    // copy keys
    for (int j = 0; j < t-1; ++j)
      z->key[j] = y->key[j + t];

    // copy children
    if (!y->leaf)
      for (int j = 0; j < t; ++j)
        z->C[j] = y->C[j + t];

    y->n = t - 1;

    // shift children of x
    for (int j = x->n; j >= i+1; --j)
      x->C[j+1] = x->C[j];
    x->C[i+1] = z;

    // shift keys of x
    for (int j = x->n-1; j >= i; --j)
      x->key[j+1] = x->key[j];
    x->key[i] = y->key[t-1];
    x->n += 1;
  }

  void insertNonFull(BTreeNode<Key>* x, Key k) {
    int i = x->n - 1;
    if (x->leaf) {
      // shift keys and insert
      while (i >= 0 && k < x->key[i]) {
        x->key[i+1] = x->key[i];
        --i;
      }
      x->key[i+1] = k;
      x->n += 1;
    } else {
      // find child
      while (i >= 0 && k < x->key[i]) --i;
      ++i;
      if (x->C[i]->n == 2*t - 1) {
        splitChild(x, i);
        if (k > x->key[i]) ++i;
      }
      insertNonFull(x->C[i], k);
    }
  }
};

int main() {
  BTree<int> T(3); // t = 3
  for (int k : {10, 20, 5, 6, 12, 30, 7, 17})
    T.insert(k);

  std::cout << "B-Tree traversal: ";
  T.traverse(); // outputs: 5 6 7 10 12 17 20 30
  return 0;
}
```

---

## ⏱️ Time Complexity

* **Search:** O(t·log_t n) ≃ O(log n)  
* **Insert/Delete:** O(t·log_t n) ≃ O(log n)  
* **Disk accesses minimized** by high fan-out (large *t*).

---

## 💾 Space Complexity

* **Total keys:** O(n)  
* **Tree height:** O(log_t n)  
* **Node size:** Each node stores up to 2t−1 keys and 2t children pointers.

---

## ✅ Advantages

* Low tree height → fewer disk reads  
* Balanced after every insertion/deletion  
* Supports range queries efficiently  

---

## ❌ Disadvantages

* More complex algorithm than binary trees  
* Overhead of splitting and merging nodes  
* Tuning *t* (page size) required for optimal performance  

---

## 💡 When to Use B-Trees

* Database and file-system indexing  
* On-disk or SSD-based storage structures  
* Large datasets that don’t fit in memory  

---

## 🚫 When NOT to Use B-Trees

* In-memory applications with small data (use AVL or RB-tree)  
* When simpler dynamic arrays or hash maps suffice  

---

## ⚔️ B-Tree vs. B+-Tree

| Feature               | B-Tree                           | B+-Tree                          |
| --------------------- | -------------------------------- | -------------------------------- |
| Key storage           | Internal + leaf nodes            | Leaf nodes only                  |
| Data pointers         | Stored with keys in nodes        | Leaf nodes; internal used for indexing |
| Range scan            | Moderate                         | Faster (linked leaves)           |
| Tree height           | Lower due to more keys/node      | Slightly higher                  |

---

## 🌍 Real-World Applications

1. Relational database indexes (MySQL, PostgreSQL)  
2. File systems (NTFS, ext4, HFS+)  
3. Key-value stores (Berkeley DB)  
4. Flash memory translation layers  

---

## 🛠️ Handling Special Cases and Edge Scenarios

* **Duplicate keys:** Decide on policy (allow duplicates in one node or reject).  
* **Deletion underflow:** Borrow from siblings or merge nodes to maintain key counts.  
* **Changing disk page size:** Adjust *t* to match block size for best I/O.  
