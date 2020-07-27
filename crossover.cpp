#include "GA/GA.hpp"

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
    int corte_init = 0;
    int corte_end = 0;


    vector<vector<int>> new_gene(ga->population_size);
    rnd = dist_real(0,1);

    if(ga -> crossover_probability >= rnd){
        for(int i = 0; i < ga -> population_size; i+=2){
            corte_init = dist_int(1, ga -> gene_size-3);
            corte_end = dist_int(corte_init + 1, ga -> gene_size-1);

            map<int, int> map_1_to_2;
            map<int, int> map_2_to_1;
            for(int j = corte_init; j < corte_end; j++){

                int f1 = ga -> population[i].chromossomo[j];
                int f2 = ga -> population[i+1].chromossomo[j];
                
                ga -> population[i].chromossomo[j] = f2;
                ga -> population[i+1].chromossomo[j] = f1;
                map_1_to_2[f1] = f2;
                map_2_to_1[f2] = f1;
            }
            
            for(int j = 0; j < ga -> gene_size; j++){
            
                if(j < corte_init || j >= corte_end){
                    
                    int f1 = ga -> population[i].chromossomo[j];
                    int f2 = ga -> population[i+1].chromossomo[j];

                    if(map_2_to_1.count(f1) > 0){
                        int val = map_2_to_1[f1];

                        while(map_2_to_1.count(val) > 0 && val != f1){
                            
                            val = map_2_to_1[val];

                        }
                        new_gene[i].push_back(val);
                    
                    }else{
                        new_gene[i].push_back(f1);
                    }

                    if(map_1_to_2.count(f2) > 0){

                        int val = map_1_to_2[f2];
                        

                        while(map_1_to_2.count(val) > 0 && val != f2){
                            
                            val = map_1_to_2[val];

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
            
        }
    }


    for(int i = 0; i < new_gene.size(); i++){
        for(int j = 0; j < new_gene[i].size(); j++){

            ga -> population[i].chromossomo[j] = new_gene[i][j];

        }

    }

}