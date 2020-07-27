#include "GA/GA.hpp"
// #include <time.h>       /* time */

int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }

    GA *ga;

    ga = read_file(argv[1]);

    print_individuals(ga);

    for(int i = 0; i < ga -> generation; i++){
        cout << "Geração " << i << endl;
        fitness(ga);

        selecao_torneio(ga);

        
        crossover_PMX(ga);

        mutacao_swap(ga);
    
        print_individuals(ga);
        cout << endl << endl;
        print_solutions(ga);
        cout << endl << endl;
    
    }

    cout << "OK" << endl;

    return 0;
}