//
// Created by Антон Деев
//
#include "head.cpp"
vector<Student> VectorMathExcellent(const vector<Student>& stud) {
    vector<Student> res;
    for (int i=0; i < stud.size(); i++) {
        for (int j=0; j < stud[i].Subjects.size(); j++) {
            if ("Math" ==  stud[i].Subjects[j] and stud[i].Ratings[j] == 5){
                res.push_back(stud[i]);
            }
        }
    }
    return res;
}