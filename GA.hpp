#include <bits/stdc++.h>

using namespace std;

class Individual{

private:

public:
    vector<double> chromossomo;
    string gene_type;
    int min, max;

    double solution = 0.0;

    Individual(string gene_type, int gene_size, int min, int max){

        this -> gene_type = gene_type;
        this -> min = min;
        this -> max = max;

        chromossomo = vector<double>(gene_size);

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

            auto dist = [](vector<double> &c, int min, int max) -> void{
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

    double crossover_probability;
    double mutation_probability;

    string gene_type;
    string crossover_type;
    string mutation_type;
    string selection_type;

    vector<Individual *> population;
    vector<int> select;

    GA(int generation, int population_size, int gene_size, double crossover_probability, double mutation_probability, string gene_type, string crossover_type, string mutation_type, string selection_type, int min, int max){

        this -> generation = generation; 
        this -> population_size = population_size;
        this -> gene_size = gene_size;
        this -> crossover_probability = crossover_probability;
        this -> mutation_probability;
        this -> gene_type = gene_type;
        this -> crossover_type = crossover_type;
        this -> mutation_type = mutation_type;
        this -> selection_type = selection_type;
        this -> min = min;
        this -> max = max;
        vector<int> aux(population_size, 0);
        select = aux;

        for(int i = 0; i < population_size; i++){
            this -> population.push_back(new Individual(gene_type, gene_size, min, max));
        }

    }

    void selecao(){
        double T = 0.0;
        vector<double> fit_relativo(population.size(), 0.0);

        double K = 0.8;

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


        if(this -> selection_type == "ROLETA"){
                    
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

        }else if(selection_type == "TORNEIO"){
            for(int i = 0; i < population.size(); i++){
                int individuo1 = dist_int(0, population.size()-1);        //melhor
                int individuo2 = dist_int(0, population.size()-1);        //pior

                if(population[individuo2]->solution > population[individuo1]->solution){
                    int aux;
                    aux = individuo1;
                    individuo1 = individuo2;
                    individuo2 = aux;
                }

                if( K >= dist_double(0,1) ){
                    select[i] = individuo1;
                }else{
                    select[i] = individuo2;
                }

            }
        }
    }

    void print_select(){
        for(int i = 0; i < population_size; i++){
            cout << "Indivíduo " << select[i] << ": " << population[select[i]] -> solution << endl;

        }
    }

};



GA* read_file(string name);

void fitness(GA ga);

void print_best_worse(GA ga);

void print_individuals(GA ga);

void print_solutions(GA ga);

// int dec_to_bin(Individual * population, int end, int init);

// double mapeamento(int valor, int min, int max, int l);

// void selecao(vector<Individual *> population, vector<int> &select);