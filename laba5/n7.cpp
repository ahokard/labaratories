//
// Created by Антон Деев
//
#include "head.cpp"
vector<Group> Groups(const vector<Student>& stud) {
    vector<Group> group;
    int c =0;
    for (int i=0; i < stud.size(); i++) {
        c = 0;
        for (int j=0; j < group.size(); j++) {
            if (stud[i].GroupId == group[j].Id) {
                c = 1;
                group[j].Students.push_back(stud[i]);
            }
        }
        if (c == 0) {
            Group Gr;
            Gr.Id = stud[i].GroupId;
            Gr.Students.push_back(stud[i]);
            group.push_back(Gr);
        }
    }
    return group;
}