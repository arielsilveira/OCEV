#include "GA.hpp"
#include <time.h>       /* time */

int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

    vector<Individual *> population;
    
    population = read_file(argv[1]);

    fitness(population);

    // print_individuals(population);

    // print_solutions(population);

    print_best_worse(population);

    cout << endl << endl;

    double T = 0.0;
    vector<double> fit_relativo(population.size(), 0.0);

    for(int i = 0; i < population.size(); i++){
        cout << "T = " << T << endl;
        T += population[i] -> solution;
        
    }

    for(int i = 0; i < population.size(); i++){
        fit_relativo[i] =  ((population[i] -> solution)/T) * 100;
        cout << "Indivíduo "<< i <<"  = " << fit_relativo[i] << endl;
    }

    srand (time(NULL));

    vector<int> select(population.size(), 0);

    for(int i = 0; i < population.size(); i++){
        int dist = [0, 101](int min, int max) -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(min, max);

                return g_dist(g_e);
            };
        double qnt = 0.0;

        for(int j = 0; j < population.size(); j++){
            qnt +=  fit_relativo[j] ;

            if(qnt > r){
                cout << "r = " << r << endl;
                cout << "qnt = " << qnt << endl;
                select[i] = j;
                
                --fit_relativo[j];
                
                if(fit_relativo[j] < 0){
                    fit_relativo[j] = 0;
                }
                cout << "Indivíduo " << j << " escolhido" << endl;
                break;
            }
        }

    }



    cout << "OK" << endl;

    return 0;
}