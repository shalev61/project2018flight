#ifndef EXPRESSIONTYPES_H
#define EXPRESSIONTYPES_H

#include "Expression.h"

class BinaryExpression : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryExpression(Expression* left, Expression* right) {
        this->left = left;
        this->right = right;
    }
    virtual double calculate() = 0;
};

class Number : public Expression {
    double value;
public:
    Number(double value) { this->value = value; }
    virtual double calculate() { return this->value; }
};

class Plus : public BinaryExpression {
public:
    Plus(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual double calculate() { return this->left->calculate() + this->right->calculate(); }
};

class Minus : public BinaryExpression {
public:
    Minus(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual double calculate() { return this->left->calculate() - this->right->calculate(); }
};

class Mult : public BinaryExpression {
public:
    Mult(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual double calculate() { return this->left->calculate() * this->right->calculate(); }
};

class Div : public BinaryExpression {
public:
    Div(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual double calculate() { return this->left->calculate() / this->right->calculate(); }
};


#endif