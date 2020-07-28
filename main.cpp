#include "GA/GA.hpp"
#include <chrono> 
using namespace std::chrono; 

int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

    GA *ga;
    ga = read_file(argv[1]);
    for(int i = 0; i < 10; i++){
        cerr << "Onde é que eu to? " << i << endl;
        ga -> start_generation();

        ga -> melhor.push_back(vector<double>());
        ga -> media.push_back(vector<double>());
        ga -> pior.push_back(vector<double>());
        for(int j = 0; j < ga -> generation; j++){
            auto start = high_resolution_clock::now(); 
            fitness(ga);
            auto stop = high_resolution_clock::now(); 

            auto duration = duration_cast<microseconds>(stop - start); 
            // cout << "Duração do fitness: "  << duration.count() << endl;

            start = high_resolution_clock::now(); 
            selecao_torneio(ga);
            
            stop = high_resolution_clock::now(); 

            duration = duration_cast<microseconds>(stop - start); 
            // cout << "Duração do seleção: "  << duration.count() << endl;

            start = high_resolution_clock::now(); 
            crossover_PMX(ga);

            stop = high_resolution_clock::now(); 

            duration = duration_cast<microseconds>(stop - start); 
            // cout << "Duração do crossover: "  << duration.count() << endl;
            
            start = high_resolution_clock::now(); 
            mutacao_swap(ga);

            stop = high_resolution_clock::now(); 

            duration = duration_cast<microseconds>(stop - start); 
            // cout << "Duração do mutação: "  << duration.count() << endl;
            
            start = high_resolution_clock::now(); 
            final_result(ga, i);

            stop = high_resolution_clock::now(); 

            duration = duration_cast<microseconds>(stop - start); 
            // cout << "Duração do result: "  << duration.count() << endl;
        // break;
        }   
        ga -> population.clear();
    }

    // cout << ga -> population.size();

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
    

    // cout << "OK" << endl;

    return 0;
}