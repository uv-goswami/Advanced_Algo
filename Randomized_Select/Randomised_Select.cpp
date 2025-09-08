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