#include "GA.hpp"

void selecao(vector<Individual *> population, vector<int> &select){
    double T = 0.0;
    vector<double> fit_relativo(population.size(), 0.0);
    
    double K = 0.8;

    for(int i = 0; i < population.size(); i++){
        T += population[i] -> solution;
        
    }

    for(int i = 0; i < population.size(); i++){
        fit_relativo[i] =  ((population[i] -> solution)/T) * 100;
    }
        
    
    auto dist = [](int min, int max) -> double {               //funcao lambda, retorna double qlqr
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_real_distribution<> g_dist(min, max);

                return g_dist(g_e);
    };

    auto dist_int = [](int min, int max) -> int {           //funcao lambda, retorna inteiro (0,1)
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(min, max);

                return g_dist(g_e);
    };

    // Seleção: Torneio estocastico
    for(int i = 0; i < population.size(); i++){
        int individuo1 = dist_int(0, population.size()-1);        //melhor
        int individuo2 = dist_int(0, population.size()-1);        //pior

        if(population[individuo2]->solution > population[individuo1]->solution){
            int aux;
            aux = individuo1;
            individuo1 = individuo2;
            individuo2 = aux;
        }

        if( K >= dist(0,1) ){
            select[i] = individuo1;
        }else{
            select[i] = individuo2;
        }

        // cout << "Individuo: " << select[i] << endl;
    }

    // return select;
}