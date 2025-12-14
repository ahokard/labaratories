//
// Created by Антон Деев
//
//
// Created by donts on 25.11.2025.
//

#ifndef laba5
#define laba5
#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct Student {
    string Name;
    string GroupId;
    vector <unsigned> Ratings;
    vector <string> Subjects;
};

struct Group {
    string Id;
    vector<Student> Students;
};


void SortByName(vector<Student>&);
float mean(const vector<unsigned>&);
void SortByRating(vector<Student>&);
size_t CountTwoness(const vector<Student>&);
size_t CountExcellent(const vector<Student>&);
vector<Student> VectorMathExcellent(const vector<Student>&);
vector <string> GroupsId(const vector<Student>&);
vector<Group> Groups(const vector<Student>&);


#endif