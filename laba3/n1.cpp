//
// Created by Антон Деев
//
#include <iostream>
using namespace std;

int main() {
    int mass[] = {1, 2, 3};
    int size, a;
    cout << "i. ";
    size = sizeof(mass)/sizeof(mass[0]);
    for (int i=0; i < size; ++i) {
        mass[i] = mass[i] * 2;
        cout << mass[i];
    }

    cout << endl;
    cout << "a = ";
    cin >> a;
    cout << "ii. ";
    for (int i=0; i < size; ++i) {
        mass[i] = mass[i] - a;
        cout << mass[i];
    }
    cout << endl;
    cout << "iii. ";

    for (int i=0; i < size; ++i) {
        mass[i] = mass[i]/mass[0];
        cout << mass[i] << " ";
    }
}