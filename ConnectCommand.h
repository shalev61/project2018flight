#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H

#include "DataServer.h"
#include "Command.h"

class ConnectCommand : public Command {
    UserData* data;
public:
    ConnectCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl, UserData* data) :
            Command(arrayEnd, symbolTbl) { this->data = data; }
    virtual void execute(vector<string>::iterator &it);
    ~ConnectCommand() {
        delete this->symbolTbl;
        delete this->data;
    }
};


#endif