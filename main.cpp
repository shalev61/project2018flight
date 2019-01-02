#include <iostream>
#include<fstream>
#include <cstring>

#include <vector>
#include <map>

#include "Calculator.h"
#include "ExpressionTypes.h"
#include "DefineVarCommand.h"
#include "AssignmentCommand.h"
#include "PrintCommand.h"
#include "IfCommand.h"
#include "WhileCommand.h"
#include "SleepCommand.h"
#include "BindCommand.h"
#include "DataServer.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"

#include "SymbolTable.h"

using namespace std;

void TokenLexer(vector<string> &lstAct) {
    vector<string>::iterator it;
    vector<string> sList;
    bool inQuotationMark = false;
    string inQuote = "";
    for (it = lstAct.begin(); it != lstAct.end(); ) {
        string token = *it;
        if (token == "") {
            sList.push_back(token);
            it++;
            continue;
        }

        char c = token.at(0);
        if (!inQuotationMark && c == '"') {
            inQuotationMark = true;
        }

        if (inQuotationMark) {
            if (inQuote == "") {
                inQuote = token;
            } else {
                inQuote += " " + token;
            }
            it++;
        } else {
            int n = token.size();
            if (n == 0 || n == 1) {
                sList.push_back(token);
                it++;
                continue;
            }
            // n >= 2
            if (c == '{' || c == '}' || ((c == '=' || c == '<' || c == '>') && token.at(1) != '=')) {
                sList.push_back(token.substr(0, 1));
                *it = token.substr(1, n - 1);
                continue;
            }
            if ((c == '=' || c == '!' || c == '<' || c == '>') && token.at(1) == '=') {
                if (n == 2) {
                    sList.push_back(token);
                    it++;
                    continue;
                } else {
                    sList.push_back(token.substr(0, 2));
                    *it = token.substr(2, n - 2);
                    continue;
                }
            }

            if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_') {
                int i = 0;
                while (i < n) {
                    char ci = token.at(i);
                    if (!(('a' <= ci && ci <= 'z') || ('A' <= ci && ci <= 'Z') || ci == '_'
                            || ('0' <= ci && ci <= '9'))) { break; }
                    i++;
                }
                if (i == n) {
                    sList.push_back(token);
                    it++;
                    continue;
                } else {
                    sList.push_back(token.substr(0, i));
                    *it = token.substr(i, n - i);
                    continue;
                }
            }

            if (('0' <= c && c <= '9') || c == '(' || c == ')' || c == '+' || c == '-' || c == '*' || c == '/') {
                int i = 0;
                while (i < n) {
                    char ci = token.at(i);
                    if (!(('0' <= ci && ci <= '9') || ci == '(' || ci == ')'
                            || ci == '+' || ci == '-' || ci == '*' || ci == '/' || ci == '.')) { break; }
                    i++;
                }
                if (i == n) {
                    sList.push_back(token);
                    it++;
                    continue;
                } else {
                    sList.push_back(token.substr(0, i));
                    *it = token.substr(i, n - i);
                    continue;
                }
            }
        }

        if (inQuotationMark && token.at(token.size() - 1) == '"') {
            inQuotationMark = false;
            sList.push_back(inQuote);
            inQuote = "";
            continue;
        }
    }
    lstAct = sList;
}

/**
* the func get list of the strings that already read and the line to lexer
* we divided the line by the spaces enter every part of it into the list
*
**/
void LexerLine(vector<string> &lstAct, string lineF) {
    //the current element of the line
    char * pch;

    int n = lineF.length();

    // declaring character array
    char char_array[n+1];

    // copying the contents of the
    // string to char array
    strcpy(char_array, lineF.c_str());

    //read from line
    pch = strtok (char_array," ");

    //till the end of the line
    while (pch != NULL)
    {
        //convers char* to string
        const char* charString = pch;
        string stringVar(charString);

        //push the elemnt into the list
        lstAct.push_back (stringVar);
        pch = strtok (NULL, " ");
    }

    // an empty string will mean the end of a line from now on.
    lstAct.push_back("");

    return;
}
/**
* the func get list of the strings that already read and the file to lexer
* we are reading all the lines and separate by the spaces and read it into our list
*
**/
void LexerFile(vector<string> &lstAct, string filename) {
    //open the file
    ifstream myReadFile;
    myReadFile.open(filename);

    string output;

    //if the file is actually open do the lexer func
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {

            //read line from file
            getline(myReadFile, output);

            //separate the elements in the line
            LexerLine(lstAct, output);

        }
    }
    myReadFile.close();

    TokenLexer(lstAct);
}

int main(int argc, char* argv[]) {
    vector<string> arr;
    /*if (argc != 2) {
        return 1;
    }
    LexerFile(arr, argv[1]);*/

    LexerFile(arr, "fl.txt");

    cout << "Commands Array:" << endl;
    for (vector<string>::iterator it=arr.begin(); it != arr.end(); ++it) {
        if (*it != "") {
            cout << " " << (*it);
        } else {
            cout << " | ";
        }
    }
    cout << endl;

    SymbolTable* symbolTbl = new SymbolTable();

    map<string, Command*> commands;

    UserData* data = new UserData();

    Command* dvc = new DefineVarCommand(arr.end(), symbolTbl);
    commands.insert(pair<string, Command*>("var", dvc));
    Command* ac = new AssignmentCommand(arr.end(), symbolTbl);
    commands.insert(pair<string, Command*>("=", ac));
    Command* pc = new PrintCommand(arr.end(), symbolTbl);
    commands.insert(pair<string, Command*>("print", pc));
    Command* ic = new IfCommand(arr.end(), symbolTbl, &commands);
    commands.insert(pair<string, Command*>("if", ic));
    Command* wc = new WhileCommand(arr.end(), symbolTbl, &commands);
    commands.insert(pair<string, Command*>("while", wc));
    Command* sc = new SleepCommand(arr.end(), symbolTbl);
    commands.insert(pair<string, Command*>("sleep", sc));
    Command* bc = new BindCommand(arr.end(), symbolTbl, data);
    commands.insert(pair<string, Command*>("bind", bc));
    Command* osc = new OpenServerCommand(arr.end(), symbolTbl, data);
    commands.insert(pair<string, Command*>("openDataServer", osc));
    Command* cc = new ConnectCommand(arr.end(), symbolTbl, data);
    commands.insert(pair<string, Command*>("connect", cc));

    vector<string>::iterator it = arr.begin();

    while (it < arr.end()) {
        // if map contains this command
        if (commands.find(*it) != commands.end()) {
            commands[*it]->execute(it);
        } else {
            it++;
        }
    }

    symbolTbl->print();

    return 0;
}