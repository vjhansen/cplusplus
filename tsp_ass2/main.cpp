//  USN, Kongsberg
//  OOP4200
//  Travelling salesman problem, v2
//  Genetic algorithms (GAs)
//  Victor J. Hansen, 2019

// clang++ -std=c++11 -stdlib=libc++ main.cpp  

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <set>

#include "point.h" //Point class
#include "tsp-ga.h"

//-Overloaded constructor
Point::Point(double x, double y, double z) {
    x_coord = x;
    y_coord = y;
    z_coord = z;
}
Point::~Point(){} //-Destructor

//-3D Euclidean space: sqrt( (x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 )
double Point::calcDist(const Point& p2) const {
    return sqrt(pow(p2.getX_coord()-x_coord,2) 
                + pow(p2.getY_coord()-y_coord,2) 
                + pow(p2.getZ_coord()-z_coord,2));
}

//-Reading .txt-file containing points
static void read_txt_and_fill(std::vector<Point>& txt_points) {
    std::ifstream myfile;
    std::vector<int> read_point;
    myfile.open("test-100.txt");
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
        std::cin >> x >> y >> z;
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

 void printPath(const std::vector<int>& shortestPath) {
    std::cout<<"\nBest order: [ ";
    for (int i=0; i<shortestPath.size()-1; i++) {
        std::cout<<shortestPath[i]<<' ';
    }
    std::cout<<shortestPath[shortestPath.size()-1]<<"]"<<std::endl;
}

void PrintNumberOfPoints(const std::vector<Point>& points) {
    std::cout<<"\nNumber of Point objects created = "<<counter<Point>::Points_created;
    std::cout<<"\nNumber of Point objects alive = "<<counter<Point>::Points_alive<<std::endl;
}

int main(int argc, char **argv) {
    //int choice = 0;
    std::vector<Point> points;
   
    std::cout<<"\n**reading from .txt-file**\n";
    read_txt_and_fill(points);
    printVec(points);
    // = points.size();
    unsigned int popSize; // positive int
    unsigned int numGen; // positive int
    float keepPop; // float [0, 1] % of population to keep
    float numMut; //positive float, e.g. 1.5*pop

   // popSize = (int) atoi(argv[1]);
    /*int numGen = (int) atoi(argv[2]);
    int keepPop = (int) ( atof(argv[3]) * ((double)popSize + 0.5 ));
    int numMut = (int) (popSize * atof(argv[4]));*/

    std::cout<< "\nEnter population: ";
    std::cin>>popSize;
    std::cout<< "\nEnter number of generations: ";
    std::cin>>numGen;
    std::cout<< "\nKeep (0-1): ";
    std::cin>>keepPop;
    std::cout<< "\nMutation (float): ";
    std::cin>>numMut;

    if (popSize<0||numGen<0||(keepPop<0 && keepPop>1)||numMut<0) {
        std::cout<<"error";
    } 
    numMut = (int)popSize*numMut;
    keepPop = (int)(double(popSize+0.5))*keepPop;
    srand(time(nullptr));
    TSPGenome path(points.size());
    path = findAShortPath(points, popSize, numGen, keepPop, numMut);
    std::cout<<"\nShortest distance: "<<path.getCircuitLength()<<std::endl;
    printPath(path.getOrder());
    return 0;
}
