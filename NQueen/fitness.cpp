#include "../GA.hpp"

void fitness(GA ga){
    int collision = 0, total = 0;
    int max_individual = ga.population_size;
    int max_chromossomo = ga.gene_size;

    for(int i = 0; i < max_individual; i++){
        collision = 0;

        for(int k = 0; k < max_individual; k++){

            if(i != k){
                if(abs(ga.population[i] -> chromossomo[i] - ga.population[i] -> chromossomo[k]) == abs(i - k)){
                    collision++;
                }
            }

        }

        ga.population[i] -> solution = (max_chromossomo * (max_chromossomo - collision - 1))/(pow(max_chromossomo, 2));
        // cout << ga.population[i] -> solution << endl;
    }

}