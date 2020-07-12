#include "GA.hpp"

vector<Individual *> read_file(string name){
    string caminho = "Entrada/"+name;

    ifstream file;
    file.open(caminho);

    if(!(file.is_open())){
        cout << "Arquivo inexistente" << endl;
        exit(0);
    }

    vector<Individual *> population;
    
    string codificacao;
    int chromossomo, individual, min, max;

    while(!file.eof()){
        string op;
        file >> op;

        if( op == "Codificação"){
            file >> codificacao;
        
        }else if(op =="Chromossomo"){
            file >> chromossomo;
        
        }else if(op == "Individual"){
            file >> individual;
        
        }else if(op == "Min"){
            file >> min;
        
        }else if(op == "Max"){
            file >> max;
        
        }else{
            cout << "Erro na entrada dos dados" << endl;
            exit(2);
        }

    }

    for(int i = 0; i < individual; i++){
        population.push_back(new Individual(codificacao, individual, chromossomo, min, max));
    }

    return population;
}

void print_best_worse(vector<Individual *> population){
    auto val_best = population[0] -> solution;
    int index_best = 0;
    
    auto val_worse = population[0] -> solution;
    int index_worse = 0;
    
    int individual = population[0] -> individual;

    for (int i = 0; i < individual; i++){
        if(population[i] -> solution > val_best){
            val_best = population[i] -> solution;
            index_best = i;
        }

        if(population[i] -> solution < val_worse){
            val_worse = population[i] -> solution;
            index_worse = i;
        }
    }
    cout << endl;
    
    cout << "Melhor indivíduo " << index_best << endl;
    cout << "Valor fitness: " << val_best << endl;

    population[index_best] -> print_individual();
    cout << endl;

    cout << "Pior indivíduo " << index_worse << endl;
    cout << "Valor fitness: " << val_worse << endl;

    population[index_worse] -> print_individual();

}

void print_individuals(vector<Individual *> population){
    for(int i = 0; i < population[0] -> individual; i++){
        cout << "Indivíduo " << i << ": ";
        
        population[i] -> print_individual();
    }
}

void print_solutions(vector<Individual *> population){
    for(int i = 0; i < population.size(); i++){
        cout << "Solution " << i << ": " << population[i] -> solution << endl;
    }
}