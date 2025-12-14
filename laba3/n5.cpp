//
// Created by Антон Деев
//
#include <iostream>
using namespace std;
int main() {
    string city;
    cin >> city;
    if (city.length() % 2 == 0) {
        cout << "Четное";
    } else {
        cout << "Нечетное";
    }
}