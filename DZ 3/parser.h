//
// Created by Антон Деев
//
#pragma once
#include <string>
#include <vector>
#include "token.h"
using namespace std;

bool tokenize(const string& s, vector<Tok>& tokens, string& err, bool& usedX);

bool toRPN(const vector<Tok>& tokens, vector<Tok>& rpn, string& err);

bool evalRPN(const vector<Tok>& rpn, double xValue, bool usedX, double& out, string& err);