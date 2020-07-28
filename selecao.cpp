#include "GA/GA.hpp"

void selecao_menu(GA* &ga){
    if(ga->selection_type == "roleta"){
        selecao_roleta(ga);
    }else if(ga->selection_type == "torneio"){
        selecao_torneio(ga);
    }else if(ga->selection_type == "vizinhanca"){
        //selecao_vizinhanca(ga);
    }else{
        exit(1); 
    }
}

// ------------------------------------------------------- //

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

// ------------------------------------------------------- //

void selecao_roleta(GA* &ga){
    double T;
    vector<double> result(ga->population_size);
    int old_individuo = -1;
    vector<int> new_individuo(ga->population_size);
    vector<Individual<int>> old_populacao(ga->population_size); 

    auto dist_double = [](int min, int max) -> double {               //funcao lambda, retorna double qlqr
                            random_device g_rd;
                            mt19937 g_e(g_rd());
                            uniform_real_distribution<> g_dist(min, max);

                            return g_dist(g_e);
    };
    
    for(int i = 0; i < ga->population_size; i++){       //T = Tamnaho total das soluções 
        T += ga->population[i].solution;
    }

    for(int i = 0; i < ga->population_size; i++){       //result = cada posicao contem o fitness relativo de cada indivuo 
        result[i] = ga->population[i].solution / T;
    }

    for(int i = 0; i < ga->population_size; i++){       //roleta 
        double incremento;
        double auxiliar_random;

        do{
            incremento = 0.0;
            auxiliar_random = dist_double(0, 1);
            
            for(int j = 0; j < ga->population_size; j++){
                if(old_individuo != j){
                    incremento += result[j];
                }
                if(incremento > auxiliar_random){
                    new_individuo[i] = j; 
                    old_individuo = j; 
                    break;
                }
            }
        }while(incremento < auxiliar_random);
    }

    old_populacao = ga->population;

    for(int i = 0; i < ga->population_size; i++){                   //guarda os individuos selecionados na roleta
        ga->population[i] = old_populacao[new_individuo[i]];
    }

}

// ------------------------------------------------------- //

// void selecao_vizinhanca(GA* &ga){

// }