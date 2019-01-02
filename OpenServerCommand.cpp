#include "OpenServerCommand.h"
#include "Calculator.h"

void OpenServerCommand::execute(vector<string>::iterator &it) {
    it++; // Go past "openDataServer"
    if (it != this->arrayEnd) {
        string portStr = this->nextExpression(it);
        string hzStr = this->nextExpression(it);
        it++; // Go to next command line

        Calculator* c1 = new Calculator(portStr);
        Calculator* c2 = new Calculator(hzStr);
        int port = (int) c1->calculate();
        int hz = (int) c2->calculate();
        this->data->openDataServer(port, hz);
    }
}