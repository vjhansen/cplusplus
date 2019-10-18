// Victor J. Hansen
// USN Kongsberg
// OOP4200 - C++
// Travelling Salesman 
// Genetic algorithm


/*  Genetic algorithm (GA): "a process of natural selection".
    Goal: Optimize towards better solutions.

    Mutation: maintain genetic diversity.
    Crossover (recombination): generate new offspring (child) from existing population (parents)
    Selection: individual genomes are selected from a population for later breeding.

  Genome (genetic material): a way of representing solutions to the problem as a sequence of values. 
    Each genome has its own set of values that specifies a potential solution to the problem being solved.
    Our population is made up of genomes.

E.g., with a problem of n points, a genome might be [(n-2) 0 ... n ... 1 ... (n-1)].
This will be the order that the points are visited. 
Fitness function: the length of the circuit formed by visiting the points in the specified order. 
  Individuals with "better" or "fitter" genomes will have a shorter path; 
  "worse" or "less fit" individuals will specify a longer path. */

#include "tsp-ga.h"


TSPGenome::TSPGenome(){} //default constructor

// initializing genome from the specified visit order.
TSPGenome::TSPGenome(const std::vector<int>& order) { // overloaded constructor
    circuitLength = 1e9; //-dummy value
    visitOrder = order;
  }

// get the total distance covered if the points are visited in a circuit, in the specified order.
double TSPGenome::getCircuitLength() const {return circuitLength;}

// takes the number of points that will be visited, 
// and generates a random order to visit those point
TSPGenome::TSPGenome(int numPoints) {
  for (int i = 0; i < numPoints; i++) {
    visitOrder.push_back(i); // push [0 1 2 3 ... numPoints-1] into a vector
  }
  random_shuffle(visitOrder.begin(), visitOrder.end()); // randomly permute the vector.
  circuitLength = 1e9; // dummy value
}


void TSPGenome::mutate() {
  //-Mutates the genome by swapping two randomly-selected values in the order vector.
  int i = rand() % (visitOrder.size());
  int j = rand() % (visitOrder.size());
  while (j == i) {   //-loop as long as the 2nd value == 1st value.
    j = rand() % (visitOrder.size());
        //std::cout<<visitOrder[i];
  }
  std::swap(visitOrder[i], visitOrder[j]); 
}
// fitness function
void TSPGenome::computeCircuitLength(const std::vector<Point>& points) {
  circuitLength = 0;
  for (int i = 0; i < visitOrder.size(); i++) { // [0 ... n-1]
    circuitLength += points[visitOrder[i]].calcDist(points[visitOrder[(i+1)%(visitOrder.size())]]);
    // e.g. if visitOrder.size() = 12 and we've reached i = 11 (end of order)
    // then visitOrder[(i+1)%(visitOrder.size())]] = visitOrder[(12)%(12)] = visitOrder[0] (start of order)
  }
}  

// mechanism to produce offspring from the "best" parents.
TSPGenome crosslink(const TSPGenome& g1, const TSPGenome& g2) {
  std::vector<int> newOrder; // offsprings order
  std::set<int> track;
  int index = rand() % g1.getOrder().size();
  for (int i = 0; i < index; i++) {
    track.insert(g1.getOrder()[i]);
    newOrder.push_back(g1.getOrder()[i]); // copy g1's order-values at indexes [0, i-1] to the new vector. 
  }

  // iterate through g2's entire vector, copying each value to the new result vector, 
  for (int i = 0; i < g2.getOrder().size(); i++) {
  //track.count(g2.getOrder()[i]) == newOrder.at(i)
    if (track.count(g2.getOrder()[i]) == 0) {
      newOrder.push_back(g2.getOrder()[i]); 
      track.insert(g2.getOrder()[i]);
    }
  }
  return(TSPGenome(newOrder)); // create a new TSPGenome object.
}

bool isShorterPath(const TSPGenome& g1, const TSPGenome& g2) {
  if (g1.getCircuitLength() < g2.getCircuitLength()) return true;
  return false;
}

/*  1. Generate initial population of random genomes. 
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
    std::sort(population.begin(), population.end(), isShorterPath);
    if (gen % 10 == 0) {
        std::cout<<"\nGeneration " << gen 
        << ": shortest path: "<<population[0].getCircuitLength()<<std::endl;
    }
    // keepPopulation specifies how many individuals to keep from the existing population
    // we have to replace the remaining members with new genomes produced from the fittest ones.
    for (int i = keepPopulation; i < populationSize; i++) {
      std::size_t g1 = rand() % (keepPopulation);
      std::size_t g2 = rand() % (keepPopulation);
      
      if (keepPopulation > 1) {
        while (g1 == g2) {   //-loop as long as the 2nd value == 1st value.
          g2 = rand() % (keepPopulation);
        }
      }
      // generate new genomes into the existing population, overwriting the existing members. 
      population[i] = crosslink(population[g1], population[g1]);
    }
    /* mutation: numMutations specifies how many mutations to apply to the population. */
    for (int i = 0; i < numMutations; i++) {
      population[1+rand() % (populationSize-1)].mutate();
    }
  }
  //std::sort(population.begin(), population.end(), isShorterPath);
  return population[0];
}
