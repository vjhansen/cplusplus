/*
 W03 - assignment 2
 1. Create a class SecretAgent where the access to class Human is private.
 
 2.Add the data number (007 or similar) include this get and set methods, verify that these can be used in the main(), while the others can not.
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
    void setName() {
        std::string n;
        Name = n;
    }
    void setAge() {
        int a = 0;
        Age = a;
    }
    
    virtual void printHuman() {
        std::cout<<"Name: "<<Name<<std::endl <<"Age: "<< Age << std::endl;
    }
    
private:
    std::string Name;
    int Age;
};

class SecretAgent : private Human {
public:
    
    SecretAgent(){
    //Name = " "; //- private member of human
    //Age = 0;    //- private member of human
        agentNr = " ";
        std::cout<<"Creating default Agent"<<std::endl;
    }
    
    SecretAgent(std::string n, int a, std::string a_nr) {
    //Name = n; //- private member of human
    //Age = a;  //- private member of human
        agentNr = a_nr;
        std::cout<<"Creating overloaded Agent"<<std::endl;
    }
    
    std::string getAgentNr () const {return agentNr;}
    void setAgentNr() {
        std::string a_nr = "007";
        agentNr = a_nr;
    }
    
    void printAgent() {
        Human::printHuman();
        std::cout<<"Agent: "<<agentNr<<std::endl;
    }
    
private:
    std::string agentNr;
};

//------------------------------------
int main() {
    SecretAgent james;
    james.setAgentNr();
    james.printAgent();
    
    SecretAgent S("Stalin",40,"008");
    S.printAgent();
    return 0;   
    // only the agentNr will be printed.
}
