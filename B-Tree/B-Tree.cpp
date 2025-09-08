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