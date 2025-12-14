//
// Created by Антон Деев
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
using namespace std;

void error_exit(string msg) {
    cout << "ERROR: " << msg << endl;
    exit(1);
}

string trim(string s) {
    while (!s.empty() && (s[0] == ' ' || s[0] == '\t' || s[0] == '\n' || s[0] == '\r'))
        s.erase(0, 1);
    while (!s.empty() && (s[s.size()-1] == ' ' || s[s.size()-1] == '\t' || s[s.size()-1] == '\n' || s[s.size()-1] == '\r'))
        s.erase(s.size()-1, 1);
    return s;
}

vector<string> split_csv(string s) {
    vector<string> a;
    string part;
    stringstream ss(s);
    while (getline(ss, part, ',')) {
        a.push_back(trim(part));
    }
    if (a.size() == 1 && a[0] == "") a.clear();
    return a;
}

int to_int(string s, string msg) {
    s = trim(s);
    if (s == "") error_exit(msg);
    char *endp = 0;
    long v = strtol(s.c_str(), &endp, 10);
    if (endp == 0 || *endp != '\0') error_exit(msg);
    return (int)v;
}

struct Node {
    string val;
    Node* next;
    Node* prev;
    Node(string v) { val = v; next = 0; prev = 0; }
};

struct List {
    Node* head;
    Node* tail;
    int size;
    bool doubly;
    bool circular;

    List(bool d, bool c) {
        head = 0; tail = 0; size = 0;
        doubly = d; circular = c;
    }

    string marker() {
        if (!doubly && !circular) return ">";
        if (doubly && !circular) return "<>";
        if (!doubly && circular) return ">0";
        return "<>0";
    }

    void make_circle() {
        if (!circular) return;
        if (!head) return;
        tail->next = head;
        if (doubly) head->prev = tail;
    }

    void break_circle() {
        if (!circular) return;
        if (!head) return;
        tail->next = 0;
        if (doubly) head->prev = 0;
    }

    void push_back(string v) {
        Node* n = new Node(v);

        if (!head) {
            head = tail = n;
            size = 1;
            make_circle();
            return;
        }

        if (circular) break_circle();

        tail->next = n;
        if (doubly) n->prev = tail;
        tail = n;
        size++;

        make_circle();
    }

    void clear() {
        if (!head) { size = 0; return; }

        if (circular) break_circle();

        Node* cur = head;
        while (cur) {
            Node* nx = cur->next;
            delete cur;
            cur = nx;
        }
        head = tail = 0;
        size = 0;
    }

    void print() {
        if (!head) {
            cout << "(empty)" << endl;
            return;
        }
        cout << "Type: " << marker() << endl;
        cout << "Size: " << size << endl;
        cout << "Elements: ";

        Node* cur = head;
        for (int i = 0; i < size; i++) {
            cout << cur->val;
            if (i != size-1) cout << " -> ";
            cur = cur->next;
            if (!circular && cur == 0) break;
        }
        if (circular) cout << " -> (back to head)";
        cout << endl;
    }

    vector<int> find_all(string v) {
        vector<int> pos;
        Node* cur = head;
        for (int i = 0; i < size; i++) {
            if (!cur) break;
            if (cur->val == v) pos.push_back(i+1); // 1-based
            cur = cur->next;
            if (!circular && cur == 0) break;
        }
        return pos;
    }

    bool erase_first(string v) {
        if (!head) return false;

        if (circular) break_circle();

        Node* cur = head;
        while (cur) {
            if (cur->val == v) {
                Node* p = cur->prev;
                Node* n = cur->next;

                if (cur == head) head = n;
                if (cur == tail) tail = p;

                if (p) p->next = n;
                if (doubly && n) n->prev = p;

                delete cur;
                size--;

                if (size == 0) head = tail = 0;

                make_circle();
                return true;
            }
            cur = cur->next;
        }

        make_circle();
        return false;
    }

    int erase_all(string v) {
        int cnt = 0;
        while (erase_first(v)) cnt++;
        return cnt;
    }

    vector<string> to_vector() {
        vector<string> out;
        Node* cur = head;
        for (int i = 0; i < size; i++) {
            if (!cur) break;
            out.push_back(cur->val);
            cur = cur->next;
            if (!circular && cur == 0) break;
        }
        return out;
    }

    ~List() { clear(); }
};

List* make_by_t(int t) {
    if (t == 1) return new List(false, false);
    if (t == 2) return new List(true, false);
    if (t == 3) return new List(false, true);
    if (t == 4) return new List(true, true);
    error_exit("Invalid -t (must be 1..4)");
    return 0;
}

int t_from_marker(string m) {
    m = trim(m);
    if (m == ">") return 1;
    if (m == "<>") return 2;
    if (m == ">0") return 3;
    if (m == "<>0") return 4;
    return 0;
}

void save_file(List* lst, string filename) {
    ofstream f(filename.c_str());
    if (!f) error_exit("Cannot write file: " + filename);

    f << lst->marker() << "\n";
    f << lst->size << "\n";
    vector<string> a = lst->to_vector();
    for (int i = 0; i < (int)a.size(); i++) {
        f << a[i];
        if (i != (int)a.size()-1) f << ",";
    }
    f << "\n";
    f.close();
}

List* load_file(string filename) {
    ifstream f(filename.c_str());
    if (!f) error_exit("Cannot read file: " + filename);

    string m, lineCount, lineElems;
    if (!getline(f, m)) error_exit("Bad file: missing marker");
    if (!getline(f, lineCount)) error_exit("Bad file: missing count");
    if (!getline(f, lineElems)) error_exit("Bad file: missing elements");

    int t = t_from_marker(m);
    if (t == 0) error_exit("Bad file: unknown marker");

    int c = to_int(lineCount, "Bad file: count is not integer");
    if (c < 0) error_exit("Bad file: count < 0");

    vector<string> elems = split_csv(lineElems);
    if ((int)elems.size() != c) error_exit("Bad file: count != elements in csv");

    List* lst = make_by_t(t);
    for (int i = 0; i < c; i++) lst->push_back(elems[i]);

    f.close();
    return lst;
}

int main(int argc, char** argv) {
    int t = -1;
    int c = -1;
    string e = "";
    vector<string> seen;

    for (int i = 1; i < argc; i++) {
        string key = argv[i];

        if (key != "-t" && key != "-c" && key != "-e")
            error_exit("Unknown parameter: " + key);

        if (i + 1 >= argc) error_exit("Missing value after " + key);

        string val = argv[i+1];
        i++;

        if (key == "-t") t = to_int(val, "Bad -t value");
        if (key == "-c") c = to_int(val, "Bad -c value");
        if (key == "-e") e = val;
    }

    if (t == -1 || c == -1) error_exit("Required parameters: -t -c -e");
    if (c < 0) error_exit("-c must be >= 0");

    vector<string> elems = split_csv(e);
    if ((int)elems.size() != c) error_exit("Count in -c does not match number of elements in -e");

    List* lst = make_by_t(t);
    for (int i = 0; i < c; i++) lst->push_back(elems[i]);

    while (true) {
        cout << "\nMENU\n";
        cout << "1) Add element\n";
        cout << "2) Print list\n";
        cout << "3) Find element (all positions)\n";
        cout << "4) Delete element (first or all)\n";
        cout << "5) Delete whole list\n";
        cout << "6) Save list to file\n";
        cout << "7) Load list from file\n";
        cout << "0) Exit\n";
        cout << "Choose: ";

        string choiceLine;
        if (!getline(cin, choiceLine)) break;
        int ch = to_int(choiceLine, "Bad menu input");

        if (ch == 0) break;

        if (ch == 1) {
            cout << "Enter element value: ";
            string v; getline(cin, v);
            lst->push_back(trim(v));
            cout << "Added.\n";
        }
        else if (ch == 2) {
            lst->print();
        }
        else if (ch == 3) {
            cout << "Enter value to find: ";
            string v; getline(cin, v);
            v = trim(v);
            vector<int> pos = lst->find_all(v);
            if (pos.empty()) {
                cout << "Not found.\n";
            } else {
                cout << "Found at positions: ";
                for (int i = 0; i < (int)pos.size(); i++) {
                    cout << pos[i];
                    if (i != (int)pos.size()-1) cout << ", ";
                }
                cout << endl;
            }
        }
        else if (ch == 4) {
            cout << "Enter value to delete: ";
            string v; getline(cin, v);
            v = trim(v);

            cout << "1 - delete first, 2 - delete all: ";
            string modeLine; getline(cin, modeLine);
            int mode = to_int(modeLine, "Bad delete mode");

            if (mode == 1) {
                bool ok = lst->erase_first(v);
                if (ok) cout << "Deleted first occurrence.\n";
                else cout << "Value not found.\n";
            } else if (mode == 2) {
                int cnt = lst->erase_all(v);
                cout << "Deleted: " << cnt << endl;
            } else {
                cout << "Wrong mode.\n";
            }
        }
        else if (ch == 5) {
            lst->clear();
            cout << "List cleared.\n";
        }
        else if (ch == 6) {
            cout << "Enter filename: ";
            string fn; getline(cin, fn);
            fn = trim(fn);
            if (fn == "") { cout << "Empty filename.\n"; continue; }
            save_file(lst, fn);
            cout << "Saved.\n";
        }
        else if (ch == 7) {
            if (lst && lst->size > 0) {
                cout << "ERROR: list already exists in program. Clear it first.\n";
                continue;
            }

            cout << "Enter filename: ";
            string fn; getline(cin, fn);
            fn = trim(fn);
            if (fn == "") { cout << "Empty filename.\n"; continue; }

            delete lst;
            lst = 0;

            lst = load_file(fn);
            cout << "Loaded.\n";
        }
        else {
            cout << "Unknown menu command.\n";
        }
    }

    delete lst;
    return 0;
}