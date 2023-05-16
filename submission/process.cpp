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
bool isOperator(char s)
{
    if (s == '/' || s == '*' || s == '%' || s == '+' || s == '-' || s == '^' || s == '~' || s == '&' || s == '|' || s == '<')
        return true;
    else return false;
}
int isOperand(char s)
{
    if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z') || (s >= '0' && s <= '9'))
        return 1;
    else return 0;
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
