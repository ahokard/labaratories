//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
using namespace std;

double remove_first_negative_element(vector<double>v) {
    double removed_element=0;
    for (int i=0; i < size(v); ++i) {
        if (v[i] < 0) {
            removed_element = v[i];
            erase(v, v[i]);
            cout << removed_element;
            return true;
        }
    }
}
int main() {
    vector<double>v;
    int a;
    cout << "Enter the number of elements in the array: ";
    cin >> a;
    for (int i=0; i < a; ++i) {
        double c;
        cout << "Enter the element " << i+1 << ":";
        cin >> c;
        v.push_back(c);
    }
    remove_first_negative_element(v);
}