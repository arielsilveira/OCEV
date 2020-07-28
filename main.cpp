#include "GA/GA.hpp"



int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

    // double init = 0;
    GA *ga;
    ga = read_file(argv[1]);
    for(int i = 0; i < 10; i++){
        ga -> start_generation();
    // print_individuals(ga);
        ga -> melhor.push_back(vector<double>());
        ga -> media.push_back(vector<double>());
        ga -> pior.push_back(vector<double>());

        for(int j = 0; j < ga -> generation; j++){
            // cout << "Geração " << i << endl;
            fitness(ga);

            selecao_torneio(ga);

            
            crossover_PMX(ga);

            mutacao_swap(ga);
        
            final_result(ga, i);

        }   

        ga -> population.clear();
    }

    cout << ga -> population.size();

    ofstream saida_melhor;
    saida_melhor.open("melhor.txt");

    ofstream saida_media;
    saida_media.open("media.txt");
    
    ofstream saida_pior;
    saida_pior.open("pior.txt");
    


    cout << "MELHOR" << endl << endl;
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
    
    cout << "MEDIA" << endl << endl;
    for(int j = 0; j < ga -> generation; j++){
        double soma_melhor = 0.0;
        for(int i = 0; i < 10; i++){
        }
    }
    
    for(int j = 0; j < ga -> generation; j++){
        double soma = 0.0;
        for(int i = 0; i < 10; i++){
        }
    }


    cout << "OK" << endl;

    return 0;
}