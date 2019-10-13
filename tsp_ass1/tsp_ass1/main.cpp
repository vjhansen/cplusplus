//  USN, Kongsberg
//  OOP4200
//  Travelling salesman problem, v1
//  Naive solution: O(n!)
//  Victor J. Hansen, 2019

// clang++ -std=c++11 -stdlib=libc++ main.cpp  

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include "point.h" //Point class


//-Overloaded constructor
Point::Point(double x, double y, double z) {
    x_coord = x;
    y_coord = y;
    z_coord = z;
}

Point::~Point(){} //-Destructor

//-3D Euclidean space: sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
double Point::calcDist(const Point &p) const {
    return sqrt(pow(p.getX_coord()-x_coord,2) 
                + pow(p.getY_coord()-y_coord,2) 
                + pow(p.getZ_coord()-z_coord,2));
}

//-Reading .txt-file containing points
static void read_txt_and_fill(std::vector<Point>& txt_points) {
    std::ifstream myfile;
    std::vector<int> read_point;
    myfile.open("test-2.txt");
    if (myfile.is_open()) {
        int points;
        while (myfile>>points) {
            read_point.push_back(points);
        }
        myfile.close();
    }
    else std::cout<<"Unable to open file.";
    int n=1;
    // read_point.front() = number of points, i.e. 5 for test-5.txt
    for (int i=0; i<read_point.front(); i++) {
        Point new_Points(read_point.at(n),read_point.at(n+1),read_point.at(n+2));
        txt_points.push_back(new_Points);
        n+=3; // needed to place points into x, y and z.
    }
}

void manualFill(std::vector<Point>& fill_points) {
    double x,y,z;
    std::cout<<"\nHow many points? ";
    int size;
    std::cin>>size;
    for (int i=0; i<size; i++) {
        std::cout<<"Point("<<i<<"): ";
        std::cin>>x>>y>>z;
        Point new_Points(x,y,z);
        fill_points.push_back(new_Points);
    }
}

//-Print points
void printVec(const std::vector<Point>& points) {
    std::cout<<"\nWe have "<<points.size()<<" points\n";
    for (int i=0; i<points.size(); i++) {
        std::cout<<"Point("<<i<<"): "<<points[i].getX_coord()
        <<", "<<points[i].getY_coord()
        <<", "<<points[i].getZ_coord()<< std::endl;
    }
}

/*  Function takes a vector of points, and the order in which those points are visited.
    Then computes total length of path when the points are traveled in a specified order.
    The path is a complete round trip */
double circuitLength(const std::vector<Point>& points, const std::vector<int>& order) {
    double dist_tot = 0.0;
    std::vector<int>::const_iterator order_iter = order.begin();
    Point start = points[*order_iter];    // Store starting value for roundtrip
    Point currPos = points[*order_iter];  // Current position

    while (order_iter != order.end()) {
        dist_tot+=points[*order_iter].calcDist(currPos); // similar to points[order[i]].calcDist(points[order[i+1]]);
        currPos=points[*order_iter];
        order_iter++;
    }
    dist_tot+=currPos.calcDist(start); // distance from end point ('current' when we've reached the end) back to starting point
    return dist_tot; // total distance
}

/*  Function takes a vector of points, and returns a vector that specifies the order to visit all of the points in a single round trip.
    Visiting each point once, to ensure that the trip is as short as possible. This function will solve the TSP. */
std::vector<int> findShortestPath(const std::vector<Point>& points) {
    std::vector<int> bestPath;
    std::vector<int> currPath(points.size());
    double shortestDist;

    for (int i=0; i<currPath.size(); i++) {
        currPath[i]=i; // [0 1 2 3 n-1 n]
    }
    shortestDist = circuitLength(points, currPath); // calculate reference distance in chronological order [0 1 2 n]
    bestPath = currPath;
    while (std::next_permutation(currPath.begin(),currPath.end())) {
    	if ((circuitLength(points, currPath) < shortestDist)) {
            shortestDist = circuitLength(points, currPath);
            bestPath = currPath;
        }
    }
    return bestPath;
}

static void printPath(std::vector<int> &shortestPath) {
    std::cout<<"\nBest order: [ ";
    for (int i=0; i<shortestPath.size(); i++) {
        std::cout<<shortestPath.at(i)<<' ';
    }
    std::cout<<"]";
}

int main() {
    std::vector<Point> points;
    int choice = 0;
    std::cout<<"Travelling salesman problem\n"
    		<<"\t1. Read points from .txt-file.\n"
    		<<"\t2. Fill in points manually.\n"
    		<<"\tYour choice: ";
    std::cin>>choice;
    if (choice == 1) {
        std::cout<<"\n**reading from .txt-file**\n";
        read_txt_and_fill(points);
    } else if (choice == 2) {
        manualFill(points);
    }

    printVec(points);
    std::vector<int> shortestPath;
    shortestPath = findShortestPath(points);
    printPath(shortestPath);
    std::cout<<"\nShortest distance: "<<circuitLength(points, shortestPath)<<std::endl;
    points.clear();
    return 0;
}
