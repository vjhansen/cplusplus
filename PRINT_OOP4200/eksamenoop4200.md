// eksamen oop4200
Konverter til pdf når ferdig.

Det koster mer å printe ut fargekopier..


Mail til Olaf: ser at "all written" support material er tillat på eksamen. 
Innebærer dette f.eks. selvskrevne notater, og bøker lånt på bibliotek?


VHDL (45%) fra lectures, discussions, summary, assignments, 


C++ (45%) fra lectures, assignments, discussions


ADA (5%)


MODULE CONTENT

Pointers and memory
Classes and objects
Inheritance
Abstract and interface classes
Polymorphism
I/O
Templates and generic programming
Exceptions
Support for multithreading
Differences between programming languages
VHDL programming



### C++
#### Basic
a. What #include statement do you always put at the top of your programs?
```#include <iostream>```

b. What using statement do you always put at the top of your programs?
```using namespace std;```

c. Declare an integer variable N and initialize it to 10.
```int N = 10;```

d. Give a statement to increase the value of variable N by 10.
```N = N + 10;```

e. What library would you include if you wanted to use the sin, cos, and tan functions?
```<cmath>```

f. What library would you include it you wanted to do file input/output?
```<fstream>```

g. What library would you include if you wanted to use vectors?
```<vector>```

h. What library would you include if you wanted to use pseudo-random numbers?
```<cstdlib>```




 #### Create a program that reads two numbers and a operator and prints the result.
 
 Example (The text at the back> in each line is read during execution):
 Numbers 1> 20
 Operator> *
 Numbers 2> 5
 The answer of 20 * 5 is 100.


```#include <iostream>

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
    
    if (!cin){
        cout << "Numbers please.." << endl;
        cin.clear();
    }
    
    switch (op) {
        case '*':
            cout << "The answer of " << num1 << op << num2 << " is " << num1*num2 << endl;
            break;
            
        case '+':
            cout << "The answer of " << num1 << op << num2 << " is " << num1+num2 << endl;
            break;
            
        case '-':
            cout << "The answer of " << num1 << op << num2 << " is " << num1-num2 << endl;
            break;
            
        case '/':
            if (num2==0) {
                cout << "Don't divide by zero!" << endl;
            }
            else
            cout << "The answer of " << num1 << op << num2 << " is " << num1/num2 << endl;
            break;
            
        case '%':
             cout << "The answer of " << num1 << op << num2 << " is " << num1%num2 << endl;
             break;        
        default:
            break;
    }
    return 0;
} ```






