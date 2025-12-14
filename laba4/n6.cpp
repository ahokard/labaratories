//
// Created by Антон Деев
//
#include <iostream>
#include <string>
using namespace std;
string replace(const string& str, const string& old, const string& new_string) {
    string result = str;
    size_t pos = 0;
    while ((pos = result.find(old, pos)) != string::npos) {
        result.replace(pos, old.length(), new_string);
        pos += new_string.length();
    }
    return result;
}

int main() {
    string newString = replace("Can you can a can as a canner can can a can?", "can", "cAN");
    cout << newString;
}