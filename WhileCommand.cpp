#include "WhileCommand.h"
#include <iostream>

void WhileCommand::execute(vector<string>::iterator &it) {
    it++; // Go past "while"
    vector<string>::iterator saveIt = it;
    while (this->isConditionTrue(saveIt)) {
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

        it = saveIt;
    }

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