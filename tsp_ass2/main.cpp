//  USN, Kongsberg
//  OOP4200
//  Travelling salesman problem, v2
//  Genetic algorithms (GAs)
//  Victor J. Hansen, October 2019

//  clang++ -g -std=c++11 -stdlib=libc++ -Wall main.cpp tsp-ga.cpp


// sjekk hvilke av disse som trengs
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <set>

#include "point.h"  // Point class
#include "tsp-ga.h" //


//-Overloaded constructor
Point::Point(double x, double y, double z): x_coord(x), y_coord(y), z_coord(z){}

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
    std::cout<<"\nHow many points?\n(2, 5, 8, 10, 12, 30, 60, 100, 300, 500): ";
    int size;
    std::cin>>size;
    std::string filestr ="test-txt/test-"+std::to_string(size)+".txt"; 
    myfile.open(filestr);
    if (myfile.is_open()) {
    	std::cout<<"\n** reading from .txt-file **\n";
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
        n+=3; // needed to insert points into x, y and z.
    }
}

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

int main(int argc, char **argv) {
    std::vector<Point> points;
    read_txt_and_fill(points);
    if (points.size() < 60) {
        printVec(points);
    }
    else std::cout<<"Read "<<points.size()<<" points"<<std::endl;

    unsigned int popSize;   // positive int
    unsigned int numGen;    // positive int
    float keepPop;          // float [0, 1] % of population to keep
    float numMut;           // positive float, e.g. 1.5*pop

    //https://www.cs.swarthmore.edu/~newhall/unixhelp/C_commandlineargs.php

    /* popSize = (int) atoi(argv[1]);
    int numGen = (int) atoi(argv[2]);
    int keepPop = (int) ( atof(argv[3]) * ((double)popSize + 0.5 ));
    int numMut = (int) (popSize * atof(argv[4]));*/

    std::cout<< "\nEnter population: ";
    std::cin>>popSize;
    std::cout<< "\nEnter number of generations: ";
    std::cin>>numGen;
    std::cout<< "\nKeep (float)[0, 1]: ";
    std::cin>>keepPop;
    std::cout<< "\nMutation (float): ";
    std::cin>>numMut;

    if (popSize<0||numGen<0||keepPop<0||keepPop>1||numMut<0) {
        std::cout<<"**Values out of range**"<<std::endl;
        exit(1);
    }
    numMut = (int)popSize*numMut;
    keepPop =  (int)(double(popSize+0.5))*keepPop;
        
    srand(time(nullptr)); // generate a different random sequence each time it runs
    TSPGenome path(points.size());
    path = findAShortPath(points, popSize, numGen, keepPop, numMut);
    std::cout<<"\nShortest distance: "<<path.getCircuitLength()<<std::endl;
    printPath(path.getOrder());
    points.clear();
    return 0;
}
