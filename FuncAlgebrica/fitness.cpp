#include "../GA/GA.hpp"

void fitness(GA* &ga){
    long int dec = 0;
    int max_chromossomo = ga -> gene_size;

    for(int k = 0; k < ga -> population_size; k++){
        dec = 0;
        
        dec = dec_to_bin(ga -> population[k], max_chromossomo, 0);
        
        double x = 0;

        x = mapeamento(dec, -4, 2, 16);
        //  + ((2 - (-4)) / (pow(2,16) - 1)) * dec;
        ga -> population[k].solution = (x + 4)/6.0;

    }
}