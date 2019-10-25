// Victor J. Hansen
// USN Kongsberg
// OOP4200 - C++
// Travelling Salesman 
// Genetic algorithm


#include "tsp-ga.h"


TSPGenome::TSPGenome(){} //default constructor

TSPGenome::TSPGenome(const std::vector<int>& order) { //-initializing genome from the specified visit order.
    circuitLength = 1e9; //-dummy value
    visitOrder = order;
  }


TSPGenome::TSPGenome(int numPoints) { //-takes the number of points that will be visited
  for (int i = 0; i < numPoints; i++) {
    visitOrder.push_back(i); //-push [0 1 2 3 ... numPoints-1] into a vector
  }
  random_shuffle(visitOrder.begin(), visitOrder.end()); //-generates a random order to visit points
  circuitLength = 1e9; //-dummy value
}

void TSPGenome::mutate() {
  //-Mutates the genome by swapping two randomly-selected values in the order vector.
  int i = rand() % (visitOrder.size()); //creates value [0, size-1]
  int j = rand() % (visitOrder.size());
  while (j == i) {   //-loop as long as the 2nd value == 1st value.
    j = rand() % (visitOrder.size());
  }
  std::swap(visitOrder[i], visitOrder[j]); //
}
// fitness function
void TSPGenome::computeCircuitLength(const std::vector<Point>& points) {
  circuitLength = 0;
  for (int i = 0; i < visitOrder.size(); i++) {
    circuitLength += points[visitOrder[i]].calcDist(points[visitOrder[(i+1)%(visitOrder.size())]]);
  }
}  

//-mechanism to produce offspring from the "best" parents.
TSPGenome crosslink(const TSPGenome& g1, const TSPGenome& g2) {
  std::vector<int> newOrder; //-offsprings order
  std::set<int> myset;  //-store unique elements following a specific order.
  int index = rand() % g1.getOrder().size();
  for (int i = 0; i < index; i++) {
    myset.insert(g1.getOrder()[i]); //-inserting only new (unique) elements
    newOrder.push_back(g1.getOrder()[i]); //-copy g1's order-values at indexes [0, i-1] to new vector. 
  }
  // iterate through g2's entire vector, 
  for (int i = 0; i < g2.getOrder().size(); i++) {
    if (myset.count(g2.getOrder()[i]) == 0) { //-check if g2's vector has elements that doesn't already appear in the new vector.
      //-Because all elements in a set container are unique, the function can only return 1 (if the element is found) or zero (otherwise).
      //-we do this to ensure that each value appears exactly once in the new vector
      newOrder.push_back(g2.getOrder()[i]); //-copying each value of g2's vector into the new result vector
      myset.insert(g2.getOrder()[i]);
    }
  }
  myset.clear();
  return(TSPGenome(newOrder)); //-create a new TSPGenome object.
}

bool isShorterPath(const TSPGenome& g1, const TSPGenome& g2) { //
  return (g1.getCircuitLength() < g2.getCircuitLength());
}

/*  1.Generate initial population of random genomes. 
      The size of each genome is the number of points.
    2.Iterate over the population and compute the circuit length for each member.
      Since the circuit length is the fitness function, 
        we can now sort the vector of genomes with the circuit length. */
TSPGenome findAShortPath(const std::vector<Point>& points,
  int populationSize, int numGenerations, 
  int keepPopulation, int numMutations) {
  std::vector<TSPGenome> population; //population
  
  // generate random genomes (population), size of genome = # of points
  for (int i = 0; i < populationSize; i++) {
    population.push_back(TSPGenome(points.size()));
  }
  // looping through generations
  for (int gen = 0; gen < numGenerations; gen++) {
    for (int i = 0; i < populationSize; i++) {
      population[i].computeCircuitLength(points);   // compute circuit length for each genome
    }
    std::sort(population.begin(), population.end(), isShorterPath); //
    if (gen % 10 == 0) {
        std::cout<<"\nGeneration "<<gen<<" shortest path: "
        		<<population[0].getCircuitLength()<<std::endl; //best solution so far
    }
    // keepPopulation specifies how many individuals to keep from the existing population
    // we have to replace the remaining members with new genomes produced from the fittest ones.
    for (int i = keepPopulation; i < populationSize; i++) {
      std::size_t g1 = rand() % (keepPopulation);
      std::size_t g2 = rand() % (keepPopulation);
      // generate new genomes into the existing population, overwriting the existing members. 
      population[i] = crosslink(population[g1], population[g2]);
    }
    // numMutations specifies how many mutations to apply to the population
    for (int i = 0; i < numMutations; i++) {
      population[1+rand() % (populationSize-1)].mutate();
    }
  }
  return population[0];
}
