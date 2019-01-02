#ifndef ASSIGNMENTCOMMAND_H
#define ASSIGNMENTCOMMAND_H

#include "Command.h"
#include "Calculator.h"

class AssignmentCommand : public Command {
public:
    AssignmentCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl) : Command(arrayEnd, symbolTbl) { }
    virtual void execute(vector<string>::iterator &it);
    ~AssignmentCommand() {
        delete this->symbolTbl;
    }
};

#endif