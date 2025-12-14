//
// Created by Антон Деев
//
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
pair<float, float> minMax(const vector<float>v) {
    auto const [min, max] = minmax_element(v.begin(), v.end());
    if (v.empty()) {
        return {0, 0};
    }
    else {
        pair <double, double> w{*min, *max};
        return w;
    }
}
int main() {
    vector<float> v;
    cout << "Enter the number of elements in the array: ";
    int c;
    cin >> c;
    for (int i=0; i < c; ++i) {
        double a;
        cout << "Enter the element " << i+1 << ": ";
        cin >> a;
        v.push_back(a);
    }
    cout << "Min: " << minMax(v).first << endl;
    cout << "Max: " << minMax(v).second;
}