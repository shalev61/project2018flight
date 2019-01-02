#ifndef LOCALBINDEDVAR_H
#define LOCALBINDEDVAR_H

#include "Variable.h"

class LocalBindedVar : public Variable {
    Variable* bindedVar;
public:
    LocalBindedVar(Variable* bindedVar) {
        this->bindedVar = bindedVar;
    }
    virtual double getValue() {
        return this->bindedVar->getValue();
    }
    virtual void setValue(double value) {
        this->bindedVar->setValue(value);
    }
    ~LocalBindedVar() {
        delete bindedVar;
    }
};

#endif