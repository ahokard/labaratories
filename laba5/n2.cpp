//
// Created by Антон Деев
//
#include "head.cpp"
float mean(const vector<unsigned>& rat) {
    float sum = 0;
    for (auto i : rat) {
        sum += i;
    }
    return sum/rat.size();
}
void SortByRating(vector<Student>& stud) {
    for (int i=0; i < stud.size(); i++) {
        for (int j=0; j < stud.size()-1-i; j++) {
            if (mean(stud[j].Ratings) < mean(stud[j+1].Ratings)) {
                swap(stud[j], stud[j+1]);
            }
        }
    }
}