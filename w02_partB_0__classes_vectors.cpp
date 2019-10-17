/*
 Create table with:
 Size three(3) that stores objects of the type Student.
 Size three(3) that stores objects of the type pointer to Student.
 
 Alter the name of the three students in their two tables to "Calvin", "Hobbes" and "Dad".
 
 Extra assignment:
    Create a linked list of student objects. Hint: Create a StudentLink class.
 */

#include <iostream>
#include <vector>
#include <string>
//---------------------student.h---------------------------------
class Student {
private:
    std::string Name;
    int Age;
    std::string Degree;
 
public:
    Student();  //-Default constructor
    Student(std::string, int, std::string); //-Overloaded constructor
    
    ~Student(); //-Destructor
    
    //-Accessors (const = not modifiable)
    std::string getName() const;     //-return name
    int getAge() const;             //-return age
    std::string getDegree() const;   //-return degree
    
    //-Mutators (modifiable)
    void setName();     //-modify name
    void setAge();      //-modify age
    void setDegree();   //-modify degree
   
    void printData();
};
//------------------------------------------------------

//-Default constructor (:: = 'scope resolution')
Student::Student() {
    Name = "John Doe";
    Age = -1;
    Degree = "Other degree";
}
//-Overloaded constructor
Student::Student(std::string n, int a, std::string d) {
    Name = n;
    Age = a;
    Degree = d;
}
//-Destructor
Student::~Student() {}

//-----------Get----------------------
std::string Student::getName() const {return Name;}
int Student::getAge() const {return Age;}
std::string Student::getDegree() const {return Degree;}

//-----------Set----------------------
void fillVec(std::vector<Student>& new_students){
    std::string n;
    int a;
    std::string d;

    std::cout<<"How many students? ";
    int size;
    std::cin>>size;
    
    for (int i=0; i<size; i++) {
        std::cout<<"Student("<<i+1<<") name: ";
        std::cin>>n;
        std::cout<<"Student("<<i+1<<") age: ";
        std::cin>>a;
        std::cout<<"Student("<<i+1<<") degree: ";
        std::cin>>d;
        
        Student newStud(n,a,d);
        new_students.push_back(newStud);
    }
}

void printVec(const std::vector<Student>& new_students) {
    for (int i=0; i<new_students.size(); i++) {
        std::cout   <<"Created a student: "<<new_students[i].getName()
                    <<", "<<new_students[i].getAge()
                    <<", "<<new_students[i].getDegree()<< std::endl;
    }
}

int main() {
    std::vector<Student> students;
    fillVec(students);
    printVec(students);
    return 0;
}
