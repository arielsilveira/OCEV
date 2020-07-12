#include "../GA.hpp"

void fitness(vector<Individual *> population){
    int collision = 0, total = 0;
    int max_individual = population[0] -> individual;
    int max_chromossomo = population[0] -> max_chromossomo;

    for(int i = 0; i < max_individual; i++){
        collision = 0;

        for(int k = 0; k < max_individual; k++){

            if(i != k){
                if(abs(population[i] -> chromossomo[i] - population[i] -> chromossomo[k]) == abs(i - k)){
                    collision++;
                }
            }

        }

        population[i] -> solution = (max_chromossomo * (max_chromossomo - collision - 1));

    }

}