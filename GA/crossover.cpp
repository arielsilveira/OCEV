#include "GA.hpp"
#include <map>

void GA::crossover(){
    if(crossover_type == "ONE_POINT"){
        one_point();
    }else if(crossover_type == "TWO_POINT"){
        two_point();
    }else if(crossover_type == "UNIFORM"){
        uniform();
    }else if(crossover_type == "PMX"){
        pmx();
    }else if(crossover_type == "BLX-a"){
        blx_a();
    }else if(crossover_type == "ARITHMETIC"){
        arithmetic();
    }else{
        cout << "Falha na operação do crossover" << endl;
        exit(1);
    }
}

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

void GA::pmx(){

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

        corte_init = dist_int(1, gene_size-3);
        corte_end = dist_int(corte_init+1, gene_size-1);
        map<int, int> map_1_to_2;
        map<int, int> map_2_to_1;

        for(int j = corte_init; j <= corte_end; j++){

            int f1 = new_population[i] -> chromossomo[j];
            int f2 = new_population[i+1] -> chromossomo[j];
            map_1_to_2.insert(pair<int, int> (f1, f2));
            map_2_to_1.insert(pair<int, int> (f2, f1));
        }

        cout << "Corte inicio: " << corte_init << endl;
        cout << "Corte fim: " << corte_end << endl;

        for (map<int,int>::iterator it=map_1_to_2.begin(); it!=map_1_to_2.end(); ++it)
            cout << it->first << " => " << it->second << " --- ";


        for (map<int,int>::iterator it=map_2_to_1.begin(); it!=map_2_to_1.end(); ++it)
            cout << it->first << " => " << it->second << " --- ";
        
        cout << endl << "i = " << i << endl;
        
        for(int j = 0; j < gene_size; j++){
            int f1 = new_population[i] -> chromossomo[j];
            int f2 = new_population[i+1] -> chromossomo[j];

            cout << "Valor antes: " << f1 << endl;
            cout << "Valor depois: " << map_2_to_1[f1] << endl;
            
            if(map_2_to_1.count(f1) > 0){
                new_population[i] -> chromossomo[j] = map_2_to_1[f1];
            }else{
                new_population[i] -> chromossomo[j] = f1;
            }

            if(map_1_to_2.count(f2) > 0){
                new_population[i+1] -> chromossomo[j] = map_1_to_2[f2];
            }else{
                new_population[i+1] -> chromossomo[j] = f2;
            }
        }


    }

    population = new_population;

}

void GA::blx_a(){

}

void GA::arithmetic(){

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