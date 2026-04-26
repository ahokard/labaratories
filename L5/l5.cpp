#include <iostream>
#include <fstream>
#include <deque>
#include <list>
#include <algorithm>
#include <string>

using namespace std;

struct Employee {
    string fio;
    string date;
    string position;
    double salary;
};

ostream& operator<<(ostream& out, const Employee& e) {
    out << e.fio << " | " << e.date << " | "
        << e.position << " | " << e.salary;
    return out;
}

bool compare(Employee a, Employee b) {
    return a.fio < b.fio;
}

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    if (!fin.is_open()) {
        cout << "input.txt ne naiden" << endl;
        return 1;
    }

    if (!fout.is_open()) {
        cout << "output.txt ne sozdan" << endl;
        return 1;
    }

    deque<Employee> d;
    list<Employee> l;

    int n;
    fin >> n;
    fin.ignore(1000, '\n');

    for (int i = 0; i < n; i++) {
        Employee e;

        getline(fin, e.fio);
        getline(fin, e.date);
        getline(fin, e.position);
        fin >> e.salary;
        fin.ignore(1000, '\n');

        d.push_back(e);
    }

    fout << "Ishodniy deque:" << endl;
    for (Employee e : d) {
        fout << e << endl;
    }

    copy(d.begin(), d.end(), back_inserter(l));

    sort(d.begin(), d.end(), compare);

    fout << endl << "Deque posle sortirovki po FIO:" << endl;
    for (Employee e : d) {
        fout << e << endl;
    }

    fout << endl << "Skopirovanniy list:" << endl;
    for (Employee e : l) {
        fout << e << endl;
    }

    fin.close();
    fout.close();

    cout << "Programma srabotala. Prover output.txt" << endl;

    return 0;
}