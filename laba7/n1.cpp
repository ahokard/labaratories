//
// Created by Антон Деев
//
#include "head.cpp"

void saveToFile(const string& filename, const vector<string>& data) {
    ofstream out(filename);
    if (!out.is_open())
        return;
    for (const auto& s : data)
        out<<s<<"\n";
}

void loadFromFile(const string& filename, vector<string>& outData) {
    ifstream in(filename);
    if (!in.is_open())
        return;
    outData.clear();
    string line;
    while (getline(in, line))
        outData.push_back(line);
}

int main() {
    vector<string> words = {"apple", "banana", "carrot"};
    saveToFile("data.txt", words);
    vector<string> loaded;
    loadFromFile("data.txt", loaded);
    for (const auto& w : loaded)
        cout<<w<<endl;

    return 0;
}