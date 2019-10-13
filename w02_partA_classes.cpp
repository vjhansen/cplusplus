/*
 
 Part A
 Create class Student that stores name, age and what degree they are on.

 In the constructor the must be able to accept information to initialise the object, and the constructor must print this to the screen: "Create a Student: <name>, <age>, <Degree>".

 The destructior must print the following message to the screen: "Deleted: : <name>, <age>, <Degree>".
 Also create a method Print() and set and get method for all data.
 
 */


#include <iostream>
#include <vector>

//------------------------------------------------------
class Student {
public:
    Student();  //-Default constructor
    Student(std::string, int, std::string); //-Overloaded constructor
    
    ~Student(); //-Destructor
    
    //-Accessors (const = not modifiable)
    std::string getName() const;    //-return name
    int getAge() const;             //-return age
    std::string getDegree() const;  //-return degree
    
    //-Mutators (modifiable)
    void setName();     //-modify name
    void setAge();      //-modify age
    void setDegree();   //-modify degree
    
    void printData();
    
private:
    std::string Name;
    int Age;
    std::string Degree;
};
//------------------------------------------------------


//-Default constructor (:: = 'scope resolution')
Student::Student() {
    std::cout << "Create a student: <name>, <age>, <degree> \n";
    Name = "John Doe";
    Age = -1;
    Degree = "Other degree";
}
//-Overloaded constructor
Student::Student(std::string n, int a, std::string d) {
    std::cout << "Create a student: <name>, <age>, <degree> \n";
    Name = n;
    Age = a;
    Degree = d;
}
//-Destructor
Student::~Student() {
    std::cout << "Deleted student: "<< Name <<", " << Age <<", "<< Degree << std::endl;

}

void Student::printData() {
    std::cout <<"Created a student: "<< Name <<", " << Age <<", "<< Degree << std::endl;
}



//-----------Get----------------------
std::string Student::getName() const {
    return Name;
}
int Student::getAge() const {
    return Age;
}
std::string Student::getDegree() const {
    return Degree;
}

//-----------Set----------------------
void Student::setName() {
    std::string n;
    std::cout<<"Enter name: ";
    std::cin>>n;
    Name = n;
}
void Student::setAge() {
    int a;
    std::cout<<"Enter age: ";
    std::cin>>a;
    Age = a;
}
void Student::setDegree() {
    std::string d;
    std::cout<<"Enter degree: ";
    std::cin>>d;
    Degree = d;
}


int main() {
    Student stud2;
    stud2.setName();
    stud2.setAge();
    stud2.setDegree();
    stud2.printData();
   
    return 0;
}
