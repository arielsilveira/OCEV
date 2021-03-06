#include "GA/GA.hpp"
#include <omp.h>

void crossover_menu(GA* &ga){
    if(ga->crossover_type == "PMX"){
        crossover_PMX(ga);

    }else if(ga->crossover_type == "UM_PONTO"){
        one_point(ga);
    
    }else if(ga->crossover_type == "DOIS_PONTOS"){
        two_point(ga);
    
    }else if(ga->crossover_type == "UNIFORME"){
        uniform(ga);
    
    }else if(ga->crossover_type == "ARITMETICO"){
        arithmetic(ga);
    
    }else{
        exit(1); 
    }
}

// ------------------------------------------------------- //

void crossover_PMX(GA* &ga){
    if(ga -> gene_type != "INT-PERM"){
        cout << "Função inapropriada para o cálculo de crossover" << endl; //exit(1);
        exit(1);  
    } 

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

    rnd = dist_real(0,1);

    if(ga -> crossover_probability >= rnd){

        vector<pair<int, int>> corte(ga -> population_size, pair<int, int>(0,0));
        vector<vector<int>> new_gene(ga->population_size, vector<int>(0));
        
        vector<vector< map<int, int> > > map_1_to_2(ga -> population_size);
        vector<vector< map<int, int> > > map_2_to_1(ga -> population_size);

        #pragma omp parallel for
        for(int i = 0; i < ga -> population_size; i+=2){
            int corte_init = dist_int(1, ga -> gene_size-3);
            int corte_end = dist_int(corte_init + 1, ga -> gene_size-1);

            // corte.push_back(pair<int,int>(corte_init, corte_end));
            map<int, int> mapa1;
            map<int, int> mapa2;
            for(int j = corte[i].first; j < corte[i].second; j++){

                int f1 = ga -> population[i].chromossomo[j];
                int f2 = ga -> population[i+1].chromossomo[j];
                
                ga -> population[i].chromossomo[j] = f2;
                ga -> population[i+1].chromossomo[j] = f1;

                mapa1[f1] = f2;
                mapa2[f2] = f1;

            }

            map_1_to_2[i].push_back(mapa1);
            map_2_to_1[i].push_back(mapa1);
        }

        #pragma omp parallel for
        for(int i = 0; i < ga -> population_size; i+=2){
            // int corte_init = dist_int(1, ga -> gene_size-3);
            // int corte_end = dist_int(corte_init + 1, ga -> gene_size-1);

            // map<int, int> map_1_to_2;
            // map<int, int> map_2_to_1;

            // for(int j = corte_init; j < corte_end; j++){

            //     int f1 = ga -> population[i].chromossomo[j];
            //     int f2 = ga -> population[i+1].chromossomo[j];
                
            //     ga -> population[i].chromossomo[j] = f2;
            //     ga -> population[i+1].chromossomo[j] = f1;

            //     map_1_to_2[f1] = f2;
            //     map_2_to_1[f2] = f1;
            // }
            
            for(int j = 0; j < ga -> gene_size; j++){
            
                if(j < corte[i].first || j >= corte[i].second){
                    
                    int f1 = ga -> population[i].chromossomo[j];
                    int f2 = ga -> population[i+1].chromossomo[j];

                    if(map_2_to_1[i][0].count(f1) > 0){
                        int val = map_2_to_1[i][0][f1];

                        while(map_2_to_1[i][0].count(val) > 0 && val != f1){
                            
                            val = map_2_to_1[i][0][val];

                        }
                        new_gene[i].push_back(val);
                    
                    }else{
                        new_gene[i].push_back(f1);
                    }

                    if(map_1_to_2[i][0].count(f2) > 0){

                        int val = map_1_to_2[i][0][f2];
                        

                        while(map_1_to_2[i][0].count(val) > 0 && val != f2){
                            
                            val = map_1_to_2[i][0][val];

                        }
                        new_gene[i+1].push_back(val);

                    }else{
                        new_gene[i+1].push_back(f2);
                    }

                }else{
                    new_gene[i].push_back(ga -> population[i].chromossomo[j]);
                    new_gene[i+1].push_back(ga -> population[i+1].chromossomo[j]);
                }
            }


            ga -> population[i].chromossomo = new_gene[i];
            ga -> population[i+1].chromossomo = new_gene[i+1];
            
        }
    }


}

// ------------------------------------------------------- //

void one_point(GA* &ga){       
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
    vector<Individual<int>> new_population(ga->population_size); 

    new_population = ga->population; 

    for(int i = 0; i < ga->population_size; i++){
        new_population[i] = ga->population[i];          //guarda os inteiros selecionados
    }

    for(int i = 0; i < ga->population_size; i+=2){
        if(i+1 < ga->population_size){
            rnd = dist_real(0, 1);
         
            if(rnd < ga->crossover_probability ){   
                corte = dist_int(1, ga->gene_size-2);   
                troca_genetica_corte(ga, i, i+1, corte, ga->gene_size, new_population);
            }
        }
    }

    ga->population = new_population;
}

// ------------------------------------------------------- //

void two_point(GA* &ga){

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
    vector<Individual<int>> new_population(ga->population_size);
    new_population = ga->population;

    for(int i = 0; i < ga->population_size; i++){
        new_population[i] = ga->population[i];
    }

    #pragma omp parallel for
    for(int i = 0; i < ga->population_size; i+=2){
        if(i+1 < ga->population_size){
            rnd = dist_real(0, 1);
         
            if(rnd < ga->crossover_probability ){
                corte_init = dist_int(1, ga->gene_size-3);
                corte_end = dist_int(corte_init+1, ga->gene_size-1);
                troca_genetica_corte(ga, i, i+1, corte_init, corte_end, new_population);
            }
        }
    }

    ga->population = new_population;
}

// ------------------------------------------------------- //

void uniform(GA* &ga){
    
    auto dist_real = [](int min, int max) -> double {
            random_device g_rd;
            mt19937 g_e(g_rd());
            uniform_real_distribution<> g_dist(min, max);
        
            return g_dist(g_e);
    };

    double rnd = 0.0;
    vector<Individual<int>> new_population(ga->population_size);
    // new_population = ga->population;

    for(int i = 0; i < ga->population_size; i++){
        new_population[i] = ga->population[i];
    }

    // #pragma omp parallel for
    for(int i = 0; i < ga->population_size; i+=2){
        double rnd = dist_real(0, 1);
        if(rnd <= ga -> crossover_probability){
            for(int j = 0; j < ga->gene_size; j++){
                rnd = dist_real(0, 1);
                if(rnd <= 0.5){
                    int f1 = new_population[i].chromossomo[j];
                    int f2 = new_population[i+1].chromossomo[j];
                    new_population[i].chromossomo[j] = f2;
                    new_population[i+1].chromossomo[j] = f1;
                }
            }
        }
    }

    ga->population = new_population;
}

// ------------------------------------------------------- //

void arithmetic(GA* &ga){
    if(ga->gene_type == "REAL"){

        auto dist_real = [](int min, int max) -> double {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_real_distribution<> g_dist(min, max);
            
                return g_dist(g_e);
        };

        vector<Individual<int>> new_population(ga->population_size);
        new_population = ga->population;

        for(int i = 0; i < ga->population_size; i++){
            new_population[i] = ga->population[i];
        }

        for(int i = 0; i < ga->population_size; i+=2){
            int a = dist_real(0, 1);

            for(int j = 0; j < ga->gene_size; j++){
                new_population[i].chromossomo[j] = a * ga->population[i].chromossomo[j] + (1-a) * ga->population[i+1].chromossomo[j];
                new_population[i+1].chromossomo[j] = (1-a) * ga->population[i].chromossomo[j] + a * ga->population[i+1].chromossomo[j];
            }
        }

        ga->population = new_population;

    }else{
        cout << "Função inapropriada para o cálculo de crossover. "<< endl;
        exit(1);
    }
}

// ------------------------------------------------------- //

//Função auxiliar de corte 
void troca_genetica_corte(GA* &ga, int p1, int p2, int corte_init, int corte_end, vector<Individual<int>> &new_population){
    
    #pragma omp parallel for
    for(int i = 0; i < ga->gene_size; i++){
        if(i >= corte_init && i <= corte_end){
            int f1 = new_population[p1].chromossomo[i];
            int f2 = new_population[p2].chromossomo[i];
            new_population[p1].chromossomo[i] = f2;
            new_population[p2].chromossomo[i] = f1;
        }
    }
}

