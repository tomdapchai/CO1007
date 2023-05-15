#include<iostream>
#include <cstring>
#include <cmath>
#include <stack>
using namespace std;
int getPriority(char o) {
    if (o == '^')
        return 3;
    if (o == '*' || o == '/' || o == '%')
        return 2;
    if (o == '+' || o == '-')
        return 1;
    return 0;
}
bool greaterOrEqualThan(char a, char b) {
    if (getPriority(a) >= getPriority(b))
        return true;
    else return false;
}
bool isOperator(char str)
{
    if (str == '/' || str == '*' || str == '%' || str == '+' || str == '-' || str == '^')
        return true;
    else return false;
}
bool isOperand(char str)
{
    if ((str >= 'a' && str <= 'z') || (str >= 'A' && str <= 'Z') || (str >= '0' && str <= '9'))
        return true;
    else return false;
}
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
            while (!Stack.empty() && Stack.top() != '(' && greaterOrEqualThan(Stack.top(), input[i])) {
                if (!(!Stack.empty() && Stack.top() == '^' && input[i] == '^')) {
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
int main() {
    string s;
    cin >> s;
    cout << Infix2Postfix(s);
    return 0;
}
