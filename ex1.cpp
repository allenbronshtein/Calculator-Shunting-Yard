#include "ex1.h"
#include "interpreter.h"
Variable::Variable(string name, double value) {
    this->name = name;
    this->value = value;
}

Value::Value(double value) {
    this->value = value;
}

UPlus::UPlus(Expression *expression) {
    this->expression = expression;
}

UMinus::UMinus(Expression *expression) {
    this->expression = expression;
}

Plus::Plus(Expression *expressionLeft, Expression *expressionRight) {
    this->expressionLeft = expressionLeft;
    this->expressionRight = expressionRight;
}

Minus::Minus(Expression *expressionLeft, Expression *expressionRight) {
    this->expressionLeft = expressionLeft;
    this->expressionRight = expressionRight;
}

Mul::Mul(Expression *expressionLeft, Expression *expressionRight) {
    this->expressionLeft = expressionLeft;
    this->expressionRight = expressionRight;
}

Div::Div(Expression *expressionLeft, Expression *expressionRight) {
    this->expressionLeft = expressionLeft;
    this->expressionRight = expressionRight;
}

//postfix
Variable &Variable::operator++() {
    this->value++;
    return *this;
}

//prefix
Variable &Variable::operator++(int) {
    this->value++;
    return *this;
}

Variable &Variable::operator--() {
    this->value--;
    return *this;
}

Variable &Variable::operator--(int) {
    this->value--;
    return *this;
}

Variable &Variable::operator+=(double num) {
    this->value += num;
    return *this;
}

Variable &Variable::operator-=(double num) {
    this->value -= num;
    return *this;
}

double Variable::calculate() {
    return this->value;
}

double Value::calculate() {
    return this->value;
}

double UPlus::calculate() {
    return this->expression->calculate();
}

double UMinus::calculate() {
    return -this->expression->calculate();
}

double Plus::calculate() {
    return this->expressionLeft->calculate() + this->expressionRight->calculate();
}

double Minus::calculate() {
    return this->expressionLeft->calculate() - this->expressionRight->calculate();
}

double Mul::calculate() {
    return this->expressionLeft->calculate() * this->expressionRight->calculate();
}

double Div::calculate() {
    double rightNum = this->expressionRight->calculate();
    if (rightNum == 0) {
        throw "Math error";
    }
    return this->expressionLeft->calculate() / rightNum;
}

string Variable::getName() {
    return name;
}

double Variable::getValue() {
    return value;
}

void Variable::setValue(double num) {
    value = num;
}
