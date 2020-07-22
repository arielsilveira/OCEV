#include "GA.hpp"
// #include <time.h>       /* time */

int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

    vector<Individual *> population;
    vector<int> select(population.size(), 0);

    population = read_file(argv[1]);

    fitness(population);

    print_best_worse(population);

    cout << endl << endl;

    selecao(population, select);
    


    



    cout << "OK" << endl;

    return 0;
}