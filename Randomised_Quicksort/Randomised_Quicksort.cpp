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