#include <string>
#include <cstring>
#include <iostream>
#include <vector>
#include "Expression.h"
#ifndef UNTITLED_EX1_H
#define UNTITLED_EX1_H

using namespace std;

class Variable : public Expression {
private:
    string name;
    double value;
public :
    Variable(string name, double value);

    Variable &operator++();

    Variable &operator--();

    Variable &operator+=(double num);

    Variable &operator-=(double num);

    Variable &operator++(int num);

    Variable &operator--(int num);

    virtual double calculate();

    virtual ~Variable() {};

    string getName();
    double getValue();
    void setValue(double num);
};

class Value : public Expression {
private :
    double value;
public :
    Value(double num);

    virtual double calculate();

    virtual ~Value() {};
};

class UnaryOperator : public Expression {
protected:
    Expression *expression;

    virtual double calculate() {};
};

class BinaryOperator : public Expression {
protected:
    Expression *expressionLeft;
    Expression *expressionRight;

    virtual double calculate() {};
};

class UPlus : public UnaryOperator {
public:
    virtual double calculate();

    UPlus(Expression *expression);

    virtual ~UPlus() {};
};

class UMinus : public UnaryOperator {
public:
    double calculate();

    UMinus(Expression *expression);

    ~UMinus() {};
};

class Plus : public BinaryOperator {
public:
    virtual double calculate();

    Plus(Expression *expressionLeft, Expression *expressionRight);

    virtual ~Plus() {};
};

class Minus : public BinaryOperator {
public:
    virtual double calculate();

    Minus(Expression *expressionLeft, Expression *expressionRight);

    virtual ~Minus() {};
};

class Mul : public BinaryOperator {
public:
    virtual double calculate();

    Mul(Expression *expressionLeft, Expression *expressionRight);

    virtual ~Mul() {};
};

class Div : public BinaryOperator {
public:
    virtual double calculate();

    Div(Expression *expressionLeft, Expression *expressionRight);

    virtual ~Div() {};
};

#endif //PROJECT_EX1_H