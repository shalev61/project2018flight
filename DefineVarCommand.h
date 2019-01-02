#ifndef DEFINEVARCOMMAND_H
#define DEFINEVARCOMMAND_H

#include "Command.h"
#include "LocalBindedVar.h"
#include "NormalVar.h"

class DefineVarCommand : public Command {
public:
    DefineVarCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl) : Command(arrayEnd, symbolTbl) { }
    virtual void execute(vector<string>::iterator &it);
    ~DefineVarCommand() {
        delete this->symbolTbl;
    }
};


#endif