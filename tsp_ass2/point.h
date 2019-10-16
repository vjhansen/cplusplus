
#ifndef POINT_H
#define POINT_H


// Curiously recurring template pattern
template <typename T>
struct counter {
    static int Points_created;
    static int Points_alive;
    counter() {
        ++Points_created;
        ++Points_alive;
    }
    counter(const counter&) {
        ++Points_created;
        ++Points_alive;
    }
protected: //Protected members are accessible in the class that defines them and in classes that inherit from that class.
    ~counter(){
        --Points_alive;
    }
};
template <typename T> int counter<T>::Points_created(0);
template <typename T> int counter<T>::Points_alive(0);


class Point : counter<Point> {
public:
    Point();  //-Default constructor
    Point(double, double, double); //-Overloaded constructor
    
    ~Point(); //-Destructor
    
    //-Accessors (const = not modifiable)
    int getX_coord() const {return x_coord;}    //-return x coordinate
    int getY_coord() const {return y_coord;}    //-return y coordinate
    int getZ_coord() const {return z_coord;}    //-return z coordinate

    //-Mutators (modifiable)
    void setX_coord();     //-modify x coordinate
    void setY_coord();     //-modify y coordinate
    void setZ_coord();     //-modify z coordinate
    
    void printData();
    double calcDist(const Point &p) const;
    
private:
    double x_coord;
    double y_coord;
    double z_coord;
};

#endif