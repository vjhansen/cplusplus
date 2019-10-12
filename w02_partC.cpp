/*
 Part C
 1. add a static data element to the Student class to store the number of students objects in existence.
 2. Create a function(not method) called Print() and that accepts a Student object as a 'pass by value' transfer.
 3. Make sure that all constructor (including copy constructors) keeps track of number of objects and that the destructor does the same.
 4. Make a PrintNumberOfStudents() method that prints out number of student objects.
 */

#include <iostream>
#include <vector>
#include <string>

// Curiously recurring template pattern
template <typename T>
struct counter {
    static int students_created;
    static int students_alive;
    counter() {
        ++students_created;
        ++students_alive;
    }
    counter(const counter&) {
        ++students_created;
        ++students_alive;
    }
protected: //Protected members are accessible in the class that defines them and in classes that inherit from that class.
    ~counter(){
        --students_alive;
    }
};
template <typename T> int counter<T>::students_created(0);
template <typename T> int counter<T>::students_alive(0);

//------------------------------------------------------
//class Student derives from a class template instantiation using Student itself as template argument.
class Student : counter<Student> {
public:
    Student();
    Student(std::string, int, std::string);
    ~Student(){;}
    
    std::string getName() const;
    int getAge() const;
    std::string getDegree() const;
    void setName();
    void setAge();
    void setDegree();
    void printData();
    
private:
    std::string Name;
    int Age;
    std::string Degree;
};
//------------------------------------------------------
Student::Student(std::string n, int a, std::string d) {
    Name = n;
    Age = a;
    Degree = d;
}

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

void PrintNumberOfStudents(const std::vector<Student>& students){
    std::cout<<"\nNumber of student objects created = "<<counter<Student>::students_created<<std::endl;
    std::cout<<"\nNumber of student objects alive = "<<counter<Student>::students_alive<<std::endl;
}

int main() {
    std::vector<Student> students;
    fillVec(students);
    printVec(students);
    PrintNumberOfStudents(students);
    students.clear(); //Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
    PrintNumberOfStudents(students);
    return 0;
}
