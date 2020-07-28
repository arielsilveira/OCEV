#include "../GA/GA.hpp"

void fitness(GA* &ga){
    double collision = 0;
    int max_individual = ga -> population_size;
    int max_chromossomo = ga -> gene_size;

    
    for(int i = 0; i < max_individual; i++){

        collision = 0;
        for(int j = 0; j < max_chromossomo; j++){
            int ok = 1;
            for(int k = 0; k < max_chromossomo; k++){
                if (j == k ) continue;
                if(abs(ga -> population[i].chromossomo[j] - ga -> population[i].chromossomo[k]) == abs(j - k)){
                    ok = 0;
                }

            }

            if(!ok) collision++;

        }

        ga -> population[i].solution = (max_chromossomo * (max_chromossomo - collision))/(double)(pow(max_chromossomo, 2));
    }

}