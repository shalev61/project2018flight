#include "ConnectCommand.h"
#include "Calculator.h"

void ConnectCommand::execute(vector<string>::iterator &it) {
    it++; // Go past "connect"
    if (it != this->arrayEnd) {
        string ip = *it;
        it++; // Go past ip
        string portStr = this->nextExpression(it);
        it++; // Go to next command line

        Calculator* c = new Calculator(portStr);
        int port = (int) c->calculate();
        this->data->openDataClient(port, ip);
    }
}