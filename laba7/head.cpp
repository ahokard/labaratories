//
// Created by Антон Деев
//
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <fstream>

using namespace std;

void saveToFile(const string& filename, const vector<string>& data);
void loadFromFile(const string& filename, vector<string>& outData);
struct Book {
    string Author;
    string Title;
    int Year;
};
void saveToFile(const string& filename, const vector<Book>& data);
void loadFromFile(const string& filename, vector<Book>& outData);
enum Score {
    Unsatisfactorily = 2,
    Satisfactorily,
    Good,
    Excellent
};
struct Student {
    string Name;
    int Year;
    map<string, Score> RecordBook;
};
using Groups = map<string, vector<Student>>;
void saveToFile(const string& filename, const Groups& groups);
void loadFromFile(const string& filename, Groups& outGroups);