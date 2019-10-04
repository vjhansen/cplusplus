/*
 Part C
 Create a program that reads a text string with multiple numbers and operators and prints the result. This text should be interpreted by the program.
 
 Example (The text at the back of the > is read during execution):
 Enter numbers with an operator between> 2 + 3 * 5
 The answer to 2 + (3 * 5) is 17.
 */

#include <iostream>
#include <string>

class calculator {
    
public:
    double num1, num2, num3, res = 0.0;
    char op1, op2;
    
    void input() {
        std::string str = "";
        std::cout << "Enter numbers with operators between: " << std::flush;
        std::cin >> num1 >> op1 >> num2 >> op2 >> num3;
        
        if ((op1 == '/' && num2 == 0) || (op2 == '/' && num3 == 0))
            std::cout << "You can't divide by zero" << std::endl;
        else if ((op2 == '*' || op2 == '/') && (op1 == '-' || op1 == '+')) {
            switch (op2) {
                case '*':
                    res = num2*num3;
                    break;
                case '/':
                    res = num2/num3;
                    break;
                case '%':
                    res = (int)num2 % (int)num3;
                    break;
                default:
                    break;
            }
            switch (op1) {
                case '+':
                    res = num1+res;
                    break;
                case '-':
                    res = num1-res;
                    break;
                default:
                    break;
            }
        }
        else {
            switch (op1) {
                case '+':
                    res = num1+num2;
                    break;
                case '-':
                    res = num1-num2;
                    break;
                case '*':
                    res = num1*num2;
                    break;
                case '/':
                    res = num1/num2;
                    break;
                default:
                    break;
            }
            switch (op2) {
                case '+':
                    res = res+num3;
                    break;
                case '-':
                    res = res-num3;
                    break;
                case '*':
                    res = res*num3;
                    break;
                case '/':
                    res = res/num3;
                    break;
                default:
                    break;
            }
        }
    }
    
    void display() {
        if (num3 == '\0') {
            std::cout << "The answer to " << num1 << op1 << num2 << " is " << res << std::endl;
        }
        else std::cout << "The answer to " << num1 << op1 << num2 << op2 << num3 << " is " << res << std::endl;
    }
};

int main() {
    calculator Calc;
    Calc.input();
    Calc.display();
    return 0;
}
