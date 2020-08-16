#include "GA.hpp"

GA* read_file(string name){
    string caminho = "Entrada/"+name;

    ifstream file;
    file.open(caminho);

    if(!(file.is_open())){
        cout << "Arquivo inexistente" << endl;
        exit(0);
    }

    bool elitismo = false;

    int generation = 0;
    int population_size = 0;
    int gene_size = 0;
    int min = 0;
    int max = 0;
    int v = 0;
    int qnt_selecionado = 0;
    int num_execucao = 0;

    double crossover_probability = 0.0;
    double mutation_probability = 0.0;
    double k = 0.0;

    string gene_type = "";
    string crossover_type = "";
    string mutation_type = "";
    string selection_type = "";
    string criterio = "";
    string e = "";
    
    while(!file.eof()){
        string op;
        file >> op;
        if(op == "num_execucao"){
            file >> num_execucao;
        }else if( op == "num_Generation"){
            file >> generation;
        
        }else if(op =="gene_Size"){
            file >> gene_size;
        
        }else if(op == "population_Size"){
            file >> population_size;
        
        }else if(op == "gene_Type"){
            file >> gene_type;

            if(gene_type == "INT-PERM"){
                file >> min >> max;
            }else if(gene_type == "INT"){
                file >> min >> max;
            }else if(gene_type == "REAL"){
                file >> min >> max;
            }

        }else if(op == "crossover_Probability"){
            file >> crossover_probability;

        }else if(op == "crossover_Type"){
            file >> crossover_type;

        }else if(op == "mutation_Probability"){
            file >> mutation_probability;

        }else if(op == "mutation_Type"){
            file >> mutation_type;
        
        }else if(op == "selection_Type"){
            file >> selection_type;
            
            if(selection_type == "TORNEIO"){
                file >> k >> qnt_selecionado;

            }else if(selection_type == "VIZINHANCA"){
                file >> v >> criterio;
            }
        }else if(op == "ELITISMO"){
            file >> elitismo;
        }else{
            cout << "Erro na entrada dos dados" << endl;
            cout << "Formato do arquivo:" << endl;
            cout << "num_Generation int" << endl;
            cout << "population_Size int" << endl;
            cout << "gene_Size int" << endl;
            cout << "gene_Type string" << endl;
            cout << "crossover_Probability double"  << endl;
            cout << "crossover_Type string"  << endl;
            cout << "mutation_Probability double" << endl;
            cout << "mutation_Type string" << endl;
            cout << "selection_Type LINEAR_NEIGHBOURHOOD 12 NEIGHBOUR_BEST" << endl;
            exit(2);

        }

    }
    return new GA(num_execucao, elitismo, generation, population_size, gene_size, crossover_probability, mutation_probability, gene_type, crossover_type, mutation_type, selection_type, min, max, k, v, criterio, qnt_selecionado);

}

void print_best_worse(GA* &ga){
    auto val_best = ga -> population[0].solution;
    int index_best = 0;
    
    auto val_worse = ga -> population[0].solution;
    int index_worse = 0;
    
    int individual = ga -> population_size;

    for (int i = 0; i < individual; i++){
        if(ga -> population[i].solution > val_best){
            val_best = ga -> population[i].solution;
            index_best = i;
        }

        if(ga -> population[i].solution < val_worse){
            val_worse = ga -> population[i].solution;
            index_worse = i;
        }
    }
    cout << endl;
    
    cout << "Melhor indivíduo: " << index_best << endl;
    cout << "Valor fitness: " << val_best << endl;

    ga -> population[index_best].print_individual();
    cout << endl;

    // cout << "Pior indivíduo: " << index_worse << endl;
    // cout << "Valor fitness: " << val_worse << endl;

    // ga -> population[index_worse] -> print_individual();

}

void print_individuals(GA* &ga){
    for(int i = 0; i < ga -> population_size; i++){
        cout << "Indivíduo " << i << ": ";
        
        ga -> population[i].print_individual();
    }
}

void print_solutions(GA* &ga){
    for(int i = 0; i < ga -> population_size; i++){
        cout << "Solution " << i << ": " << ga -> population[i].solution << endl;
    }
}


void final_result(GA* &ga, int pos){
    double val_best = 0;
    int index_best = 0;
    
    double val_worse = 1;
    int index_worse = 0;
    
    int individual = ga -> population_size;

    double media = 0;
    double t = 0;

    for (int i = 0; i < individual; i++){
        if(ga -> population[i].solution > val_best){
            val_best = ga -> population[i].solution;
            index_best = i;
            if(ga -> population[i].collision == 0){
                t = ga -> population[i].solution;
            }
        }

        if(ga -> population[i].solution < val_worse){
            val_worse = ga -> population[i].solution;
            index_worse = i;
        }

        media += ga -> population[i].solution;


    }

    ga -> melhor[pos].push_back(val_best);
    ga -> media[pos].push_back(media/ga -> population_size);
    ga -> pior[pos].push_back(val_worse);
    ga -> melhor_media[pos].push_back(t);
}

bool sortbysec(const pair<int,double> &a, 
              const pair<int,double> &b) 
{ 
    return (a.second < b.second); 
} 

