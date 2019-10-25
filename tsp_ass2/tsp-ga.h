// Victor J. Hansen
// tsp-ga.h

#ifndef TSPG_H
#define TSPG_H

#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <cstdlib>
#include "point.h"

class TSPGenome {
private:
	double circuitLength; //
	std::vector<int> visitOrder; //

public:
	TSPGenome();
	TSPGenome(int numPoints); //
	TSPGenome(const std::vector<int> &order); //
	~TSPGenome(){;} // destructor
	std::vector<int> getOrder() const {return visitOrder;} //
	double getCircuitLength() const {return circuitLength;} // get the total distance covered if the points are visited in a circuit, in the specified order.
    void computeCircuitLength(const std::vector<Point>& points); //
    void mutate(); //
};

TSPGenome findAShortPath(const std::vector<Point>& points, //
  int populationSize, int numGenerations, 
  int keepPopulation, int numMutations);

TSPGenome crosslink(const TSPGenome& g1, const TSPGenome& g2); //

#endif
