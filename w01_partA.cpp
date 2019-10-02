/*
 Part A
 Create a program that reads two numbers and a operator and prints the result.

 Example (The text at the back> in each line is read during execution):
     Numbers 1> 20
     Operator> *
     Numbers 2> 5
     The answer of 20 * 5 is 100.
 */

#include <iostream>

using namespace std;
int num1, num2;
char op;

int main() {
    cout << "Number 1: " << endl;
    cin >> num1;
    cout << "Operator: " << endl;
    cin >> op;
    cout << "Number 2: " << endl;
    cin >> num2;
    if (op == '*') {
         cout << "The answer of " << num1 << op << num2 << " is " << num1*num2 << endl;
    }
    // and so on for +, -, /
    
    return 0;
}
