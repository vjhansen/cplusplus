//  USN, Kongsberg
//  OOP4200
//  Travelling salesman problem, v1
//  Victor J. Hansen, 2019


#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <chrono>

//---------------------Point.h---------------------------------
class Point {
public:
    Point();  //-Default constructor
    Point(double, double, double); //-Overloaded constructor
    
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
    double euclidDist(const Point &p) const;
    
private:
    double x_coord;
    double y_coord;
    double z_coord;
};
//------------------------------------------------------

//-Default constructor (:: = 'scope resolution')
Point::Point() {
    x_coord = 0;
    y_coord = 0;
    z_coord = 0;
}
//-Overloaded constructor
Point::Point(double x, double y, double z) {
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

//-3D Euclidean space
double Point::euclidDist(const Point &p) const {
    double x1, y1, z1;
    double x2, y2, z2;
    x1 = x_coord;
    y1 = y_coord;
    z1 = z_coord;
    x2 = p.getX_coord();
    y2 = p.getY_coord();
    z2 = p.getZ_coord();
    // sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
    return sqrt(pow(x2-x1,2) + pow(y2-y1,2) + pow(z2-z1,2));
}

//-Reading .txt-file containing points
static void read_txt_and_fill(std::vector<Point>& vec_points) {
    std::ifstream myfile;
    std::vector<int> read_point;
    myfile.open("test-10.txt");
    if (myfile.is_open()) {
        int points;
        while (myfile>>points) {
            read_point.push_back(points);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file.";
    
    int n = 1;
    // read_point.front() = number of points, = 5 for test-5.txt
    for (int i=0; i<read_point.front(); i++) {
        Point new_Points(read_point.at(n),read_point.at(n+1),read_point.at(n+2));
        vec_points.push_back(new_Points);
        n += 3; // needed to place points into x, y and z.
    }
}


//-Print points
void printVec(const std::vector<Point>& new_points) {
    std::cout<<"\nWe have "<<new_points.size()<<" points\n";
    for (int i=0; i<new_points.size(); i++) {
        std::cout<<"Point("<<i<<"): "<<new_points[i].getX_coord()
        <<", "<<new_points[i].getY_coord()
        <<", "<<new_points[i].getZ_coord()<< std::endl;
    }
}


/*  Function takes a vector of points, and the order in which those points are visited.
    Then computes total length of path when the points are traveled in a specified order.
    The path is a complete round trip */
double circuitLength(const std::vector<Point>& points, const std::vector<int>& order) {
    double D_tot = 0.0; // total distance
    std::vector<int>::const_iterator iter = order.begin();
    Point start = points[*iter];    // Store starting value for roundtrip
    Point current = points[*iter];  // Placeholder value
    //iter++;
    while (iter != order.end()) {
        D_tot += points[*iter].euclidDist(current); // similar to points[order[i]].euclidDist(points[order[i+1]]);
        current = points[*iter];
        iter++;
    }
    // distance from end point back to starting point
    D_tot += current.euclidDist(start);
    return D_tot;
}

/*  Function takes a vector of points, and returns a vector that specifies the order to visit all of the points in a single round trip.
    Visiting each point once, to ensure that the trip is as short as possible.
    This is the function that will solve the TSP. */
//most demanding function
std::vector<int> findShortestPath(const std::vector<Point>& points) {
    std::vector<int> bestPath;
    std::vector<int> curr_path(points.size());
    double shortest_Dist;

    for (int i=0; i<curr_path.size(); i++) {
        curr_path[i] = i;
    }
    shortest_Dist = circuitLength(points, curr_path); // calculate reference distance in chronological order [0 1 2 n]
    bestPath = curr_path;
    while (std::next_permutation(curr_path.begin(),curr_path.end())) {
        if (circuitLength(points, curr_path) < shortest_Dist) {
            shortest_Dist = circuitLength(points, curr_path);
            bestPath = curr_path;
        }
    }
    return bestPath;
}

static void printPath(std::vector<int> &shortestPath) {
    std::cout <<"\nBest order: [ ";
    for (int i = 0; i < shortestPath.size(); i++) {
        std::cout << shortestPath.at(i) << ' ';
    }
    std::cout<<"]";
}

int main() {
    std::vector<Point> points;
    std::cout<<"reading from .txt-file\n";
    read_txt_and_fill(points);

    printVec(points);
    std::vector<int> shortestPath;
    
    auto start = std::chrono::high_resolution_clock::now();
    shortestPath = findShortestPath(points);
    printPath(shortestPath);
    std::cout<<"\nShortest distance: "<< circuitLength(points, shortestPath)<<std::endl;
    
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Computation time: "<< duration.count() << " microseconds" << std::endl;
    
    points.clear();
    return 0;
    //txt-12 -- Shortest distance:  47.6887
}
