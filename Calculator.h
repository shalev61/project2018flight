#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>
#include <string>
#include <queue>
#include "Expression.h"
using namespace std;

class Calculator {
    vector<string> expression;
    int index;

    string readNextToken() { return this->expression[index++]; }
    bool isNextToken() { return this->index < this->expression.size(); }
    queue<string> shuntingYard();

    bool isNumeric(char c) { return (c >= '0' && c <= '9'); }
    bool isGreaterPrecedence(const string& c1, const string& c2) {
        return (c1 == "*" || c1 == "/" || ((c2 == "+" || c2 == "-") && (c1 == "+" || c1 == "-")));
    }
    Expression* makeExpression(Expression* left, Expression* right, const string& oper);
    string handleNegative(string expression);
    string handleAdjacentOperators(string expression);
public:
    Calculator(string expression);
    double calculate();
    ~Calculator() {
        this->expression.clear();
    }
};


#endif