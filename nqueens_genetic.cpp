#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <unordered_set>
#include <algorithm>

using namespace std;

// 1) first initialize populations to random values 
// 2) each indiviudal assigned fitness value based on some fitness function
// 3) the ones with highest fitness levels mate randomly
// 4) random mutations in the resulting population 

const int POPULATION_SIZE = 10000; 
const int QUEENS = 30; 

class Individual {
    public:
    int fitness; 
    vector<int> genome;

    Individual() {
        fitness=0; 
    }

    void checkFitness() {
        
        // check if in same row
        unordered_set<int> rows;
        unordered_set<int> hills;
        unordered_set<int> dales; 
        
        int good =-1; 
        for (int i=0; i < genome.size(); i++) {
            if (rows.count(genome[i]) == 0 && hills.count(genome[i] + i) == 0 && dales.count(genome[i] - i) == 0) {
                rows.insert(genome[i]); 
                hills.insert(genome[i] + i); 
                dales.insert(genome[i] - i);
                good++; 
            }
        }
        
        fitness = good; 
        //cout << fitness << endl; 
    }
};

void createPopulation(vector<Individual*> &population) {
    for (int i=0; i < POPULATION_SIZE; i++) {
        Individual* indiv = new Individual(); 
        for (int j=0; j < QUEENS; j++) {
            int random_q = rand() % QUEENS; 
            (*indiv).genome.push_back(random_q);  
        }
        population.push_back(indiv); 
    }
}

Individual* checkPopulationFitness(vector<Individual*> &population) {
    for (int i=0; i < population.size(); i++) {
        population[i] -> checkFitness();
        if (population[i] -> fitness == QUEENS-1) {
            return population[i];
        }
    }
    return NULL;  
}

bool sortPopulation(Individual* &a, Individual* &b) {
    int first = a -> fitness;
    int second = b -> fitness; 
    return first>second;
}

void crossover(Individual* father, Individual* mother, vector<Individual*> &population, int offspring_index) {
    int fracture = rand() % QUEENS;
    int parent = rand() % 2; 
    Individual* parent1 = NULL;
    Individual* parent2  = NULL;

    if (parent == 0) {
        parent1 = father;
        parent2 = mother;
    } 
    else {
        parent1 = mother;
        parent2 = father;
    }

    vector<int> offspring; 

    for (int i=0; i < fracture; i++) {
        offspring.push_back((parent1 -> genome)[i]);
    }
    for (int i=fracture; i < QUEENS; i++) {
        offspring.push_back((parent2 -> genome)[i]);
    }

    // cout << "FRACTURE: " << fracture << endl;  

    // cout << "PARENT1" << endl;
    // for (auto& x : parent1 -> genome) {
    //     cout << x << " ";
    // }
    // cout << endl;
    
    // cout << "PARENT2" << endl;
    // for (auto& x : parent2 -> genome) {
    //     cout << x << " ";
    // }
    //     cout << endl;


    // cout << "OFFSPRING" << endl; 
    // for (auto& x : offspring) {
    //     cout << x << " ";
    // }
    //     cout << endl;

    population[offspring_index] -> genome = offspring; 
    

}

void mutation(vector<Individual*> &population) {
    int mutation = rand() % 2; 

    int index = rand() % POPULATION_SIZE; 
    int gene = rand() % QUEENS; 

    if (mutation == 0) {
        (population[index] -> genome)[gene] = rand() % QUEENS; 
    }
}




int main() {
    srand(time(NULL));
    // Individual test; 
    // vector<int> genome_test = {2,0,2,2}; 
    // test.genome = genome_test; 
    // test.checkFitness(); 

    int sum=0;
    int runs=0;
    
    while(runs < 100) {
        runs++; 
    vector<Individual*> population;
    vector<int> test = {5,4,1,2}; 
    bool found = false;  
    createPopulation(population); 
    int count = 0; 
    while (!found) {
        count++; 
        Individual* optimal = checkPopulationFitness(population); 
        sort(population.begin(),population.end(), sortPopulation); 
        
        if (optimal == NULL) {
            "nothing found";
        }      

        cout << "highest fitness: " << population[0] -> fitness << endl;

        // for (int i=0; i < population.size(); i++) {
        //     cout << "Solution: ";
            
        //     for (auto& x : population[i] -> genome) {
        //         cout << x << " "; 
        //     }
            
        //     cout << "Fitness: ";
        //     cout << population[i] -> fitness << endl; 
        // }


        // if (optimal != NULL) {
        //     cout << "OPTIMAL" << endl;
        //     cout << optimal -> fitness << endl; 
        //     for (auto& x : optimal -> genome) {
        //         cout << x << " ";
        //     }
        //     found=true; 
        // }
        if (optimal != NULL) {
            found=true; 
        }

        for (int i=0; i < POPULATION_SIZE/2; i++) {
            int parent1 = rand() % POPULATION_SIZE/4;
            int parent2 = rand() % POPULATION_SIZE/4;

            while (parent1 != parent2) {
                parent2 = rand() % POPULATION_SIZE/4;
            }

            crossover(population[parent1],population[parent2], population, i); 
        }

        for (int i=0; i < POPULATION_SIZE; i++) {
            mutation(population); 
        }


    } 
    cout << "only took " << count << " tries" << endl; 

    sum += count; 
    }
    cout << "average " << sum/runs; 
    return 0; 
}