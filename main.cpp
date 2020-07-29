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
    int index = -1;

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
    string title; 
    string arq = argv[1];
    if(arq == "arq_nqueen"){
        title = "NQueens";
    }else if(arq == "arq_funcAlgebrica"){
        title = "Função Algébrica";
    }else if(arq == "arq_Radios"){
        title = "Radios";
    }

/*
auto start = high_resolution_clock::now(); 
auto stop = high_resolution_clock::now(); 
auto duration = duration_cast<microseconds>(stop - start); 
*/

    GA *ga;
    ga = read_file(argv[1]);
    vector<int> best_solution(ga->gene_size);
    double best_val = 0;
    
    for(int i = 0; i < ga -> num_execucao; i++){
        cerr << "Iteração: " << i << endl;
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

            for (int l = 0; l < ga -> population_size; l++){
                if(ga -> population[l].solution > best_val){
                    best_val = ga -> population[l].solution;
                    best_solution = ga -> population[l].chromossomo;
                }
            }

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
        
        for(int i = 0; i < ga -> num_execucao; i++){
            soma_melhor += ga -> melhor[i][j];
            soma_media += ga -> media[i][j];
            soma_pior += ga -> pior[i][j];
        }

        saida_melhor << soma_melhor/ga -> num_execucao << endl;
        saida_media << soma_media/ga -> num_execucao << endl;
        saida_pior << soma_pior/ga -> num_execucao << endl;
    }
    


    ofstream config;
    config.open("config.txt");

    config << "PROBLEM=" << title << endl;
    config << "BEST=";
    for(int i = 0; i < best_solution.size(); i++){
        config << " " << best_solution[i];
    }
    config << endl;
    config << "Objective Function=";

    if(arq == "arq_nqueen"){
        auto lambda_nqueens = [](vector<int> best_solution) -> int{
            int collision = 0;

            for(int j = 0; j < best_solution.size(); j++){
                int ok = 1;
                for(int k = 0; k < best_solution.size(); k++){
                    if (j == k ) continue;
                    if(abs(best_solution[j] - best_solution[k]) == abs(j - k)){
                        ok = 0;
                        break;
                    }

                }
        
            if(!ok) collision++;
            }

            return (best_solution.size() * (best_solution.size() - collision));
        };
        
        config << lambda_nqueens(best_solution) << endl;

    }else if(arq == "arq_Radios"){
        int st, lt;
        auto lambda_radios = [&](vector<int> best_solution) -> int{
            int collision = 0;
            auto to_dec = [&](int start, int qnt) -> int {
                int res = 0;
                for(int i = start; i < start + qnt; i++){
                    res += best_solution[i] * pow(2, i - start);
                }
                return res;
            };


            auto mapa = [](int valor, int minimo, int maximo) -> int {
                double res = minimo + ((maximo - minimo) / (double) ((1 << 5) - 1)) * valor;
                return std::round(res);
            };
            st = int(mapa(to_dec(0,5),0,24));
            lt = int(mapa(to_dec(5,5),0,16));
            return 30*mapa(to_dec(0,5), 0, 24) + 40*mapa(to_dec(5,5), 0, 16);

        };
        
        config << lambda_radios(best_solution) << endl;
        config << "Standard=" << st << endl;
        config << "Luxuosos=" << lt << endl;

    }else if(arq == "arq_funcAlgebrica"){
        auto lambda_funcao = [](vector<int> best_solution) -> double{
            auto to_dec = [&](int start, int qnt) -> int {
                int res = 0;
                for(int i = start; i < qnt; i++){
                    res += best_solution[i] * pow(2, i);
                }
                return res;
            };

            auto mapa = [](int valor, int minimo, int maximo) -> double {
                double res = minimo + ((maximo - minimo) / (double) ((1 << 16) - 1)) * valor;
                return res;
            };

            int dec = to_dec(0, best_solution.size());

            double x = mapa(dec, -2, 2);

            return cos(20*x) - (abs(x)/2.0) + (pow(x, 3)/4.0);
        };
                
        config << lambda_funcao(best_solution) << endl;
    }
            
            config << "Fitness Function=" << best_val << endl;
            return 0;
        }