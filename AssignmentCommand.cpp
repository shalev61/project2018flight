#include "AssignmentCommand.h"

void AssignmentCommand::execute(vector<string>::iterator &it) {
    it--; // Go back to variable name
    string varName = *it;
    it += 2; // Go past "="
    if (it != this->arrayEnd && *it != "bind") {
        string expression = this->nextExpression(it);
        Calculator *calculator = new Calculator(expression);
        this->symbolTbl->setValue(varName, calculator->calculate());
    }
}