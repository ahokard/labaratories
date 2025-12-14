//
// Created by Антон Деев
//
#include "head.h"

void saveToFile(const string& filename, const vector<Book>& data) {
    ofstream out(filename);
    if (!out.is_open())
        return;
    for (const auto& b : data) {
        out<<b.Author<<"\n";
        out<<b.Title<<"\n";
        out<<b.Year<<"\n";
    }
}

void loadFromFile(const string& filename, vector<Book>& outData) {
    ifstream in(filename);
    if (!in.is_open())
        return;
    outData.clear();
    string author;
    string title;
    int year;
    while (true) {
        if (!getline(in, author)) break;
        if (!getline(in, title))  break;
        string yearStr;
        if (!getline(in, yearStr)) break;
        year = stoi(yearStr);
        outData.push_back({author, title, year});
    }
}
int main() {
    vector<Book> books = {
        {"J. London", "Martin Eden", 1909},
        {"A. Conan Doyle", "Sherlock Holmes", 1892}
    };
    saveToFile("books.txt", books);
    vector<Book> loaded;
    loadFromFile("books.txt", loaded);
    for (const auto& b : loaded) {
        cout<<b.Author<<" | "<<b.Title<<" | "<<b.Year<<endl;
    }
    return 0;
}
