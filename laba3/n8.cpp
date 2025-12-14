//
// Created by Антон Деев
//
#include <iostream>
using namespace std;

int main() {
    string chact;
    cin >> chact;
    int m, n;
    cin >> m >> n;
    for (int i = m-1; i < n; i++) {
        cout << chact[i];
    }
}