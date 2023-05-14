#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
int getPriority(string s) {
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
bool greaterOrEqualThan(string a, string b) {
    if (getPriority(a) >= getPriority(b))
        return true;
    else return false;
}
bool isOperator(char s) {
    if (s == '~' || s == '&' || s == '|' || s == '-' || s == '<')
        return true;
    else return false;
}
bool isOperand(char s) {
    if (s >= 'a' && s <= 'z' || s >= 'A' && s <= 'Z')
        return true;
    else return false;
}
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
            while (Stack.top() != "(") {
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
            while (!Stack.empty() && Stack.top() != "(" && greaterOrEqualThan(Stack.top(), temp)) {
                if (!(Stack.top() == "~" && temp == "~")) {
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

int main()
{
    string s;
    cin >> s;
    cout << LogicInfix2Postfix(s);
    return 0;
}
