#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int randomPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    
    int pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

int randomizedSelect(int arr[], int low, int high, int i) {
    if (low == high)
        return arr[low];
    
    int pi = randomPartition(arr, low, high);
    int k = pi - low + 1;
    
    if (i == k)
        return arr[pi];
    else if (i < k)
        return randomizedSelect(arr, low, pi - 1, i);
    else
        return randomizedSelect(arr, pi + 1, high, i - k);
}

int main() {
    srand(time(0));
    int n, i;
    cout << "Enter array size: ";
    cin >> n;
    
    int* arr = new int[n];
    cout << "Enter elements: ";
    for (int j = 0; j < n; j++)
        cin >> arr[j];
    
    cout << "Enter i (1 to " << n << "): ";
    cin >> i;
    
    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << i << "th smallest element: " << result << endl;
    
    delete[] arr;
    return 0;
}
