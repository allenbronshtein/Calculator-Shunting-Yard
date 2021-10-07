#include "ex1.h"
#ifndef MYPROJECT_INTERPRETER_H
#define MYPROJECT_INTERPRETER_H

class Interpreter {
private :
    vector<Variable*>variables;
public :
    Expression *interpret(string s);

    void setVariables(string s);
};

class Queue {
private :
    int enqueLocator = 0;
    int dequeLocator = 0;
    string array[100];
public:

    void enque(string s);

    void deque();

    string front();

    bool isEmpty();

};

class Stack {
private :
    int locator = 0;
    string array[100];
public:
    void push(string c);

    void pop();

    string top();

    bool isEmpty();

};

Queue *shuntingYard(string s);

string fixNeg(string s);
void checkName(string s);
Queue *assign(Queue *, vector<Variable*>);

string fixBracets(string s);
string addBracets(string s);
bool isOperator(char c);
#endif //MYPROJECT_INTERPRETER_H
