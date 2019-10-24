/*

W05 - Exception assignment

1. Create a class ZeroException that inherits from the exception-class in STL.

2. Let it have a public attribute 'teller' that contains information about 
	what the divider attempted to divide by zero.

3. Create a function float divide(int numerator, int divisor); that verifies that 
	the divisor is not 0 before an answer is attempted. 
	If the divisor is 0 then the ZeroException should be generated.

4. Create a function void testDivisor(void); that runs in an infinite loop 
	and tries to divide a counting number by random numbers from 0 to 100.

5. This function should also catch ZeroExceptions, 
	and write how many times the division managed to run without generating a divide by zero.

6. ZeroException should be regenerated to main(), that will terminate the program.

Pseudo code for testDivisor:

for i = 1 to INFINITY do
try
	divide() by a random number(0,100)
catch e
	write “Got divided " + e.teller + " by zero "
throw e
*/


/*
try block:
	The code which can throw/cause an exception is kept inside a try block. 
	Then, when the code leads to an error, that error/exception will get caught inside the catch block.

catch block:
	Catch the error and handle the exception condition. 
	We can have multiple catch blocks to handle different types of 
		exception and perform different actions when the exceptions occur. 
	e.g., we can display descriptive messages to explain why any particular excpetion occured.

throw statement:
	Throw exceptions to exception handler i.e. it is used to communicate information about error. 
	A throw expression accepts one parameter and that parameter is passed to handler.
	A throw statement is used when we explicitly want an exception to occur, 
		then we can use throw statement to throw or generate that exception.
*/


#include <iostream>
#include <exception>
#include <cstdlib>

class ZeroException : public std::exception {
public:
	ZeroException() {}
	ZeroException(int);
	~ZeroException(){;}
  	int getTeller() const {return teller;}
    	void setTeller(int t) {teller = t;}
	int teller;	// what the divider attempted to divide by zero.
};

ZeroException::ZeroException(int t) : teller(t){}

float divide(int numerator, int divisor) {
	if (divisor == 0) {
		ZeroException e;
		e.setTeller(numerator);
		throw e; // throw exception
	}
	return (numerator/divisor);
}

void testDivisor(void) {
	for (int i=1 ;; i++) { // infinite loop
		try { divide(i, rand()%100); }
		catch (const ZeroException& e) {
			std::cout<<"Divided "<< i <<" times without generating a divide by zero."<<std::endl;
			std::cout<<"Got divided: "<<e.getTeller()<<" by zero. "<<std::endl;
			exit(1);
		}
	}
}


int main() {
	testDivisor();
	return 0;
}
