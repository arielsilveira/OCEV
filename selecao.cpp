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

bool selecionado(vector<pair<int, double> > v, int x){
    for(int i = 0; i < v.size(); i++){
        if(v[i].first == x){
            return true;
        }
    }
    return false;
}

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
    // cerr << ga -> qnt_selecionado << endl;
    for(int i = 0; i < ga -> population_size; i++){
        vector<pair<int, double> > selecionado_torneio;
        int i1 = 0;
        int i2 = 0;

        for(int j = 0; j < ga -> qnt_selecionado; j++){
            int a;
            do{
                a = dist_int(0, ga -> population_size -1);

            }while(selecionado(selecionado_torneio, a));
            selecionado_torneio.push_back(std::pair<int,double>(a, ga -> population[a].solution));
        }

        // double best = 0;
        // int index_best = -1;
        // double worse = 1;
        // int index_worse = 2;

        sort(selecionado_torneio.begin(), selecionado_torneio.end(), sortbysec);

        // for(int j = 0; j < ga -> qnt_selecionado; j++){
        //     if(ga -> population[selecionado_torneio[i]].solution >= best){
        //         best = ga -> population[selecionado_torneio[i]].solution;
        //         index_best = selecionado_torneio[i];
        //     }

        //     if(ga -> population[selecionado_torneio[i]].solution <= worse){
        //         worse = ga -> population[selecionado_torneio[i]].solution;
        //         index_worse = selecionado_torneio[i];
        //     }
        // }

        double kp = dist_real(0,1);
        
        if(kp <= ga -> k){
            selecao[i] = selecionado_torneio[selecionado_torneio.size() - 1].first;
        }else{
            selecao[i] = selecionado_torneio[0].first;
        }

    }

    int p = ga -> population_size;
    vector<Individual<int>> aux(p);
    aux = ga -> population;
    for(int i = 0; i < ga -> population_size; i++){
        ga -> population[i] = aux[selecao[i]];
    }

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