#ifndef PRINTCOMMAND_H
#define PRINTCOMMAND_H

#include "Command.h"
#include "Calculator.h"
#include <iostream>

class PrintCommand : public Command {
public:
    PrintCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl) : Command(arrayEnd, symbolTbl) { }
    virtual void execute(vector<string>::iterator &it);
    ~PrintCommand() {
        delete this->symbolTbl;
    }
};

#endif