#include "PrintCommand.h"

void PrintCommand::execute(vector<string>::iterator &it) {
    it++; // Go past "print"
    if (it != this->arrayEnd && *it != "") {
        if ((*it).at(0) == '"') {
            string toPrint = *it;
            it++;
            while (it != this->arrayEnd && *it != "") {
                toPrint += " " + *it;
                it++;
            }
            cout << toPrint.substr(1, toPrint.size() - 2) << endl;
        } else {
            string expression = this->nextExpression(it);
            it++; // Go to next command line
            Calculator* calculator = new Calculator(expression);
            cout << calculator->calculate() << endl;
        }
    }
}