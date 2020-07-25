#include "GA.hpp"

void GA::crossover(){
    if(crossover_type == "ONE_POINT"){

    }else if(crossover_type == "TWO_POINT"){

    }else if(crossover_type == "UNIFORM"){

    }else if(crossover_type == "PMX"){

    }else if(crossover_type == "BLX-a"){

    }else if(crossover_type == "ARITHMETIC"){

    }else{
        cout << "Falha na operação do crossover" << endl;
        exit(1);
    }
}