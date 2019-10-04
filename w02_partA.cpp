/*
 
 Part A
 Create class Student that stores name, age and what degree they are on.

 In the constructor the must be able to accept information to initialise the object, and the constructor must print this to the screen: "Create a Student: <name>, <age>, <Degree>".

 The destructior must print the following message to the screen: "Deleted: : <name>, <age>, <Degree>".
 Also create a method Print() and set and get method for all data.
 
 */

#include <iostream>

class Student {
public:
    // default constructor
    void setData(std::string Name, int age, std::string degree);
    std::string getName(void);
    std::string getDegree(void);
    int getAge(void);

    void PrintData(void);
    
    Student();  // constructor
    ~Student(); // destructor
    
private:
    // data members
    std::string Name;
    int age;
    std::string degree;
};

Student::Student(void) {
    std::cout << "Create a student: <name>, <age>, <degree> \n";
}


Student::~Student(void) {
    std::cout << "Deleted student: "<< Name <<", " << age <<", "<< degree << std::endl;
}

void Student::setData(std::string set_name, int age_set, std::string set_deg) {
    Name = set_name;
    age = age_set;
    degree = set_deg;
}


void Student::PrintData(void) {
    std::cout <<"Created a student: "<< Name <<", " << age <<", "<< degree << std::endl;
}


std::string Student::getName(void) {
    std::cout << "\n" << "Enter name: ";
    std::cin >> Name;
    return Name;
}
std::string Student::getDegree(void) {
    std::cout << "\n" << "Enter degree: ";
    std::cin >> degree;
    return degree;
}
int Student::getAge(void) {
    std::cout << "\n" << "Enter age: ";
    std::cin >> age;
    return age;
}


int main() {
    Student stud1;
    stud1.getName();
    stud1.getAge();
    stud1.getDegree();
    stud1.PrintData();
    return 0;
}
