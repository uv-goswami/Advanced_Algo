#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int low, int high, int pivotIndex) {
    int pivotValue = arr[pivotIndex];
    swap(arr[pivotIndex], arr[high]);
    int storeIndex = low;
    for (int i = low; i < high; ++i) {
        if (arr[i] < pivotValue) {
            swap(arr[storeIndex], arr[i]);
            ++storeIndex;
        }
    }
    swap(arr[storeIndex], arr[high]);
    return storeIndex;
}

int randomized_select(vector<int>& arr, int low, int high, int k) {
    static random_device rd;
    static mt19937 gen(rd());
    while (true) {
        int n = high - low + 1;
        if (n == 1) return arr[low];
        uniform_int_distribution<int> dist(low, high);
        int pivotIndex = dist(gen);
        int mid = partition(arr, low, high, pivotIndex);
        int pivotPos = mid - low;
        if (k == pivotPos)
            return arr[mid];
        else if (k < pivotPos)
            high = mid - 1;
        else {
            k -= (pivotPos + 1);
            low = mid + 1;
        }
    }
}

int main() {
    vector<int> data = {7, 2, 9, 4, 1, 6};
    int k;
    cout << "Enter k (0-based index): ";
    cin >> k;
    if (k < 0 || k >= (int)data.size()) {
        cout << "Invalid k\n";
        return 1;
    }
    int value = randomized_select(data, 0, data.size() - 1, k);
    cout << k << "-th smallest: " << value << endl;
    return 0;
}
