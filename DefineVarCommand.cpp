#include "DefineVarCommand.h"

void DefineVarCommand::execute(vector<string>::iterator &it) {
    it++; // Go past "var"
    it += 2; // Go to "bind"
    if (it != this->arrayEnd && *it == "bind") {
        return;
    }
    it -= 2; // Go back to var name
    if (it != this->arrayEnd) {
        Variable* var = new NormalVar();
        this->symbolTbl->addVar(*it, var); // Insert variable
        it++; // Go past variable name
        if (it != this->arrayEnd && *it == "") {
            it++; // Go to next command line
        }
    }
}