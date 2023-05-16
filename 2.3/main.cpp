#include <iostream>
#include <cstring>
#include <stack>
using namespace std;
int getPriority(string s) {
    if (s == "~")
        return 4;
    if (s == "|" || s == "&")
        return 3;
    if (s == "<-" || "->")
        return 2;
    if (s == "<->")
        return 1;
    return 0;
}
bool greaterThan(string a, string b) {
    if (getPriority(a) > getPriority(b))
        return true;
    else return false;
}
bool isOperator(char s) {
    if (s == '~' || s == '&' || s == '|' || s == '<' || s == '-' || s == '>')
        return true;
    else return false;
}
bool isOperand(char s) {
    if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
        return true;
    else return false;
}
string LogicPostfixPrefixCalculator(string input,string varlue){
    stack<bool> Stack;
    char arrVar[100];
    bool arrVal[100];
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
int main()
{
    string input;
    cin >> input;
    cin.ignore();
    string varlue;
    getline(cin, varlue);
    cout << LogicPostfixPrefixCalculator(input, varlue);
    return 0;
}
