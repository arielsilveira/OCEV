#include <bits/stdc++.h>

using namespace std;

template <class T>
class Individual{

private:

public:
    vector<T> chromossomo;
    string gene_type;
    int min, max;

    double solution = 0.0;
    Individual(){}

    Individual(string gene_type, int gene_size, int min, int max){
        this -> gene_type = gene_type;
        this -> min = min;
        this -> max = max;

        chromossomo = vector<T>(gene_size);

        if (gene_type == "BINARY"){
            
            auto dist = []() -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(0, 1);

                return g_dist(g_e);
            };

            for (int i = 0; i < gene_size; i++){
                chromossomo[i] = dist();
            }
        
        }else if (gene_type == "INT-PERM"){

            auto dist = [](vector<T> &c, int min, int max) -> void{
                for (int i = 0; i < c.size(); i++){
                    c[i] = i;
                }

                for (int i = 0; i < c.size(); i++){
                    auto r = [](int min, int max) {
                        random_device g_rd;
                        mt19937 g_e(g_rd());
                        uniform_int_distribution<> g_dist(min, max);

                        return g_dist(g_e);
                    };

                    int pos = r(min, max-1);

                    int temp = c[i];
                    c[i] = c[pos];
                    c[pos] = temp;
                }
            };
            
            for (int i = 0; i < gene_size; i++){
                dist(chromossomo, min, max);
            }

        }else if (gene_type == "INT"){
            auto dist = [](int min, int max) -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(min, max);

                return g_dist(g_e);
            };

            for (int i = 0; i < gene_size; i++){
                chromossomo[i] = dist(min, max);
            }

        }else if (gene_type == "REAL"){
            auto dist = [](int min, int max) -> double {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_real_distribution<> g_dist(min, max);
            
                return g_dist(g_e);
            };

            for (int i = 0; i < gene_size; i++){
                chromossomo[i] = dist(min, max);
            }
        
        }else{
            cout << "Erro na passagem de cod" << endl;
            exit(0);
        
        }

    }

    void print_individual(){

        for (int i = 0; i < chromossomo.size(); i++){
            cout << chromossomo[i] << " ";
        }

        cout << endl;
    }

    
};

class GA{
private:
public:
    int generation;
    int population_size;
    int gene_size;
    int min;
    int max;
    int v;

    double k;
    double crossover_probability;
    double mutation_probability;

    string gene_type;
    string crossover_type;
    string mutation_type;
    string selection_type;
    string criterio;

    vector<Individual <int>> population;
    vector<int> select;

    GA(int generation, int population_size, int gene_size, double crossover_probability, double mutation_probability, string gene_type, string crossover_type, string mutation_type, string selection_type, int min, int max, double k, int v, string criterio){

        this -> generation = generation; 
        this -> population_size = population_size;
        this -> gene_size = gene_size;
        this -> crossover_probability = crossover_probability;
        this -> mutation_probability = mutation_probability;
        this -> gene_type = gene_type;
        this -> crossover_type = crossover_type;
        this -> mutation_type = mutation_type;
        this -> selection_type = selection_type;
        this -> min = min;
        this -> max = max;
        this -> v = v;
        this -> k = k;
        this -> criterio = criterio;

        vector<int> aux(population_size, 0);
        select = aux;

        for(int i = 0; i < population_size; i++){
            Individual<int> a = Individual<int>(gene_type, gene_size, min, max);
            this -> population.push_back(a);
        }

    }

    // // void selecao_roleta_sem_reposicao();
    
    // // void selecao_vizinhanca();

    // void selecao(){
    //     if(this -> selection_type == "ROLETA"){
    //         // selecao_roleta_sem_reposicao();

    //     }else if(selection_type == "TORNEIO"){
    //         selecao_torneio();

    //     }else if(selection_type == "VIZINHANCA"){
    //         // selecao_vizinhanca();

    //     }
    // }
    
    // void crossover(){
    //     if(crossover_type == "ONE_POINT"){
    //         one_point();
    //     }else if(crossover_type == "TWO_POINT"){
    //         // two_point();
    //     }else if(crossover_type == "UNIFORM"){
    //         // uniform();
    //     }else if(crossover_type == "PMX"){
    //         pmx();
    //     }else if(crossover_type == "BLX-a"){
    //         // blx_a();
    //     }else if(crossover_type == "ARITHMETIC"){
    //         // arithmetic();
    //     }else{
    //         cout << "Falha na operação do crossover" << endl;
    //         exit(1);
    //     }
    // }

    // void one_point(){
    //     auto dist_real = [](int min, int max) -> double {
    //             random_device g_rd;
    //             mt19937 g_e(g_rd());
    //             uniform_real_distribution<> g_dist(min, max);
            
    //             return g_dist(g_e);
    //     };

    //     auto dist_int = [](int min, int max) -> int {
    //             random_device g_rd;
    //             mt19937 g_e(g_rd());
    //             uniform_int_distribution<> g_dist(min, max);

    //             return g_dist(g_e);
    //     };

    //     double rnd = 0.0;
    //     int corte = 0;
    //     vector<Individual<int>> new_population(population_size, 0);

    //     new_population = population;

    //     for(int i = 0; i < population_size; i++){
    //         new_population[i] = population[select[i]];

    //     }

    //     // paralelo
    //     for(int i = 0; i < population_size; i+=2){
    //         if(i+1 < population_size){
    //             rnd = dist_real(0, 1);
            
    //             if(rnd < crossover_probability ){
    //                 corte = dist_int(1, gene_size-2);
    //                 troca_genetica_corte(i, i+1, corte, gene_size, new_population);
    //             }
    //         }
    //     }

    //     population = new_population;
    // }

    
    // // void two_point();
    
    // // void uniform();
    
    // void pmx(){
    //     if(gene_type != "INT-PERM") cout << "Função inapropriada para o cálculo de crossover" << endl; //exit(1);

    //     auto dist_real = [](int min, int max) -> double {
    //             random_device g_rd;
    //             mt19937 g_e(g_rd());
    //             uniform_real_distribution<> g_dist(min, max);
            
    //             return g_dist(g_e);
    //     };

    //     auto dist_int = [](int min, int max) -> int {
    //             random_device g_rd;
    //             mt19937 g_e(g_rd());
    //             uniform_int_distribution<> g_dist(min, max);

    //             return g_dist(g_e);
    //     };

    //     double rnd = 0.0;
    //     int corte_init = 0;
    //     int corte_end = 0;
    //     // vector<Individual *> new_population(population_size, 0);
    //     // new_population = population;


    //     for(int i = 0; i < population_size; i++){
    //         cout << "Individuos " << i << ": ";
    //         population[i] -> print_individual();
    //     }


    //     // paralelo
    //     for(int i = 0; i < population_size; i+=2){
    //         vector<vector<int>> new_gene(2);
    //         corte_init = dist_int(1, gene_size-3);
    //         corte_end = dist_int(corte_init+1, gene_size-1);

    //         map<int, int> map_1_to_2;
    //         map<int, int> map_2_to_1;
    //         // cout << "Região de corte: (" << corte_init << ", " << corte_end << " )" << endl;
    //         for(int j = corte_init; j <= corte_end; j++){

    //             int f1 = population[i] -> chromossomo[j];
    //             int f2 = population[i+1] -> chromossomo[j];
                
    //             population[i] -> chromossomo[j] = f2;
    //             population[i+1] -> chromossomo[j] = f1;
    //             map_1_to_2[f1] = f2;
    //             map_2_to_1[f2] = f1;
    //         }
            
    //         // for(map<int, int >::const_iterator it = map_1_to_2.begin(); it != map_1_to_2.end(); ++it){
    //             // std::cout << it->first << " -> " << it->second << " --- ";
    //         // }
    //         // cout << endl;
            
    //         // for(map<int, int >::const_iterator it = map_2_to_1.begin(); it != map_2_to_1.end(); ++it){
    //             // std::cout << it->first << " -> " << it->second << " --- ";
    //         // }
    //         // cout << endl;
    //         for(int j = 0; j < gene_size; j++){
            
    //             // cout << "&&&&" << endl;
    //             // population[i] -> print_individual();
    //             // cout << "&&&&" << endl;

    //             if(j < corte_init || j > corte_end){
                    
    //                 // cout << "&&&&" << endl;
    //                 // population[i] -> print_individual();
    //                 // cout << "&&&&" << endl;

    //                 int f1 = population[i] -> chromossomo[j];
    //                 int f2 = population[i+1] -> chromossomo[j];

    //                 if(map_2_to_1.count(f1) > 0){
    //                     // cout << "###" <<endl;
    //                     int val = map_2_to_1[f1];
    //                     // cout << "VAL: " << val << " -  F1: " << f1 << " -  MAPA: " << map_2_to_1[f1] << endl;

    //                     while(map_2_to_1.count(val) > 0 && val != f1){
                            
    //                         val = map_2_to_1[val];

    //                     }
    //                     // cout << "VAL: " << val << " -  F1: " << f1 << " -  MAPA: " << map_2_to_1[f1] << endl;
    //                     // population[i] -> chromossomo[j] = val;
    //                     new_gene[0].push_back(val);
                    
    //                 }else{
    //                     new_gene[0].push_back(f1);
    //                 }

    //                     // cout << "VALOR NA POPULAÇÂO: " << population[i] -> chromossomo[j] << endl;
    //                     // cout << "%%%%" << endl;
                    
    //                 if(map_1_to_2.count(f2) > 0){

    //                     int val = map_1_to_2[f2];
                        

    //                     while(map_1_to_2.count(val) > 0 && val != f2){
                            
    //                         val = map_1_to_2[val];

    //                     }
                        
    //                     // population[i+1] -> chromossomo[j] = val;
    //                     new_gene[1].push_back(val);
    //                 }else{
    //                     new_gene[1].push_back(f2);
    //                 }

    //             }else{
    //                 new_gene[0].push_back(population[i] -> chromossomo[j]);
    //                 new_gene[1].push_back(population[i+1] -> chromossomo[j]);
    //             }
    //         }
            
    //         for(int p = 0; p < gene_size; p++){
    //             population[i] -> chromossomo[p] = new_gene[0][p];
    //             population[i+1] -> chromossomo[p] = new_gene[1][p];
    //         }

    //     }

    //     // cout << "Novo individuo 1: " << endl;
    //     // for(int i = 0; i < new_gene[0].size(); i++){
    //     //     cout << new_gene[0][i] << " ";
    //     // }
    //     // cout << endl;
    //     // // population = population;
    //     // cout << "Novo individuo 2: " << endl;
    //     // for(int i = 0; i < new_gene[1].size(); i++){
    //     //     cout << new_gene[1][i] << " ";
    //     // }
    //     // // population = population;
    //     // // cout << endl;
    //     // for(int i = 0; i < population_size; i++){
    //     //     population[i] -> chromossomo = new_gene[i]; 
    //     // }
    //     for(int i = 0; i < population_size; i++){
    //         cout << "Individuos(teste) " << i << ": ";
    //         population[i] -> print_individual();
    //     }
    //     // exit(0);
    // }
    
    // // void blx_a();
    
    // // void arithmetic();

    // void troca_genetica_corte(int p1, int p2, int corte_init, int corte_end, vector<Individual<int> *> &new_population){
    //     // paralelo
    //     for(int i = 0; i < gene_size; i++){
    //         if(i >= corte_init && i <= corte_end){
    //             int f1 = new_population[p1] -> chromossomo[i];
    //             int f2 = new_population[p2] -> chromossomo[i];
    //             new_population[p1] -> chromossomo[i] = f2;
    //             new_population[p2] -> chromossomo[i] = f1;

    //         }
    //     }

    // }
    // void mutacao(){
    //     if(mutation_type == "BIT_FLIP"){
    //         // bit_flip();
    //     }else if(mutation_type == "RANDOM"){
    //         // random();
    //     }else if(mutation_type == "SWAP_MUTATION"){
    //         swap_mutation();
    //     }else if(mutation_type == "MICHALEWICZ"){

    //     }else{
    //         cout << "Falha na operação de mutação" << endl;
    //         exit(1);
    //     }

    // }

    // // void bit_flip();

    // // void random();



    void print_select(){
        for(int i = 0; i < population_size; i++){
            cout << "Indivíduo " << select[i] << ": " << population[select[i]].solution << endl;
        }
    }

};



GA* read_file(string name);

void fitness(GA* &ga);

void print_best_worse(GA* &ga);

void print_individuals(GA* &ga);

void print_solutions(GA* &ga);

void selecao_torneio(GA* &ga);

void crossover_PMX(GA* &ga);
void mutacao_swap(GA* &ga);
// int dec_to_bin(GA ga, int end, int init);

// double mapeamento(int valor, int min, int max, int l);
