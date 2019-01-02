#ifndef OPENSERVERCOMMAND_H
#define OPENSERVERCOMMAND_H

#include "Command.h"
#include "DataServer.h"

class OpenServerCommand : public Command {
    UserData* data;
public:
    OpenServerCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl, UserData* data) :
            Command(arrayEnd, symbolTbl) { this->data = data; }
    virtual void execute(vector<string>::iterator &it);
    ~OpenServerCommand() {
        delete this->symbolTbl;
        delete this->data;
    }
};

#endif