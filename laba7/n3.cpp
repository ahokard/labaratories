//
// Created by Антон Деев
//
#include "head.cpp"

void saveToFile(const string& filename, const Groups& groups) {
    ofstream out(filename);
    if (!out.is_open())
        return;
    for (const auto& g : groups) {
        out<<"GROUP "<<g.first<<"\n";
        for (const auto& st : g.second) {
            out<<"STUDENT "<<st.Name<<"\n";
            out<<"YEAR "<<st.Year<<"\n";
            out<<"RECORDS "<<st.RecordBook.size()<<"\n";
            for (const auto& rec : st.RecordBook)
                out<<rec.first<<" "<<rec.second<<"\n";
            out<<"ENDSTUDENT\n";
        }
        out<<"ENDGROUP\n";
    }
}

void loadFromFile(const string& filename, Groups& outGroups) {
    ifstream in(filename);
    if (!in.is_open())
        return;
    outGroups.clear();
    string word;
    Groups result;
    while (in>>word) {
        if (word == "GROUP") {
            string groupName;
            in>>groupName;
            vector<Student> students;
            while (in>>word && word != "ENDGROUP") {
                if (word == "STUDENT") {
                    Student st;
                    in>>st.Name;
                    in>>word;
                    in>>st.Year;
                    in>>word;
                    int count;
                    in>>count;
                    st.RecordBook.clear();
                    for (int i = 0; i < count; i++) {
                        string subject;
                        int score;
                        in>>subject>>score;
                        st.RecordBook[subject] = (Score)score;
                    }
                    in>>word;
                    students.push_back(st);
                }
            }
            result[groupName] = students;
        }
    }
    outGroups = move(result);
}
int main() {
    Groups groups;
    groups["PV-21"] = {
            {"Ivanov", 2021, { {"Math", Excellent}, {"History", Good} }},
            {"Petrov", 2021, { {"Math", Good}, {"History", Satisfactorily} }}
    };
    saveToFile("groups.txt", groups);
    Groups loaded;
    loadFromFile("groups.txt", loaded);
    for (auto& g : loaded) {
        cout<<"Group: "<<g.first<<endl;
        for (auto& st : g.second) {
            cout<<"  "<<st.Name<<" ("<<st.Year<<")\n";
            for (auto& rec : st.RecordBook)
                cout<<"    "<<rec.first<<": "<<rec.second<<"\n";
        }
    }
    return 0;
}