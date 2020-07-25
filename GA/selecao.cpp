#include "GA.hpp"

void GA::selecao(){
    if(this -> selection_type == "ROLETA"){
        selecao_roleta_sem_reposicao();

    }else if(selection_type == "TORNEIO"){
        selecao_torneio();

    }else if(selection_type == "VIZINHANCA"){
        selecao_vizinhanca();

    }
}

void GA::selecao_roleta_sem_reposicao(){

    double T = 0.0;
    vector<double> fit_relativo(population.size(), 0.0);

    for(int i = 0; i < population.size(); i++){
        T += population[i] -> solution;
    }

    auto dist_double = [](int min, int max) -> double {               //funcao lambda, retorna double qlqr
                            random_device g_rd;
                            mt19937 g_e(g_rd());
                            uniform_real_distribution<> g_dist(min, max);

                            return g_dist(g_e);
    };

    for(int i = 0; i < population.size(); i++){
        fit_relativo[i] =  ((population[i] -> solution)/T);
    }
    
    int ant = -1;
    for(int i = 0; i < population.size(); i++){
        double qnt, rnd;

        do{
            qnt = 0.0;
            rnd = dist_double(0, 1);
        
            for(int j = 0; j < population.size(); j++){
                if(ant != j){
                    qnt +=  fit_relativo[j];
                }

                if(qnt > rnd){
                    select[i] = j;
                    ant = j;
                    break;

                }
            }

        }while(qnt < rnd);

    }

}

void GA::selecao_torneio(){

    double T = 0.0;
    // double K = 0.8;
    vector<double> fit_relativo(population.size(), 0.0);

    for(int i = 0; i < population.size(); i++){
        T += population[i] -> solution;
    }

    auto dist_int = [](int min, int max) -> int {           //funcao lambda, retorna inteiro (0,1)
                        random_device g_rd;
                        mt19937 g_e(g_rd());
                        uniform_int_distribution<> g_dist(min, max);

                        return g_dist(g_e);
    };

    for(int i = 0; i < population.size(); i++){
        fit_relativo[i] =  ((population[i] -> solution)/T);
    }

    auto dist_double = [](int min, int max) -> double {               //funcao lambda, retorna double qlqr
                        random_device g_rd;
                        mt19937 g_e(g_rd());
                        uniform_real_distribution<> g_dist(min, max);

                        return g_dist(g_e);
    };
    
    

    for(int i = 0; i < population.size(); i++){
        int individuo1 = dist_int(0, population.size()-1);        //melhor
        int individuo2 = dist_int(0, population.size()-1);        //pior

        if(population[individuo2]->solution > population[individuo1]->solution){
            int aux;
            aux = individuo1;
            individuo1 = individuo2;
            individuo2 = aux;
        }

        if( k >= dist_double(0,1) ){
            select[i] = individuo1;
        }else{
            select[i] = individuo2;
        }

    }
}

void GA::selecao_vizinhanca(){

    double T = 0.0;
    vector<double> fit_relativo(population.size(), 0.0);

    for(int i = 0; i < population.size(); i++){
        T += population[i] -> solution;
        
    }

    for(int i = 0; i < population.size(); i++){
        fit_relativo[i] =  ((population[i] -> solution)/T);
    }

    auto dist_double = [](int min, int max) -> double {               //funcao lambda, retorna double qlqr
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

    // int vizinhanca_tam = 0;

    auto melhor = [&](int init, int end) -> int {
        int best = init;
        for(int i = init+1; i < end; i++){
            if(population[i] -> solution > population[best] -> solution){
                best = i;
            }
        }
        return best;
    };

    auto random = [&](int init, int end) -> int {
        return dist_int(init, end);
    };

    auto fit_prop = [&](int init, int end, int indice) -> int {
        int best = init;
        double qnt, rnd;
        qnt = rnd = 0.0;
        
        do{
            qnt = 0.0;
            rnd = dist_double(0, 1);
        
            for(int j = init+1; j <= end; j++){
                qnt +=  fit_relativo[j];

                if(qnt > rnd && j != indice){
                    best = j;
                    break;
                }
            }

        }while(qnt < rnd);

        return best;
    };

    for(int i = 0; i < population_size; i++){
        int init = population_size - v;
        int end = population_size + v;
        
        if(init < 0) init = 0;
        
        if(end > population_size) end = population_size;

        if(criterio == "MELHOR"){
            select[i] = melhor(init, end);
        }
        
        if(criterio == "PROPORCINAL"){
            select[i] = fit_prop(init, end, i);
        }

        if(criterio == "RANDOM"){
            select[i] = random(init, end);
        }
        
    }

}
