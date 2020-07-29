#include "GA/GA.hpp"
#include <chrono> 
#include <omp.h>
using namespace std::chrono; 

Individual<int> melhor(GA* &ga){
    double best_solution = 0;
    Individual<int> best;

    for(int i = 0; i < ga -> population_size; i++){
        if(ga -> population[i].solution > best_solution){
            best_solution = ga -> population[i].solution;
            best = ga -> population[i];
        }
    }

    return best;
}

void swap_worse(GA* &ga, Individual<int> best){
    double worse = 10;
    int index = 0;

    for(int i = 0; i < ga -> population_size; i++){
        if(ga -> population[i].solution < worse){
            index = i;
            worse = ga -> population[i].solution;
        }
    }

    ga -> population[index] = best;

}

int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

/*
auto start = high_resolution_clock::now(); 
auto stop = high_resolution_clock::now(); 
auto duration = duration_cast<microseconds>(stop - start); 
*/

    GA *ga;
    ga = read_file(argv[1]);

    for(int i = 0; i < 10; i++){
        cerr << "Onde é que eu to? " << i << endl;
        ga -> start_generation();

        ga -> melhor.push_back(vector<double>());
        ga -> media.push_back(vector<double>());
        ga -> pior.push_back(vector<double>());
        for(int j = 0; j < ga -> generation; j++){
            Individual<int> best;

            fitness(ga);

            if(ga -> elitismo){
                best = melhor(ga);
            }            

            selecao_menu(ga);
            
            crossover_menu(ga);


            mutacao_menu(ga);


            if(ga -> elitismo){
                swap_worse(ga, best);
            }

            final_result(ga, i);

        }   
        ga -> population.clear();
    }


    ofstream saida_melhor;
    saida_melhor.open("melhor.txt");

    ofstream saida_media;
    saida_media.open("media.txt");
    
    ofstream saida_pior;
    saida_pior.open("pior.txt");
    

    for(int j = 0; j < ga -> generation; j++){
        double soma_melhor = 0.0;
        double soma_media = 0.0;
        double soma_pior = 0.0;
        for(int i = 0; i < 10; i++){
            soma_melhor += ga->melhor[i][j];
            soma_media += ga->media[i][j];
            soma_pior += ga->pior[i][j];
        }
        saida_melhor << soma_melhor/10 << endl;
        saida_media << soma_media/10 << endl;
        saida_pior << soma_pior/10 << endl;
    }
    


    return 0;
}