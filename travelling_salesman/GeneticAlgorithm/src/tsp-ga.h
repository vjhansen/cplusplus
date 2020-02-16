//  OOP4200 -- Travelling Salesman Problem, Genetic algorithms (GAs)
//  Victor J. Hansen -- October 2019 -- USN, Kongsberg

#ifndef TSPG_H
#define TSPG_H

#include <iostream>
#include <vector>
#include <set> 		 // set container class
#include <algorithm> // Contains functions to be used on ranges of elements (e.g. swap, sort)
#include "point.h"	 // Point class

class TSPGenome {
private:
	double circuitLength; // total distance covered when points are visited in a specified order
	std::vector<int> visitOrder; // the order which the points will be visited
public:
	TSPGenome(){}; // default constructor
	TSPGenome(int numPoints); // constructor that takes # of points to visit
	TSPGenome(const std::vector<int> &order); // constructor that takes order to visit
	~TSPGenome(){;} // destructor
	
	std::vector<int> getOrder() const {return visitOrder;} // get visitOrder
	double getCircuitLength() const {return circuitLength;}
    
    // compute the circuit length
    void computeCircuitLength(const std::vector<Point>& points);
    void mutate(); // mutate genome
};

// find shortest path
TSPGenome findAShortPath(const std::vector<Point>& points, 
  int populationSize, int numGenerations, 
  int keepPopulation, int numMutations);

// create offspring
TSPGenome crosslink(const TSPGenome& g1, const TSPGenome& g2);

#endif