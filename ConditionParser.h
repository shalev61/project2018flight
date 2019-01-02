#ifndef CONDITIONPARSER_H
#define CONDITIONPARSER_H

#include "Command.h"

using namespace std;

class ConditionParser : public Command {
protected:
    map<string, Command*>* commands;

    bool checkCondition(double leftValue, double rightValue, string conditionSign);
public:
    ConditionParser(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl, map<string, Command*>* commands)
        : Command(arrayEnd, symbolTbl) {
        this->commands = commands;
    }
    bool isConditionTrue(vector<string>::iterator it);
    virtual void execute(vector<string>::iterator &it) = 0;
};


#endif