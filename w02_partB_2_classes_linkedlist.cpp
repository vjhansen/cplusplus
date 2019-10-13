/* Create a linked list of student objects.
 [Data|ptr]->[Data|ptr]->[Data|ptr]->Nullptr
 */


#include <iostream>
#include <vector>
#include <string>
//---------------------student.h---------------------------------
class StudentNode {
public:
    StudentNode();  //-Default constructor
    StudentNode(std::string, int, std::string); //-Overloaded constructor
    ~StudentNode(); //-Destructor
        
    std::string Name;
    int Age;
    std::string Degree;
    StudentNode* next;
    
    friend class StudentLink; //-friend class: a class whose members have access to the private members of another class.
};
//------------------------------------------------------
class StudentLink {
public:
    StudentLink();  //-Default constructor
    StudentLink(std::string, int, std::string); //-Overloaded constructor
    ~StudentLink(); //-Destructor
   
    void addData(std::string, int, std::string);
    void print();
private:
    StudentNode* head; // point to head
};

//-Default constructor (:: = 'scope resolution')
StudentNode::StudentNode() {
    Name = "John Doe";
    Age = -1;
    Degree = "Other degree";
}
//-Overloaded constructor
StudentNode::StudentNode(std::string n, int a, std::string d) {
    Name = n;
    Age = a;
    Degree = d;
}
//-Destructor
StudentNode::~StudentNode() {
    std::cout<<"Node deleted";
}

// this:
StudentLink::StudentLink() {
    this->head = NULL;
}

StudentLink::~StudentLink() {
    std::cout<<"\nList deleted\n";
}
void StudentLink::addData(std::string Name, int Age, std::string Degree) {
    StudentNode* Snode = new StudentNode();
    Snode->Name = Name;
    Snode->Age = Age;
    Snode->Degree = Degree;
    Snode->next = this->head;
    this->head = Snode;
}

void StudentLink::print() {
    StudentNode* head = this->head;
    while (head) {
        std::cout<<" -> ["<<head->Name<<", "
        <<head->Age<<", "<<head->Degree<<"]";
        head = head->next;
    }
}

//-----------Set----------------------
static void setValues(StudentLink *list) {
    std::string n;
    int a;
    std::string d;
    std::cout<<"How many students? ";
    int size;
    std::cin>>size;
    
    for (int i=0; i<size; ++i) {
        std::cout<<"Student("<<i+1<<") name: ";
        std::cin>>n;
        std::cout<<"Student("<<i+1<<") age: ";
        std::cin>>a;
        std::cout<<"Student("<<i+1<<") degree: ";
        std::cin>>d;
        std::cout<<std::endl;
        list->addData(n, a, d);
    }
}

int main() {
    StudentLink* list = new StudentLink();
    setValues(list);
    list->print();
    delete list;
    
    return 0;
}
