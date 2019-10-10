//  USN, Kongsberg
//  OOP4200
//  Travelling salesman problem, v1
//  Victor J. Hansen, 2019


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

//---------------------Point.h---------------------------------
class Point {
public:
    Point();  //-Default constructor
    Point(float, float, float); //-Overloaded constructor
    
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
    double distanceTo(const Point &p) const;
    
private:
    float x_coord;
    float y_coord;
    float z_coord;
};
//------------------------------------------------------

//-Default constructor (:: = 'scope resolution')
Point::Point() {
    x_coord = 0;
    y_coord = 0;
    z_coord = 0;
}
//-Overloaded constructor
Point::Point(float x, float y, float z) {
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
void fillVec(std::vector<Point>& new_vec_points) {
    
    float x,y,z;
    std::cout<<"How many points(x,y,z)? ";
    int size;
    std::cin>>size;
    
    for (int i=0; i<size; i++) {
        std::cout<<"Point("<<i<<"): ";
        std::cin>>x>>y>>z;
        std::cout<<std::endl;
        Point new_Points(x,y,z);
        new_vec_points.push_back(new_Points);
    }
}

double Point::distanceTo(const Point &p) const {
    float x1, y1, z1;
    float x2, y2, z2;
    
    x1 = x_coord;
    y1 = y_coord;
    z1 = z_coord;

    x2 = p.getX_coord();
    y2 = p.getY_coord();
    z2 = p.getZ_coord();
        
    return sqrt( pow(x2-x1,2)+pow(y2-y1,2)+pow(z2-z1,2) );
}

// a->b =(*a).b, access member through pointer
void printVec(const std::vector<Point>& new_points) {
    for (int i=0; i<new_points.size(); i++) {
        std::cout<<"Point("<<i<<"): "<<new_points[i].getX_coord()
        <<", "<<new_points[i].getY_coord()
        <<", "<<new_points[i].getZ_coord()<< std::endl;
    }
}


static void read_txt_file() {
    std::string line;
    std::ifstream myfile;
    myfile.open("test-2.txt");
    // fil inneholder antall points på linje 1
    // videre inneholder den xyz-coord for hvert punkt.
    
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


/* if the vector 'order' = [3 1 2 0], the total distance will be the sum of:
 - D{3:1} = distance from points[3] to points[1]
 - D{1:2}
 - D{2:0}
 - D{0:3} -- roundtrip
 
 --> D_tot = D{3:1}+D{1:2}+D{2:0}+D{0:3}
 */

double circuitLength(const std::vector<Point>& points, const std::vector<int>& order) {
    float d = 0.0;
    for (int i = 0; i < order.size()-1; i++) {
        d += points[order[i]].distanceTo(points[order[i+1]]);
    }
    d += points[order.size() - 1].distanceTo(points[order[0]]);
    return d;
}

// use permutation
std::vector<int> findShortestPath(const std::vector<Point>& points){
    
    std::vector<int> bestPath;
    std::vector<int> path(points.size());
    double short_Dist, curr_Dist;
    
    for (int i=0; i<path.size(); i++) {
        path[i] = i;
    }
    
    short_Dist = circuitLength(points, path);
    bestPath = path;
    
    while (std::next_permutation(path.begin(),path.end())) {
        curr_Dist = circuitLength(points, path);
        
        if (curr_Dist < short_Dist) {
            short_Dist = curr_Dist;
            bestPath = path;
        }
    }
    return bestPath;
}


static void printPath(std::vector<int> &shortestPath) {
    std::cout <<"Best order: ";
    for (int i = 0; i < shortestPath.size(); i++) {
        std::cout << shortestPath.at(i) << ' ';
    }
}

int main() {
    
    std::vector<Point> points;
    //points.reserve(3);
    fillVec(points);
    printVec(points);
    
    std::vector<int> shortestPath;
    shortestPath = findShortestPath(points);
    printPath(shortestPath);
    
    std::cout<<"\nShortest distance: "<< circuitLength(points, shortestPath)<<std::endl;
    
    //read_txt_file();
    points.clear();
    
    return 0;
}
