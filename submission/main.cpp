#include "process.h"

int main() {
    string math;
    string logic;
    cin >> math >> logic;
    cout << Infix2Postfix(math) << endl;
    cout << LogicInfix2Postfix(logic);
    return 0;
}