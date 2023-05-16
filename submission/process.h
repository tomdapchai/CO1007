#include <iostream>
#include <cmath>
#include <string>
#include <stack>
#include <iomanip>
using namespace std;

int getPriorityMath(char o);
int getPriorityLogic(string s);
bool greaterOrEqualThanMath(char a, char b);
bool greaterThanMath(char a, char b);
bool greaterOrEqualThanLogic(string a, string b);
bool greaterThanLogic(string a, string b);
bool isOperator(char s);
bool isOpenrand(char s);
int countN(int n);
int reverseNum(int n);
string reverseStr(string s);
string Infix2Postfix(string infix);
string Infix2Prefix(string infix);
string PostfixPrefixCalculator(string input);
string LogicInfix2Postfix(string infix);
string LogicInfix2Prefix(string infix);
string LogicPostfixPrefixCalculator(string input, string varlue);
