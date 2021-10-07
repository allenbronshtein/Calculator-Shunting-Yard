#ifndef MYPROJECT_EXPRESSION_H
#define MYPROJECT_EXPRESSION_H
using namespace std;

/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;

    virtual ~Expression() {};
};

#endif //MYPROJECT_EXPRESSION_H
