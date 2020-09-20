#include "GA/GA.hpp"
#include <chrono> 
#include <omp.h>
using namespace std::chrono; 


class Best_Individual{
public:
    double solution;
    vector<int> chromossomo;
    int colisao;
    double FO;

    Best_Individual(){
        solution = 0;
        colisao = 0;
        FO = 0;
        
    }
};



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

    Best_Individual BI;

    GA *ga;
    ga = read_file(argv[1]);

    double media_time = 0.0;
    
    for(int i = 0; i < ga -> num_execucao; i++){
        auto start = high_resolution_clock::now(); 
        cerr << "Iteração: " << i << endl;
        ga -> start_generation();

        ga -> melhor.push_back(vector<double>());
        ga -> media.push_back(vector<double>());
        ga -> pior.push_back(vector<double>());
        ga -> melhor_media.push_back(vector<double>());

        fitness(ga);

        for(int j = 0; j < ga -> generation; j++){
            Individual<int> best;

            if(ga -> elitismo){
                best = melhor(ga);
            }            


            selecao_menu(ga);
            
            crossover_menu(ga);

            mutacao_menu(ga);

            fitness(ga);
            
            if(ga -> elitismo){
                swap_worse(ga, best);
            }

            final_result(ga, i);

            for (int l = 0; l < ga -> population_size; l++){
                if(ga -> population[l].solution > BI.solution){
                    BI.solution = ga -> population[l].solution;
                    BI.chromossomo = ga -> population[l].chromossomo;
                    BI.colisao = ga -> population[l].collision;
                    BI.FO = ga -> population[l].FO;
                }
            }

        }

        if(i != ga -> num_execucao - 1){
            ga -> population.clear();
        }   
        
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<seconds>(stop - start);          //Calcula o tempo
        media_time += duration.count();
        cerr << "Duração= " << duration.count() << endl;
    }

    cerr << (media_time/ga->num_execucao)  << endl;  

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
    for(int i = 0; i < BI.chromossomo.size(); i++){
        config << " " << BI.chromossomo[i];
    }
    config << endl;
    config << "Objective Function=";
    

    if(arq == "arq_nqueen"){
        config << BI.FO << endl;
        config << "Quantidade de colisão=" << BI.colisao << endl;

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
        
        // config << lambda_radios(best_solution) << endl;
        config << "Standard=" << st << endl;
        config << "Luxuosos=" << lt << endl;

    }else if(arq == "arq_funcAlgebrica"){
        double val_x = 0;
        auto lambda_funcao = [&val_x](vector<int> best_solution) -> double{
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
            val_x = x;
            return cos(20*x) - (abs(x)/2.0) + (pow(x, 3)/4.0);
        };
                
        // config << lambda_funcao(best_solution) << endl;
        config << "X = " << val_x << endl;
    }
            
    config << "Fitness Function=" << BI.solution << endl;

    double media = 0;
    long double desvio = 0;
    double div = 0;
    
    for(int i = 0; i < ga -> num_execucao; i++){
            if(ga -> melhor_media[i][ga -> generation - 1] != 0){
                media += ga -> melhor_media[i][ga -> generation - 1];
                div++;
            }
    }

    if(div == 0){
        div = 1;
    }

    media = (media/div); 

    
    for(int i = 0; i < ga -> num_execucao; i++){
        desvio += pow(ga -> melhor_media[i][ga -> generation - 1] - media, 2);
    }

    desvio = (desvio /div);
    desvio = sqrt(desvio);

    config << "Média=" << media << endl;
    config << "Desvio=" << desvio << endl;

    //Printando o tabuleiro
    for(int i = 0; i < BI.chromossomo.size(); i++){
            config << "| " ;
        for(int j = 0; j < BI.chromossomo.size(); j++){
            if(BI.chromossomo[i] == j){
                config << "R" << " " ;
            }else{
                config << "-" << " " ;
            }
        }
        config << "|" << endl;
    }

    return 0;
}