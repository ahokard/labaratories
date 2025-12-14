//
// Created by Антон Деев
//
#include <iostream>
using namespace std;
int main() {
    string chact;
    cin >> chact;
    int size = chact.length();
    for (int i = 0; i < size; i++) {
        chact= "*" +chact;
    }
    for (int i = 0; i < size; i++) {
        chact = chact + "*";
    }
    cout << chact;
}