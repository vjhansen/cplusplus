/*
 Part B
 Create a program that reads a text string with two numbers and a operator and prints the result.
 
 This text should be interpreted by the program.
 
 Enter two numbers with an operator between> 10 + 15
 The answer to 10 + 15 is 25.
 Enter two numbers with an operator between> 10+15
 The answer to 10 + 15 is 25.
 
 
 Error conditions must be handled. For example, entering an illegal operator or letters and not numbers.


 
 
 */

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {
    
    int num1, num2 = 0;
    string str = "";
    cout << "Enter two numbers with an operator between: "<< flush;
    getline(cin, str);
    
    int len = (int)str.length();
    for (int i = 0; i < len; i++) {
        if (str[i] == ' ' )
        {
            for (int j = i; j < len; j++)
                str[j] = str[j+1];
            len--;
        }
    }
    
    char plus;
    istringstream iss(str);
    iss >> num1 >> plus >> num2;
    
 //use switch..case for -,/,*
 
    cout <<endl<< "The answer to " << num1 << '+' << num2 << " is " << num1 + num2<< endl;
    return 0;
}
