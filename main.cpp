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

    print_individuals(*ga);

    fitness(*ga);

    print_solutions(*ga);

    print_best_worse(*ga);

    ga -> selecao();
    ga -> print_select();
    
    cout << "OK" << endl;

    return 0;
}