#ifndef WHILECOMMAND_H
#define WHILECOMMAND_H

#include "ConditionParser.h"

class WhileCommand : public ConditionParser {
public:
    WhileCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl, map<string, Command*>* commands)
            : ConditionParser(arrayEnd, symbolTbl, commands) { }
    virtual void execute(vector<string>::iterator &it);
    ~WhileCommand() {
        delete this->symbolTbl;
        delete this->commands;
    }
};


#endif