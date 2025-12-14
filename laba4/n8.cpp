//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
using namespace std;
string join(const vector<string>& arr, const string& sep) {
    if (arr.empty()) {
        return "";
    }
    std::string result;
    result += arr[0];
    for (size_t i = 1; i < arr.size(); ++i) {
        result += sep;
        result += arr[i];
    }
    return result;
}
int main() {
    vector<string>v;
    cout << "Enter the number of words per line:";
    int c;
    cin >> c;
    for (int i=0; i < c; ++i) {
        cout << "Enter the word " << i + 1 << ":";
        string word;
        cin >> word;
        v.push_back(word);
    }
    string sep;
    cout << "Enter a separator:";
    cin >> sep;
    cout << join(v, sep);
}