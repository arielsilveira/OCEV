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

    // print_individuals(*ga);

    for(int i = 0; i < ga -> generation; i++){
        cout << "Geração " << i << endl;
        fitness(*ga);

        print_solutions(*ga);
        // print_solutions(*ga);
        // cout << endl << endl;
        print_best_worse(*ga);

        // cout << endl << endl;

        // print_individuals(*ga);
        ga -> selecao();

        // cout << endl << endl << endl;

        // for(int i = 0; i < ga -> select.size(); i++){
        //     cout << "Seleção " << ga -> select[i] << ": ";
        //     for(int j = 0; j < ga -> gene_size; j++){
        //          cout << ga -> population[ga -> select[i]] -> chromossomo[j] << " ";
        //     }
        //     cout << endl;
        // }
        // cout << endl; 
        // print_individuals(*ga);
        // cout << endl; 
        // ga -> print_select();
        // cout << endl; 
        ga -> crossover();
        cout << endl << endl << endl;
        // print_individuals(*ga);

        ga -> mutacao();
        // cout << endl << endl << endl;
        // print_individuals(*ga);
        // print_solutions(*ga);
    }
    cout << "OK" << endl;

    return 0;
}