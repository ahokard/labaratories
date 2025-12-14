//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<string> split(const string& str, char sep) {
    vector<string> result;
    if (str.empty()) {
        return result;
    }
    bool only_separators = true;
    for (char c : str) {
        if (c != sep) {
            only_separators = false;
            break;
        }
    }
    if (only_separators) {
        return result;
    }

    size_t start = 0;
    size_t end = str.find(sep);

    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));
        start = end + 1;
        end = str.find(sep, start);
    }
    result.push_back(str.substr(start));
    return result;
}

int main() {
    vector<string> arr = split("Can you can a can as a canner can can a can?", ' ');
    for (const auto& word : arr) {
        cout << "\"" << word << "\" ";
    }
    cout << endl;
}