#include <iostream>
#include <math.h>
#include <string>
#include <stack>
using namespace std;

bool isOperator(char s);
int isOperand(char s);
int getPriorityMath(char o);
int getPriorityLogic(string s);
bool greaterOrEqualThanMath(char a, char b);
bool greaterThanMath(char a, char b);
bool greaterOrEqualThanLogic(string a, string b);
bool greaterThanLogic(string a, string b);
int countN(int n);
int reverseNum(int n);
string reverseStr(string s);
