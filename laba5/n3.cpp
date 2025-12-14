//
// Created by Антон Деев
//
#include "head.cpp"

size_t CountTwoness(const vector<Student>& stud) {
    size_t res = 0;
    for (int i=0; i < stud.size(); i++) {
        for (int j=0; j < stud[i].Ratings.size(); j++){
            if (stud[i].Ratings[j] == 2) {
                res += 1;
                break;
            }
        }
    }
    return res;
}