/*
Template assignment 1
clang++ -std=c++11 -stdlib=libc++ main.cpp 

1. Compile and run the swap example
2. Verify that that the program actually swaps the values.
3. Can you swap the value of two objects of the class string or your home made CString?


3. You can swap the value of two objects of the class/type string.
As long as your types support copying (via copy constructor and copy assignment operator), 
    the default swap implementation will let objects of your types be swapped without 
    your having to do any special work to support it.

However, the default swap implementation may not thrill you. 
It involves copying three objects: a to temp, b to a, and temp to b. 
For some types, none of these copies are really necessary. 
For such types, the default swap puts you on the fast track to the slow lane.

Foremost among such types are those consisting primarily of a pointer to another type that contains the real data. 

Effective C++, Scott Meyers
*/


#include <iostream>
#include <cmath>
#include <string>

class abc {
public:
	abc();
	abc(std::string);
	~abc(){;}
	
	std::string getString() const;

private:
	std::string str;
};

abc::abc() {
	str = " ";
}

abc::abc(std::string s) {
	str = s;
}

std::string abc::getString() const {return str;}

template <class X>
void Swap(X& a, X& b) {
    X temp;
    // pass by value needs a copy constructor
    // pass by reference doesn't need a copy constructor
    temp = a;   // temp gets address of a
    a = b;      // a gets address of b
    b = temp;   // b gets address of temp (=a)
}

int main() {
    int nI = 10, nJ = 2;
    char c1 = 'B', c2 = 'A';
    float f1 = 0.0, f2 = -1.0;
    std::string s1 = "Hei";
    std::string s2 = "Hallo";
    const char * Cstr1 = "Chei";
    const char * Cstr2 = "Challo";

    abc a("hei");
    abc b("hallo");

    Swap(nI, nJ); // ok
    Swap(c1, c2); // ok
    Swap(f1, f2); // ok
    Swap(s1, s2); // ok
    Swap(Cstr1, Cstr2); // ok   

    Swap(a,b); // ok
    std::cout<<a.getString()<<" " <<b.getString();
    return 0;
}