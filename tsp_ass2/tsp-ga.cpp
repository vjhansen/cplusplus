// Victor

#include "tsp-ga.h"
using namespace std;

TSPGenome::TSPGenome(){}

TSPGenome::TSPGenome(const std::vector<int> &order) {
	// initializes the genome from the specified visit order.
    circuitLength = -1; //-dummy value
    visitOrder = order;
}

TSPGenome::TSPGenome(int numPoints) {
    circuitLength = -1; //-dummy value
    for (int i = 0; i < numPoints; ++i) {
        visitOrder.push_back(i); //-push [0 1 2 3 ... numPoints-1] into a vector
    }
    random_shuffle(visitOrder.begin(), visitOrder.end()); //-randomly permute the vector.
}

void TSPGenome::mutate() {
  //-Mutates the genome by swapping two randomly-selected values in the order vector.
     int i = rand() % (visitOrder.size()-1) +1;
     int j = rand() % (visitOrder.size()-1) +1;
     while (j == i) {   //-loop as long as the 2nd value == 1st value.
        j = rand() % (visitOrder.size()-1) +1;
     }
     std::swap(visitOrder[i], visitOrder[j]); 
}

void TSPGenome::computeCircuitLength(const std::vector<Point>& points){
  circuitLength = 0;

    for (int i = 0; i < visitOrder.size(); i++){
        circuitLength += points[visitOrder[i]].calcDist(points[visitOrder[(i + 1) %
                                             (visitOrder.size())]]);
    }
  
  /*std::vector<int>::const_iterator order_iter = visitOrder.begin();
  Point start = points[*order_iter];    // Store starting value for roundtrip
  Point currPos = points[*order_iter];  // Current position
  
  while (order_iter != visitOrder.end()) {
    circuitLength  += points[*order_iter].calcDist(currPos); // similar to points[order[i]].calcDist(points[order[i+1]]);
    currPos = points[*order_iter];
    order_iter++;
  }
  circuitLength += currPos.calcDist(start);*/
}

  double TSPGenome::getCircuitLength() const {
    return circuitLength;
  }

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2) {
    std::vector<int> newOrder; // offspring
    std::set<int> track;
    int index = rand() % g1.getOrder().size();
    for (int i = 0; i < index; i++) {
        track.insert(g1.getOrder()[i]);
        newOrder.push_back(g1.getOrder()[i]); // copy g1's order-values at indexes [0, i-1] to the new vector. 
    }
    // iterate through g2's entire vector, copying each value to the new result vector, 
    for (int i = 0; i < g2.getOrder().size(); ++i) {
    	if (track.count(g2.getOrder()[i]) != newOrder.at(i)) {
    		newOrder.push_back(g2.getOrder()[i]); 
    	}
    }
    return(TSPGenome(newOrder));
}

bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2) {
  //return true if g1 has a shorter circuit length than g2; 
  if(g1.getCircuitLength() < g2.getCircuitLength()) return true;
  return false;
}

TSPGenome findAShortPath(const std::vector<Point> &points,
  int populationSize, int numGenerations, 
  int keepPopulation, int numMutations) {

  std::vector<TSPGenome> population; //population
  int g1, g2;

  // generate random(?) genomes (population), size of genome = # of points
  for (int i = 0; i < populationSize; i++) {
    population.push_back(TSPGenome(points.size()));
  }
  std::sort(population.begin(), population.end(), isShorterPath);
  for (int gen = 0; gen < numGenerations; gen++) {
    for (int i = 0; i < populationSize; i++) {
      population[i].computeCircuitLength(points);   // compute circuit length for each genome
    }
    if (gen % 10 == 0) {
      std::cout<<"Generation " << gen 
        << ": shortest path is "<<population[0].getCircuitLength()
        <<std::endl;
    }
    //keepPopulation specifies how many individuals to keep from the existing population
    for (int i = keepPopulation; i < populationSize; i++) {
      g1 = rand() % keepPopulation;
      g2 = rand() % keepPopulation;
      population[i] = crosslink(population[g1], population[g1]);
    }
    // numMutations specifies how many mutations to apply to the population. 
    for (int i = 0; i < numMutations; i++) {
      population[1+rand() % (populationSize-1)].mutate();
    }
  }
    std::sort(population.begin(), population.end(), isShorterPath);
  return population[0];
}
