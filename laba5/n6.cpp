//
// Created by Антон Деев
//
#include "head.cpp"
vector <string> GroupsId(const vector<Student>& stud) {
    vector <string> res;
    for (int i=0; i < stud.size();i++) {
        int c = 0;
        for (int j=0; j < stud.size();j++) {
            if (stud[i].GroupId == stud[j].GroupId)
                c++;
        }
        if (c == 1) {
            res.push_back(stud[i].GroupId);
        }
    }
    return res;
}