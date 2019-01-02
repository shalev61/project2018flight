#ifndef REMOTEBINDEDVAR_H
#define REMOTEBINDEDVAR_H

#include "Variable.h"
#include "DataServer.h"
#include <string>
using namespace std;

class RemoteBindedVar : public Variable {
    UserData* data;
    string path;
public:
    RemoteBindedVar(UserData* data, string path) {
        this->data = data;
        this->path = path;
    }
    virtual double getValue() {
        return this->data->getValue(this->path);
    }
    virtual void setValue(double value) {
        this->data->setValue(this->path, value);
    }
    ~RemoteBindedVar() {
        delete data;
    }
};


#endif