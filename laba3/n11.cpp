//
// Created by Антон Деев
//
#include <iostream>
using namespace std;

int main() {
    string let = "can you can a can as a canner can can a can?";
    string new_word;
    cin >> new_word;
    string result = "";
    string prom = "";

    for (int i = 0; i < let.length(); i++) {
        if (isalpha(let[i])) {
            prom += let[i];
        } else {
            if (prom== "can") {
                result += new_word;
            }else {
                result += prom;
            }
            result += let[i];
            prom= "";
        }
    }
    cout << result << endl;


}