#include "../GA/GA.hpp"
#include <omp.h>

void fitness(GA* &ga){
    int max_individual = ga -> population_size;
    int max_chromossomo = ga -> gene_size;

    #pragma omp parallel for
    for(int i = 0; i < max_individual; i++){

        double collision = 0;
        for(int j = 0; j < max_chromossomo; j++){
            int ok = 1;
            for(int k = 0; k < max_chromossomo; k++){
                if (j == k ) continue;
                if(abs(ga -> population[i].chromossomo[j] - ga -> population[i].chromossomo[k]) == abs(j - k)){
                    ok = 0;
                    break;
                }

            }

            if(!ok) collision++;

        }

        ga -> population[i].solution = (max_chromossomo * (max_chromossomo - collision))/(double)(pow(max_chromossomo, 2));
        ga -> population[i].FO = (max_chromossomo * (max_chromossomo - collision));
        ga -> population[i].collision = collision;
    }

}