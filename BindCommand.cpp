#include "BindCommand.h"
#include "LocalBindedVar.h"
#include "RemoteBindedVar.h"

void BindCommand::execute(vector<string>::iterator &it) {
    it++; // Go past bind
    if (it != this->arrayEnd && (*it).at(0) == '"') {
        Variable* var = new RemoteBindedVar(this->data, (*it).substr(1, (*it).size() - 2));
        it-=3; // Go back to variable name
        this->symbolTbl->addVar(*it, var);
        it+=4; // Go past path
    } else if (it != this->arrayEnd) {
        Variable* var = new LocalBindedVar(this->symbolTbl->getVar(*it));
        it -= 3; // Go back to var name
        this->symbolTbl->addVar(*it, var);
        it += 4; // Go past binded var
    }
}