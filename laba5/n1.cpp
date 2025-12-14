//
// Created by Антон Деев
//
#include "head.cpp"

void SortByName(vector<Student>& stud) {
    for (int i=0; i < stud.size(); i++) {
        for (int j=0; j< stud.size()-1-i;j++) {
            if (stud[j].Name > stud[j+1].Name)
                swap(stud[j], stud[j+1]);
        }
    }
}