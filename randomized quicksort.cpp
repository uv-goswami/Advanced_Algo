
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

long long comparisons = 0;
int randomPartition(vector<int>& arr, int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = randomPartition(arr, low, high);  
        randomizedQuickSort(arr, low, pi - 1);     
        randomizedQuickSort(arr, pi + 1, high);    
    }
}


int main() {
    srand(time(0));  
    int n;
    cout << "Enter array size: ";
    cin >> n;

    vector<int> arr(n);  
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    comparisons = 0;  
    randomizedQuickSort(arr, 0, n - 1);  

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\nTotal comparisons: " << comparisons << endl;

    return 0;  
}
