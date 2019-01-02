#include "Command.h"
#include <algorithm>

string Command::nextExpression(vector<string>::iterator &it) {
    if (it == this->arrayEnd || *it == "") { return ""; }

    string expression = "";

    int openParanthesis = 0;
    while (it != arrayEnd && *it != "") {
        if (this->symbolTbl->contains(*it)) {
            expression += to_string(this->symbolTbl->getValue(*it));
        } else {
            expression += *it;

        }
        openParanthesis += count((*it).begin(), (*it).end(), '(');
        openParanthesis -= count((*it).begin(), (*it).end(), ')');
        if (it + 1 == arrayEnd || *(it + 1) == "") { break; }
        if (!isOperator((*it).at((*it).size() - 1)) && !isOperator((*(it + 1)).at(0)) && openParanthesis == 0) { break; }
        it++;
    }
    it++; // Go to next command line or argument
    return expression;
}