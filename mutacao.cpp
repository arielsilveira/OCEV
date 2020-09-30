#include "GA/GA.hpp"
#include <omp.h>

void mutacao_menu(GA* &ga){
    if(ga -> mutation_type == "SWAP_MUTATION"){
        mutacao_swap(ga);
    }else if(ga -> mutation_type == "BITFLIP"){
        mutacao_bitflip(ga);
    }else if(ga -> mutation_type == "RANDOM"){
        mutation_random(ga);
    }
}

void mutacao_swap(GA* &ga){
    // if(ga -> gene_type != "INT-PERM") exit(1);

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

            if(rnd <= ga -> mutation_probability){
                int pos = 0;

                do{
                    pos = dist_int(0, ga->gene_size-1);
                }while(j == pos);

                swap(ga -> population[i].chromossomo[j], ga -> population[i].chromossomo[pos]);

            }
        }

    }

}


void mutacao_bitflip(GA* &ga){
    if(ga -> gene_type != "BINARY") exit(1);


    auto dist_real = [](int min, int max) -> double {
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_real_distribution<> g_dist(min, max);
    
        return g_dist(g_e);
    };

    #pragma omp parallel for
    for(int i = 0; i < ga -> population_size; i++){
        for(int j = 0; j < ga -> gene_size; j++){
            double rnd = dist_real(0, 1);
            
            if(rnd <= ga -> mutation_probability){
                ga -> population[i].chromossomo[j] = !ga -> population[i].chromossomo[j];
            }

        }

    }
}

void mutation_random(GA* &ga){
    double dom_min = ga -> min;
    double dom_max = ga -> max;


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

    for(int i = 0; i < ga -> population_size; i++){
        for(int j = 0; j < ga -> gene_size; j++){
            double rnd = dist_real(0,1);

            if(rnd <= ga -> mutation_probability){
                if(ga -> gene_type == "REAL") ga -> population[i].chromossomo[j] = dist_real(dom_min, dom_max);
                if(ga -> gene_type == "INT") ga -> population[i].chromossomo[j] = dist_int(dom_min, dom_max);
                
            }
        }

    }

}