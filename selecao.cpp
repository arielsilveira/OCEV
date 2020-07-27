#include "GA/GA.hpp"


void selecao_torneio(GA* &ga){

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

    vector<int> selecao(ga -> population_size, 0);

    
    for(int i = 0; i < ga -> population_size; i++){
        int i1 = 0;
        int i2 = 0;
        
        do{
            i1 = dist_int(0, ga -> population_size -1);
            i2 = dist_int(0, ga -> population_size -1);
        }while(i1 == i2);   

        if(ga -> population[i2].solution > ga -> population[i1].solution){
            int aux = i1;
            i1 = i2;
            i2 = aux;
        }

        double kp = dist_real(0,1);
        
        if(kp <= ga -> k){
            selecao[i] = i1;
        }else{
            selecao[i] = i2;
        }

    }

    int p = ga -> population_size;
    vector<Individual<int>> aux(p);
    aux = ga -> population;
    for(int i = 0; i < ga -> population_size; i++){
        ga -> population[i] = aux[selecao[i]];
    }

    // for(int i = 0; i < ga -> population_size; i++){
    //     cout << "Indivíduo " << selecao[i] << ": ";
    //     ga -> population[i].print_individual();
    //     cout << endl;
    // }


}

