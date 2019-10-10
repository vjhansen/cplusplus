//  Travelling salesman problem
//  Victor


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
//---------------------Point.h---------------------------------
class Point {
public:
    Point();  //-Default constructor
    Point(int, int, int); //-Overloaded constructor
    
    ~Point(); //-Destructor
    
    //-Accessors (const = not modifiable)
    int getX_coord() const;     //-return x coordinate
    int getY_coord() const;     //-return y coordinate
    int getZ_coord() const;     //-return z coordinate
    
    //-Mutators (modifiable)
    void setX_coord();     //-modify x coordinate
    void setY_coord();     //-modify y coordinate
    void setZ_coord();     //-modify z coordinate
    
    void printData();
    
private:
    int x_coord;
    int y_coord;
    int z_coord;
};
//------------------------------------------------------

//-Default constructor (:: = 'scope resolution')
Point::Point() {
    x_coord = 0;
    y_coord = 0;
    z_coord = 0;
}
//-Overloaded constructor
Point::Point(int x, int y, int z) {
    x_coord = x;
    y_coord = y;
    z_coord = z;
}
//-Destructor
Point::~Point() {
}

//-----------Get----------------------
int Point::getX_coord() const {return x_coord;}
int Point::getY_coord() const {return y_coord;}
int Point::getZ_coord() const {return z_coord;}

//-----------Set----------------------

//
void fillVec(std::vector<Point*>& new_vec_points) {
    Point* p_points = NULL;
    int x;
    int y;
    int z;
    std::cout<<"How many points(x,y,z)? ";
    int size;
    std::cin>>size;
    
    for (int i=0; i<size; i++) {
        std::cout<<"Point("<<i<<"): ";
        std::cin>>x>>y>>z;
        std::cout<<std::endl;
        p_points = new Point(x,y,z);
        new_vec_points.push_back(p_points);
    }
}

// a->b =(*a).b, access member through pointer
void printVec(const std::vector<Point*> new_points) {
    for (int i=0; i<new_points.size(); i++) {
        std::cout<<"Point("<<i<<"): "<<new_points[i]->getX_coord()
        <<", "<<new_points[i]->getY_coord()
        <<", "<<new_points[i]->getZ_coord()<< std::endl;
    }
}

// some trouble here
static void cleanUP(std::vector<Point*>& points) {
    for (std::vector<Point*>::iterator pObj = points.begin(); pObj!=points.end(); ++pObj) {
        delete *pObj;
    }
    for (int i=0; i<points.size(); ++i) {
        std::cout<<"Deleting: "<<"Point("<<i<<")"<<std::endl;
    }
    points.clear();
}

static void read_txt_file() {
    std::string line;
    std::ifstream myfile;
    myfile.open("test-2.txt");
    
    if (myfile.is_open())
    {
        while ( myfile.good() )
        {
            getline (myfile,line);
            std::cout << line << std::endl;
        }
        myfile.close();
    }
    
    else std::cout << "Unable to open file";
}



int main() {
    
    std::vector<Point*> points;
    points.reserve(3);
    fillVec(points);
    printVec(points);
    cleanUP(points);
        
     //read_txt_file();
    
    return 0;
}
