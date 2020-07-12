#include "GA.hpp"

int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

    vector<Individual *> population;
    
    population = read_file(argv[1]);
    // vector<int> solutions;
    
    
    // vector<T> solutions(population[0] -> individual, 0);

    fitness(population);

    print_individuals(population);

    print_solutions(population);

    print_best_worse(population);

    cout << "OK" << endl;

    return 0;
}