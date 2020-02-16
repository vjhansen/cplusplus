//  OOP4200 -- Travelling Salesman Problem, Genetic algorithms (GAs)
//  Victor J. Hansen -- October 2019 -- USN, Kongsberg

#ifndef POINT_H
#define POINT_H

#include <cmath> // mathematical operations and functions (e.g. pow, sqrt)

class Point{
private:
    double x_coord;
    double y_coord;
    double z_coord;

public:
    Point();  // Default constructor
    Point(double x, double y, double z) : x_coord(x), y_coord(y), z_coord(z) {} // Overloaded constructor
    ~Point(){;} // Destructor
    
    // Accessors (const = not modifiable)
    int getX_coord() const {return x_coord;}    // return x coordinate
    int getY_coord() const {return y_coord;}    // return y coordinate
    int getZ_coord() const {return z_coord;}    // return z coordinate

    // 3D Euclidean space: sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
    double calcDist(const Point& p2) const {
        return sqrt(pow(p2.getX_coord()-x_coord,2)  // pow(base, exponent)
                + pow(p2.getY_coord()-y_coord,2) 
                + pow(p2.getZ_coord()-z_coord,2));
 }
};

#endif