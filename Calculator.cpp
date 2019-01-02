#include "Calculator.h"
#include <stack>
#include "Expression.h"
#include <stdlib.h>
#include "ExpressionTypes.h"

queue<string> Calculator::shuntingYard() {
    stack<string> eStack;
    queue<string> eQueue;
    while (this->isNextToken()) {
        string token = this->readNextToken();
        if (isNumeric(token.at(0))) { // if token is a number
            eQueue.push(token);
        } else if (token == "(") { // if token is "("
            eStack.push("(");
        } else if (token == ")") { // if token is ")"
            while (eStack.top() != "(") {
                eQueue.push(eStack.top());
                eStack.pop();
            }
            // pop "("
            eStack.pop();
        } else { // if token is an operator
            while (!eStack.empty() && isGreaterPrecedence(eStack.top(), token)) {
                eQueue.push(eStack.top());
                eStack.pop();
            }
            eStack.push(token);
        }
    }
    while (!eStack.empty()) {
        eQueue.push(eStack.top());
        eStack.pop();
    }
    this->index = 0;

    return eQueue;
}

double Calculator::calculate() {
    queue<string> eQueue = this->shuntingYard();
    stack<Expression*> eStack;
    while (!eQueue.empty()) {
        string token = eQueue.front();
        eQueue.pop();
        if (isNumeric(token.at(0))) { // if token is a number
            eStack.push(new Number(atof(token.c_str())));
        } else {
            Expression* right = eStack.top();
            eStack.pop();
            Expression* left = eStack.top();
            eStack.pop();
            Expression* e = makeExpression(left, right, token);
            eStack.push(e);
        }
    }
    return eStack.top()->calculate();
}

Calculator::Calculator(string expression) {
    expression = handleNegative(expression);
    expression = handleAdjacentOperators(expression);

    this->index = 0;
    vector<string> eVector;
    int i = 0;
    while (i < expression.size()) {
        if (isNumeric(expression.at(i))) {
            string number = "";
            while (i < expression.size() && (isNumeric(expression.at(i)) || (expression.at(i) == '.'))) {
                number.push_back(expression.at(i++));
            }
            eVector.push_back(number);
        } else {
            string op = "";
            op.push_back(expression.at(i++));
            eVector.push_back(op);
        }
    }

    this->expression = eVector;
}

Expression* Calculator::makeExpression(Expression* left, Expression* right, const string& oper) {
    if (oper == "+") {
        return new Plus(left, right);
    } else if (oper == "-") {
        return new Minus(left, right);
    } else if (oper == "*") {
        return new Mult(left, right);
    } else if (oper == "/") {
        return new Div(left, right);
    }
}

string Calculator::handleNegative(string expression) {
    // handle with negative numbers
    if (expression.at(0) == '-' || expression.at(0) == '+') {
        expression = "0" + expression;
    }
    for (int i = 1; i < expression.size(); i++) {
        if ((expression.at(i) == '-' || expression.at(i) == '+') && expression.at(i - 1) == '(') {
            expression = expression.substr(0, i) + "0" + expression.substr(i, expression.size() - i);
        }
    }
    return expression;
}

string Calculator::handleAdjacentOperators(string expression) {
    // handle with adjacent operators
    for (int i = 1; i < expression.size(); i++) {
        char c1 = expression.at(i - 1);
        char c2 = expression.at(i);
        int n = expression.size();
        if (c2 == '+' && (c1 == '*' || c1 == '/' || c1 == '+' || c1 == '-')) {
            expression = expression.substr(0, i) + expression.substr(i + 1, n - i - 1);
            i--;
        } else if (c2 == '-' && c1 == '+') {
            expression = expression.substr(0, i - 1) + expression.substr(i, n - i);
            i--;
        } else if (c2 == '-' && c1 == '-') {
            expression = expression.substr(0, i - 1) + "+" + expression.substr(i + 1, n - i - 1);
            i--;
        } else if (c2 == '-' && (c1 == '*' || c1 == '/')) {
            if (expression.at(i + 1) == '(') {
                int openParanthesis = 0;
                int j = i + 1;
                while (j < n) {
                    if (expression.at(j) == '(') { openParanthesis++; }
                    else if (expression.at(j) == ')') { openParanthesis--; }
                    if (openParanthesis == 0) { break; }
                    j++;
                }
                expression = expression.substr(0, i) + "(0" + expression.substr(i, j - i)
                             + ")" + expression.substr(j, n - j);
            } else {
                int j = i + 1;
                while (j < n && (expression.at(j) == '+' || expression.at(j) == '-')) { j++; }
                while (j < n && ((expression.at(j) >= '0' && expression.at(j) <= '9')
                                 || expression.at(j) == '.')) { j++; }
                expression = expression.substr(0, i) + "(0" + expression.substr(i, j - i)
                             + ")" + expression.substr(j, n - j);
            }
        }
    }
    return expression;
}