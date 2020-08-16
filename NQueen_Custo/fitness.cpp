#include "../GA/GA.hpp"

void fitness(GA* &ga){
// Mesma coisa da nqueen
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

        double maxi_Value = [&](){
            int tam = ga -> gene_size;
            double tot = 0;
            for(int i = 0; i < tam; i++){
                tot += sqrt((tam-2) * tam + i + 1);
            }
            return tot;
        }();

        double val = 0;
        for(int j = 0; j < ga -> gene_size; j++){
            int pos = (j * ga -> gene_size) + ga -> population[i].chromossomo[j] + 1;
            val += (j % 2 == 0 ) ? sqrt(pos) : log10(pos);
        }

        double val_pos = val/maxi_Value;
        double val_nqueen = (max_chromossomo * (max_chromossomo - collision))/(double)(pow(max_chromossomo, 2));
        ga -> population[i].solution = (val_pos + val_nqueen)/2.0;
        
        ga -> population[i].collision = collision;
        ga -> population[i].FO = val + (max_chromossomo * (max_chromossomo - collision));
    }
}