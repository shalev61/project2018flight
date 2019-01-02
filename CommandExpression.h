#ifndef COMMANDEXPRESSION_H
#define COMMANDEXPRESSION_H

#include "Expression.h"
#include "Command.h"

class CommandExpression : public Expression {
    Command* c;
    vector<string>::iterator it;
public:
    CommandExpression(Command* c, vector<string>::iterator &it) {
        this->c = c;
        this->it = it;
    }
    virtual double calculate() {
        this->c->execute(it);
        return 0.0;
    }
    virtual ~CommandExpression() {
        delete this->c;
    }
};

#endif