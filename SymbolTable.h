#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include "Variable.h"
#include <string>
#include <map>
#include <iostream>
using namespace std;

class SymbolTable {
    map<string, Variable*> symbolTbl;
public:
    double getValue(string varName) {
        return this->symbolTbl[varName]->getValue();
    }
    void setValue(string varName, double value) {
        this->symbolTbl[varName]->setValue(value);
    }
    bool contains(string varName) {
        map<string, Variable*>::iterator it = this->symbolTbl.begin();
        return (this->symbolTbl.find(varName) != this->symbolTbl.end());
    }
    void addVar(string varName, Variable* var) {
        this->symbolTbl.insert(pair<string, Variable*>(varName, var));
    }
    Variable* getVar(string varName) {
        return this->symbolTbl[varName];
    }

    ~SymbolTable() {
        for (map<string, Variable*>::iterator it = symbolTbl.begin(); it != symbolTbl.end(); it++) {
            delete (*it).second;
        }
        this->symbolTbl.clear();
    }

    void print() {
        cout << "Symbol Table:" << endl;
        for (map<string, Variable*>::iterator mit=symbolTbl.begin(); mit != symbolTbl.end(); ++mit) {
            cout << " (" << (*mit).first << "," << (*mit).second->getValue() << ")";
        }
        cout << endl;
    }
};


#endif