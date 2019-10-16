/*
 Template assignment 2
 Implement these mathematical operations by using templates:
 answer = myAbs(x);
 answer = myAdd(x,y);
 answer = myPow(x,int);
 
 Demonstrate that your code works by printing:
 myAbs(-5) myAbs(-3.14)
 myAdd(5,-5) myAdd(2.71, -3.14) myAdd('1','G')
 myPow(3.14,10) myPow('c',2)
 
 What happens if we have two string-objects s1 "hei” and  s2 "hallo":
 myAbs(s1);
 myAdd(s1,s2);
 myPow(s2,2);
 */


/*
 template <typename T> // class = typename
 T GetMax (T a, T b) {
     return (a>b ? a:b); // (condition ? value_if_true : value_if_false)
 }
int i=1, j=2, k;
char x='a',y='f',z;
k = GetMax(i, j); // int GetMax (int a, int b);
z = GetMax(x, y); // char GetMax (char a, char b); 
*/



// create objects


#include <iostream>
#include <cmath>

template <typename T>
T myAbs(T x){
    return (x*((x>0)-(x<0)));
    //return abs(x);
}

template <typename T>
T myAdd(T x, T y){
    return (x + y);
}

template <typename T>
T myPow(T x, int y){
    return pow(x, y);
}

int main(int argc, const char * argv[]) {
   /* What happens if we have two string-objects s1 "hei” and  s2 "hallo":
    myAbs(s1); // doesnt work because of abs()
    myAdd(s1,s2); --> = heihallo
    myPow(s2,2); // doesnt work because of pow()
    */
    
    std::string s1 = "hei";
    std::string s2 = "hallo";
    
    std::cout<<"myAbs: "<<myAbs(1)<<std::endl;
    std::cout<<"myAdd: "<<myAdd(s1, s2)<<std::endl;
    std::cout<<"myPow: "<<myPow(4, 2)<<std::endl;

    return 0;
}
