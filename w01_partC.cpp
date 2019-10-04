/*
 Part C
 Create a program that reads a text string with multiple numbers and operators and prints the result. This text should be interpreted by the program.
 
 
 Error conditions must be handled. For example, entering an illegal operator or letters and not numbers.
 
 Example (The text at the back of the > is read during execution):
 Enter numbers with an operator between> 2 + 3 * 5
 The answer to 2 + 3 * 5 is 17.
 */

#include <iostream>
#include <string>
#include <sstream>
#define div /

class calculator {
    
public:
    double num1, num2, num3, num4, res1, res2 =0.0;
    char op1, op2, op3;
    void input() {
        std::string str = "";
        std::cout << "Enter numbers with operators between: " << std::flush;
        getline(std::cin, str);
        
        // remove blank space from expression
        int len = (int)str.length();
        for (int i = 0; i < len; i++) {
            if (str[i] == ' ' ) {
                for (int j = i; j < len; j++)
                    str[j] = str[j+1];
                len--;
            }
        }
        
        std::istringstream iss(str);
        iss >> num1 >> op1 >> num2 >> op2 >> num3;
    }
    
    
    // Addition
    void operator +() {
        res1 = num1+num2;

    }
    // Subtraction
    void operator -() {
        res1 = num1-num2;

    }
    // Multiplication
    void operator *() {
        res1 = num1*num2;
    }
    
    void display() {
        if (num3 == '\0') {
                    std::cout << "The answer to " << num1 << op1 << num2 << " is " << res1 << std::endl;

        }
        else std::cout << "The answer to " << num1 << op1 << num2 << op2 << num3 << " is " << res2 << std::endl;

    }
};


int main() {
    calculator Calc1, Calc2;
    Calc1.input();
    
    switch (Calc1.op1) {
        case '+':
            +Calc1;
            break;
        case '-':
            -Calc1;
            break;
        case '*':
            *Calc1;
            break;
            
            //Division
        case '/':
            if (Calc1.num2 == 0) {
                std::cout << "Not allowed" << std::endl;
            }
            Calc1.res1 = Calc1.num1/Calc1.num2;
            break;
            
            // Modulus
        case '%':
            Calc1.res1 = (int)Calc1.num1 % (int)Calc1.num2;
            break;
        default:
            break;
    }
    
    switch (Calc1.op2) {
        case '+':
            Calc1.res2 = Calc1.res1 - Calc1.num3;
            break;
        case '-':
             Calc1.res2 = Calc1.res1 - Calc1.num3;
            break;
        case '*':
            Calc1.res2 = Calc1.res1 * Calc1.num3;
            break;
    }
    Calc1.display();   
    return 0;
}
