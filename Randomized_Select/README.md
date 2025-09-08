# 📌 Randomized Select (Quickselect)

Randomized Select (Quickselect) finds the k-th smallest element in an unsorted array in expected linear time. It uses a randomized pivot to partition the array, then recurses only into the relevant side, avoiding the full sorting cost.

---

## 🔑 Key features and characteristics

- **Goal:** Find k-th order statistic (k-th smallest) without fully sorting.
- **Random pivot:** Reduces chance of pathological splits; expected linear time.
- **In-place:** Uses constant extra memory besides recursion stack.
- **Handles duplicates:** Works correctly even when many elements are equal.
- **STL-friendly:** Uses `vector`, `<algorithm>`, `<random>`.

---

## 🧭 Step-wise working

1. **Base case:** If the subarray has one element, return it.
2. **Random pivot:** Pick a random index p in [lo, hi], swap with a[hi].
3. **Partition:** Place pivot in final position `mid` so that:
   - all indices in [lo, mid-1] have values ≤ pivot
   - all indices in [mid+1, hi] have values > pivot
4. **Select side:** 
   - If k == mid, return a[mid].
   - If k < mid, recurse on [lo, mid-1].
   - Else recurse on [mid+1, hi].

> Indexing choice: In this README, k is 0-based (k = 0 returns the minimum).

---

## 🧾 Pseudocode

```plaintext
RandomizedSelect(A, lo, hi, k):
  if lo == hi: return A[lo]

  p = random integer in [lo, hi]
  swap A[p], A[hi]
  pivot = A[hi]

  // Lomuto partition
  i = lo - 1
  for j = lo to hi - 1:
    if A[j] <= pivot:
      i = i + 1
      swap A[i], A[j]
  swap A[i+1], A[hi]
  mid = i + 1

  if k == mid: return A[mid]
  else if k < mid: return RandomizedSelect(A, lo, mid - 1, k)
  else: return RandomizedSelect(A, mid + 1, hi, k)
```

---

## 🧑‍💻 C++ implementation (STL)

```cpp
#include <bits/stdc++.h>
using namespace std;

// Returns the k-th smallest (0-based) element in a, modifying the array in-place.
int randomized_select(vector<int>& a, int k) {
    if (a.empty() || k < 0 || k >= (int)a.size())
        throw invalid_argument("k out of range");

    random_device rd;
    mt19937 rng(rd());

    function<int(int,int)> select_rec = [&](int lo, int hi) -> int {
        if (lo == hi) return a[lo];

        uniform_int_distribution<int> dist(lo, hi);
        int p = dist(rng);
        swap(a[p], a[hi]);
        int pivot = a[hi];

        // Lomuto partition
        int i = lo - 1;
        for (int j = lo; j < hi; ++j) {
            if (a[j] <= pivot) {
                ++i;
                if (i != j) swap(a[i], a[j]);
            }
        }
        swap(a[i + 1], a[hi]);
        int mid = i + 1;

        if (k == mid) return a[mid];
        if (k < mid) return select_rec(lo, mid - 1);
        return select_rec(mid + 1, hi);
    };

    return select_rec(0, (int)a.size() - 1);
}

int main() {
    vector<int> a = {7, 1, 5, 3, 9, 2, 8, 6, 4, 0};
    int k = 4; // 0-based: the 5th smallest
    try {
        int val = randomized_select(a, k);
        cout << "k-th smallest (k=" << k << "): " << val << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }
    return 0;
}
```

---

## ⏱️ Time complexity

- **Expected:** O(n) due to random, balanced partitions on average.
- **Worst case:** O(n^2) if partitions are consistently skewed (rare with random pivot).
- **Per partition:** O(m) for a subarray of size m.

---

## 💾 Space complexity

- **Auxiliary space:** O(1) extra (in-place).
- **Recursion stack:** O(log n) expected; O(n) in the worst case.

---

## ✅ Advantages

- **Faster than sorting for single selection:** Expected linear time.
- **In-place:** Minimal memory footprint.
- **Robust:** Randomization prevents adversarial worst cases in practice.

---

## ❌ Disadvantages

- **Not stable:** Order among equals is not preserved.
- **Worst-case quadratic:** Still possible, albeit unlikely with random pivot.
- **Destructive:** Modifies the input array (can be avoided by copying first).

---

## 💡 When to use Randomized Select

- **Need only the k-th statistic:** Median, quartiles, or a single order statistic.
- **Large arrays:** Avoids O(n log n) cost of full sorting.
- **Streaming-ish workflows:** Paired with periodic sampling or bounded copies.

---

## 🛠️ Practical notes

- **Deterministic runs:** Replace `random_device` with a fixed seed for reproducible experiments.
- **Handling duplicates:** The `<=` in partition ensures all duplicates of pivot fall to the left side; correctness is preserved.
- **Non-destructive:** If you must keep original data, call on a copy: `auto b = a; randomized_select(b, k);`.

