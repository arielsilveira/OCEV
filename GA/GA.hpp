#include <bits/stdc++.h>

using namespace std;

class Individual{

private:

public:
    vector<double> chromossomo;
    string gene_type;
    int min, max;

    double solution = 0.0;

    Individual(string gene_type, int gene_size, int min, int max);

    void print_individual();
    
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

    vector<Individual *> population;
    vector<int> select;

    GA(int generation, int population_size, int gene_size, double crossover_probability, double mutation_probability, string gene_type, string crossover_type, string mutation_type, string selection_type, int min, int max, int k, int v, string criterio);

    void selecao_roleta_sem_reposicao();
    
    void selecao_torneio();
    
    void selecao_vizinhanca();

    void selecao();
    
    void crossover();

    void one_point();
    
    void two_point();
    
    void uniform();
    
    void pmx();
    
    void blx_a();
    
    void arithmetic();

    void troca_genetica_corte(int p1, int p2, int corte_init, int corte_end, vector<Individual *> &new_population);

    void mutacao();

    void print_select();

};



GA* read_file(string name);

void fitness(GA ga);

void print_best_worse(GA ga);

void print_individuals(GA ga);

void print_solutions(GA ga);

// int dec_to_bin(GA ga, int end, int init);

// double mapeamento(int valor, int min, int max, int l);
