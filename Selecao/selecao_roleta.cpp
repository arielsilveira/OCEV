#include "GA.hpp"

void selecao(vector<Individual *> population, vector<int> &select){
    double T = 0.0;
    vector<double> fit_relativo(population.size(), 0.0);
    // vector<int> select(population.size(), 0);


    for(int i = 0; i < population.size(); i++){
        // cout << "T = " << T << endl;
        T += population[i] -> solution;
        
    }

    for(int i = 0; i < population.size(); i++){
        fit_relativo[i] =  ((population[i] -> solution)/T) * 100;
        // cout << "Indivíduo "<< i <<"  = " << fit_relativo[i] << endl;
    }
        //Seleção: roleta sem reposição
    for(int i = 0; i < population.size(); i++){
        auto dist = [](int min, int max) -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(min, max);

                return g_dist(g_e);
            };
        double qnt = 0.0;

        for(int j = 0; j < population.size(); j++){
            qnt +=  fit_relativo[j] ;

            if(qnt > dist(0,101)){
                select[i] = j;
                
                --fit_relativo[j];
                
                if(fit_relativo[j] < 0){
                    fit_relativo[j] = 0;
                }
                break;
            }
        }

    }

}