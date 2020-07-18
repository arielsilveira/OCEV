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

    //Seleção: roleta sem reposição
    // for(int i = 0; i < population.size(); i++){
    //     int dist = [0, 101](int min, int max) -> int {
    //             random_device g_rd;
    //             mt19937 g_e(g_rd());
    //             uniform_int_distribution<> g_dist(min, max);

    //             return g_dist(g_e);
    //         };
    //     double qnt = 0.0;

    //     for(int j = 0; j < population.size(); j++){
    //         qnt +=  fit_relativo[j] ;

    //         if(qnt > r){
    //             cout << "r = " << r << endl;
    //             cout << "qnt = " << qnt << endl;
    //             select[i] = j;
                
    //             --fit_relativo[j];
                
    //             if(fit_relativo[j] < 0){
    //                 fit_relativo[j] = 0;
    //             }
    //             cout << "Indivíduo " << j << " escolhido" << endl;
    //             break;
    //         }
    //     }

    // }

    //Seleção: Torneio estocastico
    double K = 0.8;
    
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

        cout << "Individuo: " << select[i] << endl;
    }

    



    cout << "OK" << endl;

    return 0;
}