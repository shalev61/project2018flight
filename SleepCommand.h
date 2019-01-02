#ifndef ADPREX3_SLEEPCOMMAND_H
#define ADPREX3_SLEEPCOMMAND_H

#include "Command.h"
#include "Calculator.h"
#include <unistd.h>
#include <iostream>

class SleepCommand : public Command {
public:
    SleepCommand(vector<string>::iterator arrayEnd, SymbolTable* symbolTbl) : Command(arrayEnd, symbolTbl) { }
    virtual void execute(vector<string>::iterator &it) {
        it++; // Go past "sleep"
        if (it != this->arrayEnd) {
            string expression = this->nextExpression(it);
            it++; // Go to next command line
            Calculator* calculator = new Calculator(expression);
            usleep((unsigned int) (calculator->calculate() * 1000));
        }
    }
    ~SleepCommand() {
        delete this->symbolTbl;
    }
};

#endif