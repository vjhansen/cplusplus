/*
 Part B
 Create a program that reads a text string with two numbers and a operator and prints the result.
 This text should be interpreted by the program.
 
 Enter two numbers with an operator between> 10 + 15
 The answer to 10 + 15 is 25.
 Enter two numbers with an operator between> 10+15
 The answer to 10 + 15 is 25.
 */

#include <iostream>
using namespace std;

int main() {
    int num1, num2 = 0;
    char op;
    cout<< "Enter two numbers with an operator between: "<< flush;
    cin>> num1 >> op >> num2;
    
    if (!cin) { // check for invalid input.
        cout<<"Only numbers please"<<endl;
    }
    
    switch (op) {
        case '+':
            cout<<endl<< "The answer to " << num1 << op << num2 << " is " << num1+num2 << endl;
            break;
        case '-':
            cout<<endl<< "The answer to " << num1 << op << num2 << " is " << num1-num2 << endl;
            break;
        case '*':
            cout<<endl<< "The answer to " << num1 << op << num2 << " is " << num1*num2 << endl;
            break;
        case '/':
            if (num2 == 0) { // division by zero
                cout << "Don't divide by zero!";
            }
            else
                cout<<endl<< "The answer to " << num1 << op << num2 << " is " << (double) num1/num2 << endl;
            break;
        default:
            break;
    }
    return 0;
}
