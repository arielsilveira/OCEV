#include "GA.hpp"
#include <map>

void GA::

void GA::one_point(){
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

    double rnd = 0.0;
    int corte = 0;
    vector<Individual *> new_population(population_size, 0);

    new_population = population;

    for(int i = 0; i < population_size; i++){
        new_population[i] = population[select[i]];

    }

    // paralelo
    for(int i = 0; i < population_size; i+=2){
        if(i+1 < population_size){
            rnd = dist_real(0, 1);
         
            if(rnd < crossover_probability ){
                corte = dist_int(1, gene_size-2);
                troca_genetica_corte(i, i+1, corte, gene_size, new_population);
            }
        }
    }

    population = new_population;
}


void GA::two_point(){

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

    double rnd = 0.0;
    int corte_init = 0;
    int corte_end = 0;
    vector<Individual *> new_population(population_size, 0);
    new_population = population;


    for(int i = 0; i < population_size; i++){
        new_population[i] = population[select[i]];

    }


    // paralelo
    for(int i = 0; i < population_size; i+=2){
        if(i+1 < population_size){
            rnd = dist_real(0, 1);
         
            if(rnd < crossover_probability ){
                corte_init = dist_int(1, gene_size-3);
                corte_end = dist_int(corte_init+1, gene_size-1);
                troca_genetica_corte(i, i+1, corte_init, corte_end, new_population);
            }
        }
    }

    population = new_population;
}

void GA::uniform(){
    
    auto dist_real = [](int min, int max) -> double {
            random_device g_rd;
            mt19937 g_e(g_rd());
            uniform_real_distribution<> g_dist(min, max);
        
            return g_dist(g_e);
    };

    double rnd = 0.0;
    vector<Individual *> new_population(population_size, 0);
    new_population = population;


    for(int i = 0; i < population_size; i++){
        new_population[i] = population[select[i]];

    }

    for(int i = 0; i < population_size; i+=2){
        for(int j = 0; j < gene_size; j++){
            double rnd = dist_real(0, 1);
            if(rnd <= 0.5){
                int f1 = new_population[i] -> chromossomo[j];
                int f2 = new_population[i+1] -> chromossomo[j];
                new_population[i] -> chromossomo[j] = f2;
                new_population[i+1] -> chromossomo[j] = f1;

            }
        }
    }

    population = new_population;

}

void GA::

void GA::blx_a(){
    if(gene_type == "REAL"){
        // tentar entender
    }else{
        cout << "Função inapropriada para o cálculo de crossover. "<< endl;
        exit(1);
    }
}

void GA::arithmetic(){
    if(gene_type == "REAL"){

        auto dist_real = [](int min, int max) -> double {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_real_distribution<> g_dist(min, max);
            
                return g_dist(g_e);
        };

        vector<Individual *> new_population(population_size, 0);
        new_population = population;


        for(int i = 0; i < population_size; i++){
            new_population[i] = population[select[i]];

        }

        for(int i = 0; i < population_size; i+=2){
            int a = dist_real(0, 1);

            for(int j = 0; j < gene_size; j++){
                new_population[i] -> chromossomo[j] = a*population[i]->chromossomo[j] + (1-a)*population[i+1]->chromossomo[j];
                new_population[i+1] -> chromossomo[j] = (1-a)*population[i]->chromossomo[j] + a*population[i+1]->chromossomo[j];
            }


        }

        population = new_population;

    }else{
        cout << "Função inapropriada para o cálculo de crossover. "<< endl;
        exit(1);
    }
}


void GA::troca_genetica_corte(int p1, int p2, int corte_init, int corte_end, vector<Individual *> &new_population){
    // paralelo
    for(int i = 0; i < gene_size; i++){
        if(i >= corte_init && i <= corte_end){
            int f1 = new_population[p1] -> chromossomo[i];
            int f2 = new_population[p2] -> chromossomo[i];
            new_population[p1] -> chromossomo[i] = f2;
            new_population[p2] -> chromossomo[i] = f1;

        }
    }

}