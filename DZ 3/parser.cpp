//
// Created by Антон Деев
//
#include "parser.h"
#include <cctype>
#include <cmath>
#include <stack>
using namespace std;

static bool isFunc(const string& s) {
    return s=="sin" || s=="cos" || s=="tg" || s=="ctg" || s=="exp";
}

static int pr(char op) {
    if (op=='~') return 3;
    if (op=='*' || op=='/') return 2;
    if (op=='+' || op=='-') return 1;
    return 0;
}

static bool rightAssoc(char op) { return op=='~'; }

bool tokenize(const string& s, vector<Tok>& a, string& err, bool& usedX) {
    a.clear(); err.clear(); usedX=false;

    auto bad = [&](string e){ err=e; return false; };

    TType prev = OP;

    for (int i=0; i<(int)s.size();) {
        if (isspace((unsigned char)s[i])) { i++; continue; }

        char c = s[i];

        if (isdigit((unsigned char)c) || c=='.') {
            int st = i;
            bool dot = (c=='.');
            i++;
            while (i<(int)s.size()) {
                char d = s[i];
                if (isdigit((unsigned char)d)) { i++; continue; }
                if (d=='.') {
                    if (dot) return bad("Ошибка: неверный формат числа (две точки).");
                    dot = true; i++; continue;
                }
                break;
            }
            string t = s.substr(st, i-st);
            if (t==".") return bad("Ошибка: одиночная точка не является числом.");

            double v = 0;
            try { v = stod(t); }
            catch(...) { return bad("Ошибка: не удалось разобрать число: " + t); }

            a.push_back({NUM, v, 0, ""});
            prev = NUM;
            continue;
        }

        if (isalpha((unsigned char)c)) {
            int st = i;
            i++;
            while (i<(int)s.size() && isalpha((unsigned char)s[i])) i++;
            string name = s.substr(st, i-st);

            if (name=="x") {
                a.push_back({VARX, 0, 0, ""});
                usedX = true;
                prev = VARX;
            } else if (isFunc(name)) {
                a.push_back({FUNC, 0, 0, name});
                prev = FUNC;
            } else {
                return bad("Ошибка: неизвестный идентификатор: " + name);
            }
            continue;
        }

        if (c=='(') { a.push_back({LP,0,0,""}); prev=LP; i++; continue; }
        if (c==')') { a.push_back({RP,0,0,""}); prev=RP; i++; continue; }

        if (c=='+' || c=='-' || c=='*' || c=='/') {
            if (c=='-') {
                bool unary = (a.empty() || prev==OP || prev==LP || prev==FUNC);
                a.push_back({OP,0,(unary?'~':'-'),""});
            } else {
                a.push_back({OP,0,c,""});
            }
            prev = OP;
            i++;
            continue;
        }

        return bad(string("Ошибка: недопустимый символ: '") + c + "'");
    }

    if (a.empty()) return bad("Ошибка: пустое выражение.");
    return true;
}

static bool checkOrder(const vector<Tok>& t, string& err) {
    auto isValueEnd = [&](const Tok& x){
        return x.type==NUM || x.type==VARX || x.type==RP;
    };
    auto isValueStart = [&](const Tok& x){
        return x.type==NUM || x.type==VARX || x.type==LP || x.type==FUNC;
    };

    if (t[0].type==OP && t[0].op!='~') {
        err = "Ошибка: выражение не может начинаться с бинарного оператора.";
        return false;
    }

    Tok last = t.back();
    if (last.type==OP || last.type==FUNC || last.type==LP) {
        err = "Ошибка: выражение не может заканчиваться оператором/функцией/'('.";
        return false;
    }

    for (int i=0; i+1<(int)t.size(); i++) {
        Tok a=t[i], b=t[i+1];

        if (isValueEnd(a) && isValueStart(b)) {
            err = "Ошибка: пропущен оператор между элементами выражения.";
            return false;
        }

        if (a.type==FUNC && b.type!=LP) {
            err = "Ошибка: после имени функции должна идти '('. Пример: sin(x).";
            return false;
        }

        if (a.type==LP && b.type==RP) {
            err = "Ошибка: пустые скобки '()' недопустимы.";
            return false;
        }

        if (a.type==OP && b.type==RP) {
            err = "Ошибка: оператор перед ')'.";
            return false;
        }

        if (a.type==LP && b.type==OP && b.op!='~') {
            err = "Ошибка: после '(' не может идти бинарный оператор.";
            return false;
        }

        if (a.type==OP) {
            if (!isValueStart(b) && !(b.type==OP && b.op=='~')) {
                err = "Ошибка: после оператора должен быть операнд.";
                return false;
            }
        }
    }

    return true;
}

bool toRPN(const vector<Tok>& tokens, vector<Tok>& rpn, string& err) {
    rpn.clear(); err.clear();
    if (!checkOrder(tokens, err)) return false;

    stack<Tok> st;
    int bal = 0;

    for (int i=0; i<(int)tokens.size(); i++) {
        Tok t = tokens[i];

        if (t.type==NUM || t.type==VARX) {
            rpn.push_back(t);
        }
        else if (t.type==FUNC) {
            st.push(t);
        }
        else if (t.type==OP) {
            while (!st.empty()) {
                Tok top = st.top();
                if (top.type==OP) {
                    int pTop = pr(top.op), pCur = pr(t.op);
                    bool popIt = (pTop > pCur) || (pTop==pCur && !rightAssoc(t.op));
                    if (popIt) { rpn.push_back(top); st.pop(); continue; }
                } else if (top.type==FUNC) {
                    rpn.push_back(top); st.pop(); continue;
                }
                break;
            }
            st.push(t);
        }
        else if (t.type==LP) {
            st.push(t);
            bal++;
        }
        else if (t.type==RP) {
            bal--;
            if (bal < 0) { err="Ошибка: лишняя ')'.";
                return false;
            }
            while (!st.empty() && st.top().type!=LP) {
                rpn.push_back(st.top());
                st.pop();
            }
            if (st.empty()) { err="Ошибка: несогласованные скобки."; return false; }
            st.pop();

            if (!st.empty() && st.top().type==FUNC) {
                rpn.push_back(st.top());
                st.pop();
            }
        }
    }

    if (bal!=0) { err="Ошибка: несогласованные скобки."; return false; }

    while (!st.empty()) {
        if (st.top().type==LP || st.top().type==RP) {
            err="Ошибка: несогласованные скобки.";
            return false;
        }
        rpn.push_back(st.top());
        st.pop();
    }

    return true;
}

bool evalRPN(const vector<Tok>& rpn, double xValue, bool usedX, double& out, string& err) {
    err.clear();
    vector<double> st;

    auto need = [&](int n){
        if ((int)st.size() < n) { err="Ошибка: недостаточно операндов (некорректное выражение)."; return false; }
        return true;
    };

    for (int i=0; i<(int)rpn.size(); i++) {
        Tok t = rpn[i];

        if (t.type==NUM) st.push_back(t.val);
        else if (t.type==VARX) st.push_back(xValue);
        else if (t.type==OP) {
            if (t.op=='~') {
                if (!need(1)) return false;
                double a = st.back(); st.pop_back();
                st.push_back(-a);
            } else {
                if (!need(2)) return false;
                double b = st.back(); st.pop_back();
                double a = st.back(); st.pop_back();

                if (t.op=='+') st.push_back(a+b);
                else if (t.op=='-') st.push_back(a-b);
                else if (t.op=='*') st.push_back(a*b);
                else if (t.op=='/') {
                    if (b==0) { err="Ошибка: деление на ноль."; return false; }
                    st.push_back(a/b);
                } else {
                    err="Ошибка: неизвестный оператор.";
                    return false;
                }
            }
        }
        else if (t.type==FUNC) {
            if (!need(1)) return false;
            double a = st.back(); st.pop_back();

            if (t.name=="sin") st.push_back(sin(a));
            else if (t.name=="cos") st.push_back(cos(a));
            else if (t.name=="tg") st.push_back(tan(a));
            else if (t.name=="ctg") {
                double ta = tan(a);
                if (ta==0) { err="Ошибка: ctg(x) не определен (tan(x)=0)."; return false; }
                st.push_back(1.0/ta);
            }
            else if (t.name=="exp") st.push_back(exp(a));
            else { err="Ошибка: неизвестная функция: " + t.name; return false; }
        }
        else {
            err="Ошибка: некорректный токен при вычислении.";
            return false;
        }
    }

    if (st.size()!=1) { err="Ошибка: выражение некорректно (остаток в стеке)."; return false; }
    out = st.back();
    return true;
}