#include "GA.hpp"

GA* read_file(string name){
    string caminho = "Entrada/"+name;

    ifstream file;
    file.open(caminho);

    if(!(file.is_open())){
        cout << "Arquivo inexistente" << endl;
        exit(0);
    }

    int generation;
    int population;
    int gene_size;
    int min;
    int max;

    double crossover_probability;
    double mutation_probability;

    string gene_type;
    string crossover_type;
    string mutation_type;
    string selection_type;


    while(!file.eof()){
        string op;
        file >> op;

        if( op == "num_Generation"){
            file >> generation;
        
        }else if(op =="gene_Size"){
            file >> gene_size;
        
        }else if(op == "population_Size"){
            file >> population;
        
        }else if(op == "gene_Type"){
            file >> gene_type;

        }else if(op == "crossover_Probability"){
            file >> crossover_probability;

        }else if(op == "crossover_Type"){
            file >> crossover_type;

        }else if(op == "mutation_Probability"){
            file >> mutation_type;

        }else if(op == "mutation_Type"){
            file >> mutation_type;
        
        }else if(op == "selection_Type"){
            file >> selection_type;

        }else if(op == "min"){
            file >> min;

        }else if(op == "max"){
            file >> max;

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
            cout << "min int" << endl;
            cout << "max int" << endl;
            exit(2);

        }

    }

    return new GA(generation, population, gene_size, crossover_probability, mutation_probability, gene_type, crossover_type, mutation_type, selection_type, min, max);

}

void print_best_worse(GA ga){
    auto val_best = ga.population[0] -> solution;
    int index_best = 0;
    
    auto val_worse = ga.population[0] -> solution;
    int index_worse = 0;
    
    int individual = ga.population_size;

    for (int i = 0; i < individual; i++){
        if(ga.population[i] -> solution > val_best){
            val_best = ga.population[i] -> solution;
            index_best = i;
        }

        if(ga.population[i] -> solution < val_worse){
            val_worse = ga.population[i] -> solution;
            index_worse = i;
        }
    }
    cout << endl;
    
    cout << "Melhor indivíduo: " << index_best << endl;
    cout << "Valor fitness: " << val_best << endl;

    ga.population[index_best] -> print_individual();
    cout << endl;

    cout << "Pior indivíduo: " << index_worse << endl;
    cout << "Valor fitness: " << val_worse << endl;

    ga.population[index_worse] -> print_individual();

}

void print_individuals(GA ga){
    for(int i = 0; i < ga.population_size; i++){
        cout << "Indivíduo " << i << ": ";
        
        ga.population[i] -> print_individual();
    }
}
void print_solutions(GA ga){
    for(int i = 0; i < ga.population_size; i++){
        cout << "Solution " << i << ": " << ga.population[i] -> solution << endl;
    }
}


/*
int dec_to_bin(Individual * population, int end,  int init){
    int dec = 0;

    for(int i = init; i < end; i++){
        dec += population -> chromossomo[(end - 1) - i] * pow(2,i);
    }

    return dec;
}

double mapeamento(int valor, int min, int max, int l){
    // cout << "Valor = " << valor << endl;
    // cout << "Mapeado = ";
    // cout << min + (max - min)/(pow(2, l) - 1) * valor << endl;
    
    return min + (max - min)/(pow(2, l) - 1) * valor;
}
*/