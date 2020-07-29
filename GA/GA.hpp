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
    bool elitismo;

    int generation;
    int population_size;
    int gene_size;
    int min;
    int max;
    int v;
    int qnt_selecionado;
    int num_execucao;

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

    vector<vector<double>> melhor;
    vector<vector<double>> media;
    vector<vector<double>> pior;

    GA(int num_execucao, bool elitismo, int generation, int population_size, int gene_size, double crossover_probability, double mutation_probability, string gene_type, string crossover_type, string mutation_type, string selection_type, int min, int max, double k, int v, string criterio, int qnt_selecionado){

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
        this -> qnt_selecionado = qnt_selecionado;
        this -> elitismo = elitismo;
        this -> num_execucao = num_execucao;
        vector<int> aux(population_size, 0);

        select = aux;

        start_generation();


    }

    void start_generation(){
        for(int i = 0; i < population_size; i++){
            Individual<int> a = Individual<int>(gene_type, gene_size, min, max);
            this -> population.push_back(a);
        }
    }

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

void selecao_menu(GA* &ga);

void selecao_torneio(GA* &ga);

void selecao_roleta(GA* &ga);

void crossover_menu(GA* &ga);

void crossover_PMX(GA* &ga);

void mutacao_swap(GA* &ga);

void one_point(GA* &ga);

void two_point(GA* &ga);

void uniform(GA* &ga);

void arithmetic(GA* &ga);

void troca_genetica_corte(GA* &ga, int p1, int p2, int corte_init, int corte_end, vector<Individual<int>> &new_population);

void final_result(GA* &ga, int pos);

bool sortbysec(const pair<int,double> &a, const pair<int,double> &b);

void mutacao_bitflip(GA* &ga);

void mutation_random(GA* &ga);

void mutacao_menu(GA* &ga);