#ifndef NORMALVAR_H
#define NORMALVAR_H

#include "Variable.h"

class NormalVar : public Variable {
    double value;
public:
    virtual double getValue() {
        return this->value;
    }
    virtual void setValue(double value) {
        this->value = value;
    }
    ~NormalVar() { }
};

#endif