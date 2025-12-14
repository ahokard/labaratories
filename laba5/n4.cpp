//
// Created by Антон Деев
//
#include "head.cpp"

size_t CountExcellent(const vector<Student> &stud) {
    size_t res = 0, c5 = 0;
    for (int i=0; i < stud.size(); i++) {
        c5 = 0;
        for (int j=0; j < (stud[i].Ratings).size(); j++) {
            if (stud[i].Ratings[j] == 5) {
                c5 += 1;}
        }
        if (c5 == stud[i].Ratings.size()) {
            res++;
        }
    }
    return res;
}