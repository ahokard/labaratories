//
// Created by Антон Деев
//
#include <algorithm>
#include <iostream>
using namespace std;
#include <vector>
double argmax(vector<double>v) {
    if (v.empty()) {
        return -1;
    }else {
        double max;
        int index;
        max = *max_element(begin(v), end(v));
        index = *find(v.begin(), v.end(), max);
        return index;
    }
}
int main() {
    vector<double>v;
    cout << "Enter the number of elements in the array: ";
    int c;
    cin >> c;
    for (int i=0; i < c; ++i) {
        cout << "Enter the element " << i+1 << ":";
        double a;
        cin >> a;
        v.push_back(a);
    }
    cout << "The maximum element in the array: " << argmax(v);
}