#ifndef IFCOMMAND_H
#define IFCOMMAND_H

#include "ConditionParser.h"

class IfCommand : public ConditionParser {
public:
    IfCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl, map<string, Command*>* commands)
        : ConditionParser(arrayEnd, symbolTbl, commands) { }
    virtual void execute(vector<string>::iterator &it);
    ~IfCommand() {
        delete this->symbolTbl;
        delete this->commands;
    }
};


#endif