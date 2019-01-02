#include "IfCommand.h"

void IfCommand::execute(vector<string>::iterator &it) {
    it++; // Go past "if"
    bool isTrue = this->isConditionTrue(it);
    if (isTrue) {
        while (it != this->arrayEnd && *it != "{") {
            it++;
        }
        it++; // Go past "{"

        while (it < this->arrayEnd && *it != "}") {
            // if map contains this command
            if (this->commands->find(*it) != this->commands->end()) {
                (*(this->commands))[*it]->execute(it);
            } else if (this->symbolTbl->contains(*it)) {
                it++;
            } else {
                it++;
            }
        }
        it++; // Go past "}"
    } else {
        while (it != this->arrayEnd && *it != "{") {
            it++;
        }
        it++;
        int openBrackets = 1;
        while (it < this->arrayEnd && openBrackets > 0) {
            if (*it == "{") {
                openBrackets++;
            } else if (*it == "}") {
                openBrackets--;
            }
            it++;
        }
        it++; // Go past "}"
    }
}