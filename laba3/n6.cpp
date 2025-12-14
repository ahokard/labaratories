//
// Created by Антон Деев
//
#include <iostream>
using namespace std;

int main() {
    string name1, name2;
    cin >> name1 >> name2;
    if (name1.length() > name2.length()) {
        cout << "True";
    }else {
        cout << "False";
    }
}