# 📌 Randomized Quick Sort

Randomized Quick Sort is an in-place, divide-and-conquer sorting algorithm. It picks a pivot uniformly at random, partitions the array around the pivot, and recursively sorts the subarrays. Randomization avoids the adversarial inputs that cause worst-case behavior in classic Quick Sort.

---

## 🔑 Key features and characteristics

- **Random pivot:** Uniform random pivot selection reduces the chance of worst-case splits.
- **In-place partitioning:** Uses constant extra space aside from recursion stack.
- **Comparison counting:** We explicitly count element-to-pivot comparisons during partition.
- **STL-friendly:** Uses `vector`, `<algorithm>`, and `<random>` from the C++ STL.

---

## 🧭 Step-wise working

1. **Base check:** If the subarray has size 0 or 1, return.
2. **Random pivot:** Choose an index p uniformly from [lo, hi], swap arr[p] with arr[hi].
3. **Partition:** 
   - Use a partition scheme (here: Lomuto).
   - For j from lo to hi-1:
     - Increment comparisons by 1 for the check arr[j] <= pivot.
     - If true, move arr[j] into the “<= pivot” region.
   - Place pivot at its final position.
4. **Recurse:** Sort left [lo, pivot_idx - 1] and right [pivot_idx + 1, hi].

> Note on counting: We count only element-to-pivot comparisons inside partition. We do not count index bound checks or swaps.

---

<p align="center">
  <img src="https://github.com/uv-goswami/Advanced_Algo/blob/03037dfa4d1c6105ca1b8846c9bf6e2ee03481ea/Randomised_Quicksort/Randomised_QuickSort.png" alt="QuickSort" height="400px"/>
</p>

## 🧾 Pseudocode

```plaintext
RandomizedQuickSort(A, lo, hi, comps):
  if lo >= hi: return

  p = random integer in [lo, hi]
  swap A[p], A[hi]         // pivot is A[hi]
  pivot = A[hi]

  i = lo - 1
  for j = lo to hi - 1:
    comps += 1             // comparing A[j] to pivot
    if A[j] <= pivot:
      i += 1
      swap A[i], A[j]

  swap A[i+1], A[hi]
  mid = i + 1

  RandomizedQuickSort(A, lo, mid - 1, comps)
  RandomizedQuickSort(A, mid + 1, hi, comps)
```

---

## 🧑‍💻 C++ implementation (STL, counts comparisons)

```cpp
#include <bits/stdc++.h>
using namespace std;

struct QuickSortReport {
    long long comparisons = 0; // number of element-to-pivot comparisons
};

int partition_lomuto(vector<int>& a, int lo, int hi, mt19937& rng, QuickSortReport& rep) {
    // choose random pivot in [lo, hi] and move it to end
    uniform_int_distribution<int> dist(lo, hi);
    int p = dist(rng);
    swap(a[p], a[hi]);
    int pivot = a[hi];

    int i = lo - 1;
    for (int j = lo; j < hi; ++j) {
        rep.comparisons += 1;               // count A[j] <= pivot
        if (a[j] <= pivot) {
            ++i;
            if (i != j) swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[hi]);
    return i + 1;
}

void randomized_quicksort(vector<int>& a, int lo, int hi, mt19937& rng, QuickSortReport& rep) {
    if (lo >= hi) return;
    int mid = partition_lomuto(a, lo, hi, rng, rep);
    randomized_quicksort(a, lo, mid - 1, rng, rep);
    randomized_quicksort(a, mid + 1, hi, rng, rep);
}

QuickSortReport randomized_quicksort(vector<int>& a) {
    QuickSortReport rep;
    random_device rd;
    mt19937 rng(rd());
    if (!a.empty())
        randomized_quicksort(a, 0, (int)a.size() - 1, rng, rep);
    return rep;
}

int main() {
    vector<int> a = {9, 3, 7, 1, 8, 2, 5, 4, 6, 0};
    auto report = randomized_quicksort(a);

    cout << "Sorted: ";
    for (int x : a) cout << x << " ";
    cout << "\nComparisons: " << report.comparisons << "\n";
    return 0;
}
```

---

## ⏱️ Time complexity

- **Expected time:** O(n log n) due to random, balanced partitions on average.
- **Worst case:** O(n^2) if partitions are consistently unbalanced (rare with random pivot).
- **Partition cost:** Each partition performs (hi - lo) element-to-pivot comparisons.

> Expected number of comparisons across the whole run is proportional to n log n.

---

## 💾 Space complexity

- **Auxiliary space:** O(1) extra (in-place), excluding recursion stack.
- **Recursion stack:** O(log n) expected; O(n) in the worst case.

---

## ✅ Advantages

- **Fast in practice:** Excellent average performance and cache locality.
- **In-place:** Minimal extra memory.
- **Randomization:** Protects against adversarial inputs.

---

## ❌ Disadvantages

- **Unstable:** Does not preserve equal elements’ order.
- **Worst-case quadratic:** Although rare with random pivot, still possible.
- **Counting nuance:** Comparison count depends on the chosen partition scheme.

---

## 💡 Notes and variations

- **Partition scheme:** Lomuto is simple and counts are straightforward. Hoare’s partition uses fewer swaps but changes counting details.
- **Pivot strategies:** Median-of-three can reduce variance but is not truly random; pure random is simpler and robust.
- **Determinism:** To reproduce runs, replace `random_device` with a fixed seed for `mt19937`.

