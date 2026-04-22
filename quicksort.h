#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <vector>
#include <algorithm>

using namespace std;

// ----------------------------------
// Product Structure
// ----------------------------------
struct Product {
    string name;
    double price;
    double rating;
};

// ----------------------------------
// Global Choice for Sorting
// ----------------------------------
extern int sortChoice;

// ----------------------------------
// Comparison Function
// ----------------------------------
inline bool compareProduct(const Product& a, const Product& b) {
    // 1. Product Name A-Z
    if (sortChoice == 1)
        return a.name < b.name;
    // 2. Price Low to High
    else if (sortChoice == 2)
        return a.price < b.price;
    // 3. Price High to Low
    else if (sortChoice == 3)
        return a.price > b.price;
    // 4. Rating High to Low
    else if (sortChoice == 4)
        return a.rating > b.rating;
    // 5. Rating Low to High
    else if (sortChoice == 5)
        return a.rating < b.rating;
    // Default
    return a.name < b.name;
}

// ----------------------------------
// Partition for QuickSort
// ----------------------------------
inline int partition(vector<Product>& arr, int low, int high) {
    Product pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (compareProduct(arr[j], pivot)) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// ----------------------------------
// QuickSort Function
// ----------------------------------
inline void quickSort(vector<Product>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// ----------------------------------
// Merge Two Sorted Lists
// ----------------------------------
inline vector<Product> mergeSorted(vector<Product>& a, vector<Product>& b) {
    vector<Product> result;
    size_t i = 0, j = 0;

    while (i < a.size() && j < b.size()) {
        if (compareProduct(a[i], b[j]))
            result.push_back(a[i++]);
        else
            result.push_back(b[j++]);
    }

    while (i < a.size()) result.push_back(a[i++]);
    while (j < b.size()) result.push_back(b[j++]);

    return result;
}

#endif // QUICKSORT_H
