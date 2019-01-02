#ifndef BINDCOMMAND_H
#define BINDCOMMAND_H

#include "Command.h"
#include "DataServer.h"

class BindCommand : public Command {
    UserData* data;
public:
    BindCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl, UserData* data) : Command(arrayEnd, symbolTbl) {
        this->data = data;
    }
    virtual void execute(vector<string>::iterator &it);
    ~BindCommand() {
        delete this->symbolTbl;
        delete this->data;
    }
};


#endif
