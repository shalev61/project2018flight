#ifndef ADPREX3_VARIABLE_H
#define ADPREX3_VARIABLE_H

class Variable {
public:
    virtual double getValue() = 0;
    virtual void setValue(double value) = 0;
};

#endif