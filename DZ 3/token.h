//
// Created by Антон Деев
//
#pragma once
#include <string>
using namespace std;

enum TType { NUM, VARX, OP, LP, RP, FUNC };

struct Tok {
    TType type;
    double val;
    char op;
    string name;
};