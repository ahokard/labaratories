//
// Created by Антон Деев
//
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include "parser.h"
using namespace std;

int main() {
    cout << "Строковый калькулятор\n";
    cout << "Операции: + - * /, скобки (), функции sin cos tg ctg exp, переменная x\n";
    cout << "Пример: cos(x-5)*10/(2*x-5)\n\n";

    cout << "Введите выражение:\n";
    string expr;
    getline(cin, expr);

    vector<Tok> tokens, rpn;
    string err;
    bool usedX = false;

    if (!tokenize(expr, tokens, err, usedX)) {
        cout << err << "\n";
        return 0;
    }

    if (!toRPN(tokens, rpn, err)) {
        cout << err << "\n";
        return 0;
    }

    double xValue = 0;
    if (usedX) {
        cout << "В выражении есть x.\nВведите x = ";
        if (!(cin >> xValue)) {
            cout << "Ошибка: не удалось прочитать x.\n";
            return 0;
        }
    }

    double ans = 0;
    if (!evalRPN(rpn, xValue, usedX, ans, err)) {
        cout << err << "\n";
        return 0;
    }

    cout << setprecision(15);
    cout << "Результат: " << ans << "\n";
    return 0;
}