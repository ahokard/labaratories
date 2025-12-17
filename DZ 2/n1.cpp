//
// Created by Антон Деев
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Node {
    string data;
    Node* next;
    Node(string d): data(d), next(nullptr) {}
};

struct DNode {
    string data;
    DNode* next;
    DNode* prev;
    DNode(string d): data(d), next(nullptr), prev(nullptr) {}
};

int listType = 0;
bool listExists = false;
Node* head = nullptr;
DNode* dhead = nullptr;

void error(string m) {
    cout << "Ошибка: " << m << endl;
    exit(1);
}

void createList(vector<string> e) {
    if (listExists) return;
    if (listType == 1 || listType == 3) {
        Node* last = nullptr;
        for (auto &x : e) {
            Node* n = new Node(x);
            if (!head) head = n;
            else last->next = n;
            last = n;
        }
        if (listType == 3 && last) last->next = head;
    } else {
        DNode* last = nullptr;
        for (auto &x : e) {
            DNode* n = new DNode(x);
            if (!dhead) dhead = n;
            else { last->next = n; n->prev = last; }
            last = n;
        }
        if (listType == 4 && last) { last->next = dhead; dhead->prev = last; }
    }
    listExists = true;
}

void printList() {
    if (!listExists) return;
    if (listType == 1 || listType == 3) {
        Node* c = head;
        do {
            cout << c->data << " ";
            c = c->next;
        } while (c && (listType != 3 || c != head));
    } else {
        DNode* c = dhead;
        do {
            cout << c->data << " ";
            c = c->next;
        } while (c && (listType != 4 || c != dhead));
    }
    cout << endl;
}

void findElement(string v) {
    if (!listExists) return;
    vector<int> pos; int i = 0;
    if (listType == 1 || listType == 3) {
        Node* c = head;
        do {
            if (c->data == v) pos.push_back(i);
            c = c->next; i++;
        } while (c && (listType != 3 || c != head));
    } else {
        DNode* c = dhead;
        do {
            if (c->data == v) pos.push_back(i);
            c = c->next; i++;
        } while (c && (listType != 4 || c != dhead));
    }
    if (pos.empty()) cout << "Не найдено" << endl;
    else { for (int p : pos) cout << p << " "; cout << endl; }
}

void addElement(string v) {
    if (!listExists) return;
    if (listType == 1 || listType == 3) {
        Node* c = head;
        while (c->next && (listType != 3 || c->next != head)) c = c->next;
        Node* n = new Node(v);
        c->next = n;
        if (listType == 3) n->next = head;
    } else {
        DNode* c = dhead;
        while (c->next && (listType != 4 || c->next != dhead)) c = c->next;
        DNode* n = new DNode(v);
        c->next = n;
        n->prev = c;
        if (listType == 4) { n->next = dhead; dhead->prev = n; }
    }
}

void deleteElement(string v, bool all) {
    if (!listExists) return;
    if (listType == 1 || listType == 3) {
        Node* c = head; Node* p = nullptr;
        do {
            if (c->data == v) {
                if (p) p->next = c->next; else head = c->next;
                Node* t = c; c = c->next; delete t;
                if (!all) break;
            } else { p = c; c = c->next; }
        } while (c && (listType != 3 || c != head));
    } else {
        DNode* c = dhead;
        do {
            if (c->data == v) {
                if (c->prev) c->prev->next = c->next; else dhead = c->next;
                if (c->next) c->next->prev = c->prev;
                DNode* t = c; c = c->next; delete t;
                if (!all) break;
            } else c = c->next;
        } while (c && (listType != 4 || c != dhead));
    }
}

void deleteList() {
    if (!listExists) return;
    if (listType == 1 || listType == 3) {
        Node* c = head;
        do { Node* t = c; c = c->next; delete t; } while (c && (listType != 3 || c != head));
        head = nullptr;
    } else {
        DNode* c = dhead;
        do { DNode* t = c; c = c->next; delete t; } while (c && (listType != 4 || c != dhead));
        dhead = nullptr;
    }
    listExists = false;
}

void saveToFile(string f) {
    if (!listExists) return;
    ofstream o(f);
    string t = listType==1?">":listType==2?"<>":listType==3?">0":"<>0";
    o << t << endl;
    if (listType == 1 || listType == 3) {
        Node* c = head;
        do { o << c->data << ","; c = c->next; } while (c && (listType != 3 || c != head));
    } else {
        DNode* c = dhead;
        do { o << c->data << ","; c = c->next; } while (c && (listType != 4 || c != dhead));
    }
    o.close();
}

void loadFromFile(string f) {
    if (listExists) { cout << "Удалите текущий список" << endl; return; }
    ifstream i(f);
    if (!i) { cout << "Нет файла" << endl; return; }
    string t; getline(i,t);
    if (t==">") listType=1; else if (t=="<>") listType=2; else if (t==">0") listType=3; else listType=4;
    string line; getline(i,line);
    stringstream ss(line); string v; vector<string> e;
    while (getline(ss,v,',')) if (!v.empty()) e.push_back(v);
    createList(e);
}

void menu() {
    while (true) {
        cout << "\n1.Показать\n2.Добавить\n3.Найти\n4.Удалить\n5.Удалить все\n6.Удалить список\n7.Сохранить\n8.Считать\n0.Выход\n>";
        int c; cin >> c;
        if (c==0) break;
        string v,f;
        if (c==1) printList();
        else if (c==2){cout<<"Значение:";cin>>v;addElement(v);}
        else if (c==3){cout<<"Значение:";cin>>v;findElement(v);}
        else if (c==4){cout<<"Значение:";cin>>v;deleteElement(v,false);}
        else if (c==5){cout<<"Значение:";cin>>v;deleteElement(v,true);}
        else if (c==6) deleteList();
        else if (c==7){cout<<"Файл:";cin>>f;saveToFile(f);}
        else if (c==8){cout<<"Файл:";cin>>f;loadFromFile(f);}
    }
}

int main(int argc,char* argv[]) {
    if (argc!=7) error("Неверные параметры");
    string t=argv[1], c=argv[3], e=argv[5];
    if (t!="-t"||c!="-c"||e!="-e") error("Неверный формат");
    listType=stoi(argv[2]);
    int count=stoi(argv[4]);
    string s=argv[6]; stringstream ss(s); string x; vector<string> arr;
    while (getline(ss,x,',')) arr.push_back(x);
    if (arr.size()!=count) error("Не совпадает количество");
    createList(arr);
    menu();
    return 0;
}
