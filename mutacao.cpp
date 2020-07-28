#include "GA/GA.hpp"
#include <omp.h>

void mutacao_swap(GA* &ga){
    if(ga -> gene_type != "INT-PERM") exit(1);

    auto dist_real = [](int min, int max) -> double {
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_real_distribution<> g_dist(min, max);
    
        return g_dist(g_e);
    };

    auto dist_int = [](int min, int max) -> int {
        random_device g_rd; 
        mt19937 g_e(g_rd());
        uniform_int_distribution<> g_dist(min, max);

        return g_dist(g_e);
    };
    
    #pragma omp parallel for
    for(int i = 0; i < ga -> population_size; i++){


        for(int j = 0; j < ga -> gene_size; j++){
            double rnd = dist_real(0, 1);

            if(rnd <= ga->mutation_probability){
                int pos = 0;

                do{
                    pos = dist_int(0, ga->gene_size-1);
                }while(j == pos);

                swap(ga -> population[i].chromossomo[j], ga -> population[i].chromossomo[pos]);

            }
        }

    }

}