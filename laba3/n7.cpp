//
// Created by Антон Деев
//
#include <iostream>
using namespace std;
int main() {
    string city1, city2, city3, longest, shortest;
    cin >> city1 >> city2 >> city3;
    longest = city1;
    shortest = city1;
    if (city2.length() > longest.length()) {
        longest = city2;
    }
    if (city3.length() > longest.length()) {
        longest = city3;
    }


    if (city2.length() < shortest.length()) {
        shortest = city2;
    }
    if (city3.length() < shortest.length()) {
        shortest = city3;
    }

    cout << "Самое длинное " << longest << endl;
    cout << "Свмое короткое" << shortest << endl;
}