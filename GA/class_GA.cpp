#include "GA.hpp"

GA::GA(int generation, int population_size, int gene_size, double crossover_probability, double mutation_probability, string gene_type, string crossover_type, string mutation_type, string selection_type, int min, int max, int k, int v, string criterio){

    this -> generation = generation; 
    this -> population_size = population_size;
    this -> gene_size = gene_size;
    this -> crossover_probability = crossover_probability;
    this -> mutation_probability;
    this -> gene_type = gene_type;
    this -> crossover_type = crossover_type;
    this -> mutation_type = mutation_type;
    this -> selection_type = selection_type;
    this -> min = min;
    this -> max = max;
    this -> v = v;
    this -> k = k;
    this -> criterio = criterio;

    vector<int> aux(population_size, 0);
    select = aux;

    for(int i = 0; i < population_size; i++){
        this -> population.push_back(new Individual(gene_type, gene_size, min, max));
    }

}

void GA::print_select(){
    for(int i = 0; i < population_size; i++){
        cout << "Indivíduo " << select[i] << ": " << population[select[i]] -> solution << endl;
    }
}