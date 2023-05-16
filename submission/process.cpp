#include "process.h"
int getPriortyMath(char o) {
    if (o == '^')
        return 3;
    if (o == '*' || o == '/' || o == '%')
        return 2;
    if (o == '+' || o == '-')
        return 1;
    return 0;
}
int getPriorityLogic(string s) {
    if (s == "~")
        return 4;
    if (s == "|" || s == "&")
        return 3;
    if (s == "->")
        return 2;
    if (s == "<->")
        return 1;
    return 0;
}
bool greaterOrEqualThanMath(char a, char b) {
    if (getPriortyMath(a) >= getPriortyMath(b))
        return true;
    else return false;
}
bool greaterOrEqualThanLogic(string a, string b) {
    if (getPriorityLogic(a) >= getPriorityLogic(b))
        return true;
    else return false;
}
bool greaterThanMath(char a, char b) {
    if (getPriortyMath(a) > getPriortyMath(b))
        return true;
    else return false;
}
bool greaterThanLogic(string a, string b) {
    if (getPriorityLogic(a) > getPriorityLogic(b))
        return true;
    else
        return false;
}
bool isOperator(char s)
{
    if (s == '/' || s == '*' || s == '%' || s == '+' || s == '-' || s == '^' || s == '~' || s == '&' || s == '|' || s == '<')
        return true;
    else return false;
}
bool isOperand(char s)
{
    if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9'))
        return true;
    else return false;
}
string reverseStr(string s) {
    string k = "";
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '(') {
            s[i] = ')';
            goto here;
        }
        if (s[i] == ')') {
            s[i] = '(';
            goto here;
        }
        if (s[i] == '<') {
            s[i] = '>';
            goto here;
        }
        if (s[i] == '>') {
            s[i] = '<';
            goto here;
        }
        here:
        k += s[i];
    }
    return k;
}
int countN(int n) {
    int k = 0;
    while (n > 0) {
        n /= 10;
        k ++;
    }
    return k;
}
int reverseNum(int n) {
    int a[countN(n) + 1];
    const int countNum = countN(n);
    int i = 1;
    while (n > 0) {
        a[i] = n % 10;
        i ++;
        n /= 10;
    }
    int result = 0;
    for (int j = 1; j <= countNum; j ++)
        result += a[j]*pow(10, countNum - j);
    return result;
}
/*MATH*/
/*BEGIN INFIX2POSTFIX*/
string Infix2Postfix(string input) {
    stack<char> Stack;
    string s = "";
    for (unsigned int i = 0; i < input.length(); i++) {
        if (isOperand(input[i])) {
            unsigned int j = i;
            while (isOperand(input[j]) && j < input.length()) {
                s += input[j];
                j++;
            }
            s += ' ';
            i = j - 1;
        }
        if (input[i] == '(') {
            Stack.push(input[i]);
        }
        if (input[i] == ')') {
            while (!Stack.empty() && Stack.top() != '(') {
                s += Stack.top();
                s += ' ';
                Stack.pop();
            }
            Stack.pop();
        }
        if (isOperator(input[i])) {
            while (!Stack.empty() && Stack.top() != '(' && greaterOrEqualThanMath(Stack.top(), input[i])) {
                if (!Stack.empty()) {
                    s += Stack.top();
                    s += ' ';
                    Stack.pop();
                }
            }
            Stack.push(input[i]);
        }
    }
    while (!Stack.empty()) {
        s += Stack.top();
        s += ' ';
        Stack.pop();
    }
    return s;
}
/*END INFIX2POSTFIX*/
/*BEGIN INFIX2PREFIX*/
string Infix2Prefix(string input) {
    input = reverseStr(input);
    stack<char> Stack;
    string s = "";
    for (unsigned int i = 0; i < input.length(); i++) {
        if (isOperand(input[i])) {
            unsigned int j = i;
            while (isOperand(input[j]) && j < input.length()) {
                s += input[j];
                j++;
            }
            s += ' ';
            i = j - 1;
        }
        if (input[i] == '(') {
            Stack.push(input[i]);
        }
        if (input[i] == ')') {
            while (!Stack.empty() && Stack.top() != '(') {
                s += Stack.top();
                s += ' ';
                Stack.pop();
            }
            Stack.pop();
        }
        if (isOperator(input[i])) {
            while (!Stack.empty() && Stack.top() != '(' && greaterThanMath(Stack.top(), input[i])) {
                if (!Stack.empty()) {
                    s += Stack.top();
                    s += ' ';
                    Stack.pop();
                }
            }
            Stack.push(input[i]);
        }
    }
    while (!Stack.empty()) {
        s += Stack.top();
        s += ' ';
        Stack.pop();
    }
    s = reverseStr(s);
    s.erase(0, 1);
    return s;
}
/*END INFIX2PREFIX*/
/*BEGIN CALPREPOST*/
string PostfixPrefixCalculator(string input){
    stack<double> Stack;
        if (isOperator(input[0])) {
            for (unsigned int i = input.length() - 1; i >= 0; i--) {
                if (isOperand(input[i])) {
                    unsigned int j = i;
                    double temp = 0;
                    int c = 0;
                    while (input[j] != ' ' && j >= 0) {
                        temp *= 10;
                        temp += (input[j] - '0');
                        if (temp == 0)
                            c++;
                        j--;
                    }
                    i = j;
                    Stack.push(reverseNum(temp)*pow(10, c));
                    continue;
                }
                if (isOperator(input[i])) {
                    double a = Stack.top();
                    Stack.pop();
                    double b = Stack.top();
                    Stack.pop();
                    switch (input[i]) {
                        case '+':
                            Stack.push(a + b);
                            break;
                        case '-':
                            Stack.push(a - b);
                            break;
                        case '*':
                            Stack.push(a * b);
                            break;
                        case '/':
                            Stack.push(a / b);
                            break;
                        case '^':
                            Stack.push(pow(a, b));
                            break;
                        default:
                            break;
                    }
                }
                if (i == 0)
                    break;
            }
        }
        if (isOperand(input[0])) {
            for (unsigned int i = 0; i < input.length(); i++){
                if (isOperand(input[i])) {
                    unsigned int j = i;
                    double temp = 0;
                    while (input[j] != ' ' && j < input.length()) {
                        temp *= 10;
                        temp += (input[j] - '0');
                        j++;
                    }
                    i = j;
                    Stack.push(temp);
                    continue;
                }
                if (isOperator(input[i])) {
                    double b = Stack.top();
                    Stack.pop();
                    double a = Stack.top();
                    Stack.pop();
                    switch (input[i]) {
                        case '+':
                            Stack.push(a + b);
                            break;
                        case '-':
                            Stack.push(a - b);
                            break;
                        case '*':
                            Stack.push(a * b);
                            break;
                        case '/':
                            Stack.push(a / b);
                            break;
                        case '^':
                            Stack.push(pow(a, b));
                            break;
                    }
                }
            }
        }
    stringstream temp;
    temp << fixed << setprecision(4) << noshowpoint << Stack.top();
    string s = temp.str();
    s.erase(s.find_last_not_of('0') + 1, std::string::npos);
    if (s[s.length() - 1] == '.')
        s.erase(s.length() - 1, 1);
    return s;
}
/*END CALPREPOST*/
/*LOGIC*/
/*BEGIN LOGICINFIX2POSTFIX*/
string LogicInfix2Postfix(string infix){
    stack<string> Stack;
    string s = "";
    for (unsigned int i = 0; i < infix.length(); i++) {
        if (isOperand(infix[i])) {
            s += infix[i];
        }
        if (infix[i] == '(') {
            Stack.push("(");
        }
        if (infix[i] == ')') {
            while (!Stack.empty() && Stack.top() != "(") {
                s += Stack.top();
                Stack.pop();
            }
            Stack.pop();
        }
        if (isOperator(infix[i])) {
            string temp = "";
            if (infix[i] == '-') {
                temp += "->";
                i += 1;
            }
            else if (infix[i] == '<') {
                temp += "<->";
                i += 2;
            }
            else {
                temp += infix[i];
            }
            while (!Stack.empty() && Stack.top() != "(" && greaterOrEqualThanLogic(Stack.top(), temp)) {
                if (!Stack.empty()) {
                    s += Stack.top();
                    Stack.pop();
                }
            }
            Stack.push(temp);
        }
    }
    while (!Stack.empty()) {
        s += Stack.top();
        Stack.pop();
    }
    return s;
}
/*END LOGICINFIX2POSTFIX*/
/*BEGIN LOGICINFIX2PREFIX*/
string LogicInfix2Prefix(string infix){
    stack<string> Stack;
    string s = "";
    infix = reverseStr(infix);
    for (unsigned int i = 0; i < infix.length(); i++) {
        if (isOperand(infix[i])) {
            s += infix[i];
        }
        if (infix[i] == '(') {
            Stack.push("(");
        }
        if (infix[i] == ')') {
            while (!Stack.empty() && Stack.top() != "(") {
                s += Stack.top();
                Stack.pop();
            }
            Stack.pop();
        }
        if (isOperator(infix[i])) {
            string temp = "";
            if (infix[i] == '<') {
                if (infix[i + 2] == '>') {
                    temp += "<->";
                    i += 2;
                }
                else {
                    temp += "<-";
                    i += 1;
                }
            }
            else {
                temp += infix[i];
            }
            while (!Stack.empty() && Stack.top() != "(" && greaterThanLogic(Stack.top(), temp)) {
                if (!Stack.empty()) {
                    s += Stack.top();
                    Stack.pop();
                }
            }
            Stack.push(temp);
        }
    }
    while (!Stack.empty()) {
        s += Stack.top();
        Stack.pop();
    }
    return reverseStr(s);
}
/*END LOGICINFIX2PREFIX*/
/*BEGIN LOGICCALPERPOST*/
string LogicPostfixPrefixCalculator(string input,string varlue){
    stack<bool> Stack;
    char arrVar[1000];
    bool arrVal[1000];
    unsigned int numVar = 0;
    unsigned int numVal = 0;
    for (unsigned int i = 0; i < varlue.length(); i++) {
        if (isOperand(varlue[i])) {
            arrVar[numVar] = varlue[i];
            numVar++;
        }
        if (varlue[i] == '0') {
            arrVal[numVal] = false;
            numVal++;
        }
        if (varlue[i] == '1') {
            arrVal[numVal] = true;
            numVal++;
        }
    }
    switch (isOperand(input[0])) {
        case 0: {//prefix
            for (unsigned int i = input.length() - 1; i >= 0; i--) {
                if (isOperand(input[i])) {
                    unsigned int j = 0;
                    while (j < numVar && arrVar[j] != input[i]) {
                        j++;
                    }
                    Stack.push(arrVal[j]);
                }
                if (isOperator(input[i])) {
                    if (input[i] == '~') {
                        bool a = Stack.top();
                        Stack.pop();
                        Stack.push(!a);
                    }
                    else {
                        string temp = "";
                        if (input[i] == '>') {
                            if (i > 1 && input[i - 2] == '<') {
                                temp += "<->";
                                i-=2;
                            }
                            else {
                                temp += "->";
                                i--;
                            }
                        }
                        else {
                            temp += input[i];
                        }
                        bool a = Stack.top();
                        Stack.pop();
                        bool b = Stack.top();
                        Stack.pop();
                        if (temp == "&")
                            Stack.push(a && b);
                        if (temp == "|")
                            Stack.push(a || b);
                        if (temp == "->") {
                            if (a && !b)
                                Stack.push(false);
                            else
                                Stack.push(true);
                        }
                        if (temp == "<->") {
                            if ((a && b) || (!a && !b))
                                Stack.push(true);
                            else
                                Stack.push(false);
                        }
                    }
                }
                if (i == 0)
                    break;
            }
            break;
        }
        case 1: {//postfix
            for (unsigned int i = 0; i < input.length(); i++) {
                if (isOperand(input[i])) {
                    unsigned int j = 0;
                    while (j < numVar && arrVar[j] != input[i]) {
                        j++;
                    }
                    Stack.push(arrVal[j]);
                }
                if (isOperator(input[i])) {
                    if (input[i] == '~') {
                        bool a = Stack.top();
                        Stack.pop();
                        Stack.push(!a);
                    }
                    else {
                        string temp = "";
                        if (input[i] == '-') {
                            temp += "->";
                            i++;
                        }
                        else if (input[i] == '<') {
                            temp += "<->";
                            i += 2;
                        }
                        else {
                            temp += input[i];
                        }
                        bool b = Stack.top();
                        Stack.pop();
                        bool a = Stack.top();
                        Stack.pop();
                        if (temp == "&")
                            Stack.push(a && b);
                        if (temp == "|")
                            Stack.push(a || b);
                        if (temp == "->") {
                            if (a && !b)
                                Stack.push(false);
                            else
                                Stack.push(true);
                        }
                        if (temp == "<->") {
                            if ((a && b) || (!a && !b))
                                Stack.push(true);
                            else
                                Stack.push(false);
                        }
                    }
                }
            }
            break;
        }
        default:
            break;
    }
    string s;
    if (Stack.top())
        s = "TRUE";
    else
        s = "FALSE";
    return s;
}
/*END*/
