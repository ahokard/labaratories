//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
using namespace std;
float mean(const vector<float>v) {
    int count=0, sum=0;

    for (int i=0; i < size(v); ++i) {
        sum += v[i];
        ++count;
    }
    cout << sum / count;
}

int main() {
    const vector<float>v {1, 2.1, 3.1, 4.1};
    mean(v);
}