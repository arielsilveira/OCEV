#include "GA.hpp"

void GA::mutacao(){
    if(mutation_type == "BIT_FLIP"){

    }else if(mutation_type == "RANDOM"){

    }else if(mutation_type == "SWAP_MUTATION"){

    }else if(mutation_type == "MICHALEWICZ"){

    }else{
        cout << "Falha na operação de mutação" << endl;
        exit(1);
    }

}