#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "quicksort.h"

using namespace std;

// ----------------------------------
// Trim Whitespace from String
// ----------------------------------
inline string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) {
        return str;
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}

// ----------------------------------
// Read Products from File
// ----------------------------------
inline vector<Product> readProductsFromFile(const string& filename) {
    vector<Product> products;
    ifstream fin(filename);

    if (!fin.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return products;
    }

    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string name, priceStr, ratingStr;

        getline(ss, name, '|');
        getline(ss, priceStr, '|');
        getline(ss, ratingStr);

        // Trim whitespace
        name = trim(name);
        priceStr = trim(priceStr);
        ratingStr = trim(ratingStr);

        try {
            Product p;
            p.name = name;
            p.price = stod(priceStr);
            p.rating = stod(ratingStr);
            products.push_back(p);
        } catch (exception& e) {
            cerr << "Error parsing line: " << line << endl;
        }
    }

    fin.close();
    return products;
}

// ----------------------------------
// Write Products to File
// ----------------------------------
inline bool writeProductsToFile(const string& filename, const vector<Product>& products) {
    ofstream fout(filename);

    if (!fout.is_open()) {
        cerr << "Error: Could not open " << filename << " for writing" << endl;
        return false;
    }

    for (const auto& p : products) {
        fout << p.name << " | "
             << p.price << " | "
             << p.rating << endl;
    }

    fout.close();
    return true;
}

#endif // FILE_UTILS_H
