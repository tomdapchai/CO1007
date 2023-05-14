#include <iostream>
#include <cmath>
#include <cstring>
#include <stack>
#include <iomanip>
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
bool greaterThan(char a, char b) {
    if (getPriority(a) > getPriority(b))
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
int main()
{
    string s;
    getline(cin, s);
    cout << PostfixPrefixCalculator(s);
    return 0;
}
