#include "interpreter.h"

Expression *Interpreter::interpret(string s) {
    if (s.find(" ") != string::npos) {
        cout << "Expression cannot have spaces" << endl;
        throw "error";
    }
    string expression = s;
    while (expression != fixNeg(expression)) {
        expression = fixNeg(expression);
    }
    Queue *queue;
    queue = shuntingYard(expression);
    Queue *newQueue;
    newQueue = assign(queue, variables);
    Stack *stack = new Stack();
    while (!newQueue->isEmpty()) {
        string token = newQueue->front();
        newQueue->deque();
        if (token != "+" && token != "-" && token != "*" && token != "/") {
            stack->push(token);
            continue;
        }
        if (token == "+") {
            double a, b;
            if (stack->isEmpty()) {
                throw "error";
            }
            a = stod(stack->top());
            stack->pop();
            if (stack->isEmpty()) {
                throw "error";
            }
            b = stod(stack->top());
            stack->pop();
            Plus *plus = new Plus(new Value(a), new Value(b));
            double c = plus->calculate();
            stack->push(to_string(c));
        } else if (token == "-") {
            double a, b;
            if (stack->isEmpty()) {
                throw "error";
            }
            a = stod(stack->top());
            stack->pop();
            if (stack->isEmpty()) {
                throw "error";
            }
            b = stod(stack->top());
            stack->pop();
            Minus *minus;
            minus = new Minus(new Value(b), new Value(a));
            double c = minus->calculate();
            stack->push(to_string(c));
        } else if (token == "*") {
            double a, b;
            if (stack->isEmpty()) {
                throw "error";
            }
            a = stod(stack->top());
            stack->pop();
            if (stack->isEmpty()) {
                throw "error";
            }
            b = stod(stack->top());
            stack->pop();
            Mul *mul = new Mul(new Value(a), new Value(b));
            double c = mul->calculate();
            stack->push(to_string(c));
        } else if (token == "/") {
            double a, b;
            if (stack->isEmpty()) {
                throw "error";
            }
            a = stod(stack->top());
            stack->pop();
            if (stack->isEmpty()) {
                throw "error";
            }
            b = stod(stack->top());
            stack->pop();
            Div *div = new Div(new Value(b), new Value(a));
            double c = div->calculate();
            stack->push(to_string(c));
        } else {
            throw "error";
            break;
        }
    }
    Expression *e = new Value(stod(stack->top()));
    if (e->calculate() != (double) e->calculate()) {
        throw "error";
    }
    return e;
}

Queue *shuntingYard(string s) {
    Queue *outputQueue = new Queue();
    Stack *stack = new Stack();
    string tempName = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            stack->push(s.substr(i, 1));
            continue;
        }
        if (s[i] == ')') {
            while (stack->top() != "(") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
            }
            if (stack->top() == "(") {
                stack->pop();
            }
            continue;
        }
        // if s[i] is number
        if (isdigit(s[i]) || (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/')) {
            if (isdigit(s[i])) {
                double num = 0;
                double fraction = 0;
                double deciFraction = 1;
                while (isdigit(s[i])) {
                    num *= 10;
                    num += stoi(s.substr(i, 1));
                    if (isdigit(s[i + 1])) {
                        ++i;
                        continue;
                    }
                    break;
                }
                if (s[i + 1] == '.') {
                    i += 2;
                    while (isdigit(s[i])) {
                        deciFraction /= 10;
                        fraction += stoi(s.substr(i, 1)) * deciFraction;
                        if (!isdigit(s[i + 1])) {
                            break;
                        }
                    }
                }
                outputQueue->enque(to_string(num + fraction));
                num = 0;
                deciFraction = 1;
                fraction = 0;
                continue;
            }
            do {
                tempName += s[i];
                i++;
            } while (s[i] != '+' && s[i] != '-' && s[i] != '*' && s[i] != '/' && i < s.size() && s[i] != ')' &&
                     s[i] != '(');
            i--;
            outputQueue->enque(tempName);
            tempName = "";
            continue;
        }
            //if s[i] is operator
        else {
            if (s[i] == '-' && stack->top() == "-") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '-' && stack->top() == "+") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '+' && stack->top() == "-") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '/' && stack->top() == "/") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '/' && stack->top() == "*") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '*' && stack->top() == "/") {
                string temp = "" + stack->top();
                outputQueue->enque(temp);
                stack->pop();
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '*' && (stack->top() == "+" || stack->top() == "-")) {
                stack->push(s.substr(i, 1));
                continue;
            }
            if (s[i] == '/' && (stack->top() == "+" || stack->top() == "-")) {
                stack->push(s.substr(i, 1));
                continue;
            }
            //stronger
            if (s[i] == '+' || s[i] == '-') {
                while ((stack->top() == "/" || stack->top() == "*") && stack->top() != "(") {
                    string temp = "" + stack->top();
                    outputQueue->enque(temp);
                    stack->pop();
                }
                if (s[i] == '-' && stack->top() == "-") {
                    string temp = "" + stack->top();
                    outputQueue->enque(temp);
                    stack->pop();
                    stack->push(s.substr(i, 1));
                    continue;
                }
                if (s[i] == '-' && stack->top() == "+") {
                    string temp = "" + stack->top();
                    outputQueue->enque(temp);
                    stack->pop();
                    stack->push(s.substr(i, 1));
                    continue;
                }
                if (s[i] == '+' && stack->top() == "-") {
                    string temp = "" + stack->top();
                    outputQueue->enque(temp);
                    stack->pop();
                    stack->push(s.substr(i, 1));
                    continue;
                }
            }
            stack->push(s.substr(i, 1));
            continue;
        }
    }
    while (!stack->isEmpty()) {
        string temp = "" + stack->top();
        outputQueue->enque(temp);
        stack->pop();
    }
    return outputQueue;
}

void Queue::enque(string c) {
    array[enqueLocator] = c;
    ++enqueLocator;
}

void Queue::deque() {
    ++dequeLocator;
}

string Queue::front() {
    return array[dequeLocator];
}

bool Queue::isEmpty() {
    if (enqueLocator == dequeLocator) {
        return true;
    }
    return false;
}

bool Stack::isEmpty() {
    if (locator == 0) {
        return true;
    }
    return false;
}

void Stack::push(string c) {
    array[locator] = c;
    ++locator;
}

void Stack::pop() {
    --locator;
    if (locator < 0) {
        locator = 0;
    }
}

string Stack::top() {
    return array[locator - 1];
}

string fixNeg(string s) {
    int j;
    string newS = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '0' && s[i + 1] == '-' && s[i + 2] == '0') {

        }
        if (s[i] == '(' && s[i + 1] == '-') {
            if (s[i + 2] != '(') {
                newS = newS + s[i] + "(" + "0" + "-";
                int skipper = i + 2;
                if (isdigit(s[skipper])) {
                    while (isdigit(s[skipper]) || s[skipper] == '.') {
                        newS += s[skipper];
                        skipper++;
                    }
                    newS += ')';
                    i = skipper;
                    continue;
                }
                while (s[skipper] != '+' && s[skipper] != '-' && s[skipper] != '*' && s[skipper] != '/') {
                    newS += s[skipper];
                    skipper++;
                }
                newS += ')';
                i = skipper - 1;
                continue;
            } else if (s[i + 2] == '(') {
                newS = newS + '(' + '0' + '-';
                i++;
                continue;
            }
        }
        if ((s[i] == '+' && s[i + 1] == '-') || (s[i] == '-' && s[i + 1] == '+')) {
            newS = newS + "-";
            ++i;
            continue;
        }
        if (((s[i] == '-' && s[i + 1] == '-')) || ((s[i] == '+' && s[i + 1] == '+'))) {
            newS = newS + "+";
            ++i;
            continue;
        }
        if ((s[i] == '*' || s[i] == '/') && s[i + 1] == '-') {
            newS = newS + s[i] + "(0-" + s[i + 2] + ')';
            i += 2;
            continue;
        }
        if (s[i] == '+') {
            if (s[i + 1] == ')') {
                continue;
            }
            if (i == 0) {
                continue;
            }
            if (s[i - 1] == '*' || s[i - 1] == '/') {
                continue;
            }
        }
        if (i == 0 && s[i] == '-') {
            newS = newS + "0-" + s[i + 1];
            i++;
            continue;
        }
        newS = newS + s[i];
    }
    //entered a loop
    if (newS.size() > 100) {
        throw "error";
    }
    newS = fixBracets(newS);
    return newS;
}

string fixBracets(string s) {
    int countLeft = 0, countRight = 0, bracetsToAdd;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            countLeft++;
        }
        if (s[i] == ')') {
            countRight++;
        }
    }
    if (countLeft > countRight) {
        bracetsToAdd = countLeft - countRight;
    } else {
        bracetsToAdd = countRight - countLeft;
    }
    for (int i = 0; i < bracetsToAdd; i++) {
        s += ')';
    }
    return s;
}

void Interpreter::setVariables(string s) {
    string newS = "";
    int j = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] != ';' && s[i] != ' ') {
            newS += s[i];
        }
    }
    int i = 0;
    while (newS != "") {
        string name;
        double value = 0;
        int i = 0;
        int skipper = 0;
        double deciFraction = 1;
        double fraction = 0;
        bool hasFraction = false;
        int asciiValue = toascii(s[i]);
        bool flag = false;
        bool negative = false;
        //variable start
        if (asciiValue < 48 || asciiValue > 57) {
            skipper = newS.find('=');
            name = newS.substr(i, skipper);
            checkName(name);
        }
        i = skipper + 1;
        if (newS[i] == '-') {
            i++;
            negative = true;
        }
        while (isdigit(newS[i])) {
            value = value * 10 + stoi(newS.substr(i, 1));
            i++;
            flag = true;
        }
        if (!isdigit(newS[i]) && !flag) {
            throw "error";
        }
        if (newS[i] == '.') {
            i++;
            hasFraction = true;
            while (isdigit(newS[i])) {
                deciFraction /= 10;
                fraction += stoi(newS.substr(i, 1)) * deciFraction;
                if (isdigit(s[i + 1])) {
                    ++i;
                    continue;
                }
                break;
            }
        }
        value = value + fraction;
        if (negative) {
            value = -value;
        }
        while (isdigit(newS[i])) {
            i++;
        }
        newS = newS.substr(i, newS.length());
        bool f = false;
        for (Variable *v : variables) {
            if (v->getName() == name) {
                v->setValue(value);
                f = true;
                break;
            }
        }
        if (!f) {
            Variable *e = new Variable(name, value);
            variables.push_back(e);
        }
    }
}

Queue *assign(Queue *queue, vector<Variable *> variables) {
    Queue *newQueue = new Queue();
    while (!queue->isEmpty()) {
        bool nameFound = false;
        string s = queue->front();
        if (isdigit(s[0]) || s == "+" || s == "-" || s == "*" || s == "/") {
            newQueue->enque(s);
            queue->deque();
            continue;
        } else {
            for (int i = 0; i < variables.size(); i++) {
                if (s == variables[i]->getName()) {
                    s = to_string(variables[i]->getValue());
                    nameFound = true;
                }
            }
            if (!nameFound) {
                throw "error";
            }
            newQueue->enque(s);
            queue->deque();
        }
    }
    return newQueue;
}


bool isFlatOperator(char c) {
    return c == '+' || c == '-';
}

void checkName(string name) {
    int temp;
    if (isdigit(name[0])) {
        throw "Invalid Variable name";
    }
    for (int i = 1; i < name.size(); i++) {
        temp = toascii(name[i]);
        if (isdigit(name[i])) {
            continue;
        }
        if (!(temp <= 90 && temp >= 65)&&!(temp <= 122 && temp >= 97) && (temp!=95)){
            throw "Invalid Variable name";
        }
    }
}
