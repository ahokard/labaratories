//
// Created by Антон Деев
//
#include <iostream>
using namespace std;

int main() {
    int mass[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    int first, second, third, last1, last2, last3;
    first = mass[0];
    second = mass[1];
    third = mass[2];
    last3 = mass[17];
    last2 = mass[18];
    last1 = mass[19];
    mass[0] = last3;
    mass[1] = last2;
    mass[2] = last1;
    mass[17] = first;
    mass[18] = second;
    mass[19] = third;
    int size = sizeof(mass) / sizeof(mass[0]);
    for (int i=0;i < size;i++) {
        cout << mass[i] << " ";
    }

}