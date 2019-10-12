/*
 W03 - assignment 1
 1. Create class Human that can store the data name og age:
 2. Create constructor
 3. get- and set-methods
 4. Print method
 5. Create two classes, Student and Professor, with the added data ects (for Student) and papers (for Professors):
 6. Constructor calls the constructor in the base class and use that for initialising the class.
 7. get- and set-methods
 8.Print that also used the base class print method
 */



#include <iostream>
#include <string>

//------------------------------------
class Human {
public:
    Human() {
        std::cout<<"Creating default Human"<<std::endl;
    }
    Human(std::string n, int a) {
        Name = n;
        Age = a;
        std::cout<<"Creating overloaded Human"<<std::endl;
    }
    
    // Get (accessors)
    std::string getName() const {return Name;}
    int getAge() const {return Age;}
    
    // Set (mutators)
    void setName(std::string n) {Name = n;}
    void setAge(int a) {Age = a;}
    
    virtual void printHuman() {
        std::cout<<"Name: "<<Name<<std::endl
        <<"Age: "<<Age<<std::endl;
    }
    
private:
    std::string Name;
    int Age;
};
//------------------------------------
class Student : public Human {
public:
    Student(std::string s_name, int s_age, int e) : Human(s_name, s_age) {
        s_name = s_name;
        s_age = s_age;
        ECTS = e;
        std::cout<<"Creating overloaded Student"<<std::endl;
    }
    int getECTS() const {return ECTS;}
    void printStudent() {
        Human::printHuman();
        std::cout<<"ECTS: "<<ECTS<<std::endl;
    }
private:
    int ECTS;
};
//------------------------------------
class Professor : public Human {
public:
    Professor(std::string p_name, int p_age, int p) : Human(p_name, p_age) {
        p_name = p_name;
        p_age = p_age;
        Papers = p;
        std::cout<<"Creating overloaded Professor"<<std::endl;
    }
    int getPapers() const {return Papers;}
    void printProfessor() {
        Human::printHuman();
        std::cout<<"Papers: "<<Papers<<std::endl;
    }
private:
    int Papers;
};
//------------------------------------

int main() {
    Student stu("Student",20,300);
    stu.printStudent();
    Professor pro("Prof.",30,50);
    pro.printProfessor();
    return 0;
}
