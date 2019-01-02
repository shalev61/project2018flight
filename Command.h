#ifndef COMMAND_H
#define COMMAND_H

#include <map>
#include <list>
#include <string>
#include <vector>
#include "SymbolTable.h"

using namespace std;

class Command {
protected:
    vector<string>::iterator arrayEnd;
    SymbolTable* symbolTbl;

    string nextExpression(vector<string>::iterator &it);
    bool isOperator(char c) { return (c == '+' || c == '-' || c == '*' || c == '/'); }
public:
    Command(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl) {
        this->arrayEnd = arrayEnd;
        this->symbolTbl = symbolTbl;
    }
    virtual void execute(vector<string>::iterator &it) = 0;
};

#endif