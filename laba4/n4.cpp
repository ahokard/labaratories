//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
using namespace std;
double sort(vector<double>v) {
    if (v.empty()) {
        cout << "Array is empty";
        return 0;
    }
    for (int i=0; i < size(v); ++i) {
        for (int j=0; j < size(v); ++j) {
            while (v[j] < v[j+1]) {
                double c;
                c = v[j];
                v[j] = v[j+1];
                v[j+1] = c;
            }
        }
    }
    for (int i=0; i < size(v); ++i) {
        cout << v[i] << " ";
    }
}
int main() {
    vector<double>v;
    cout << "Enter the number of elements in the array: ";
    int a;
    cin >> a;
    for (int i=0; i < a; ++i) {
        cout << "Enter the element " << i+1 << ": ";
        double c;
        cin >> c;
        v.push_back(c);
    }
    sort(v);
}