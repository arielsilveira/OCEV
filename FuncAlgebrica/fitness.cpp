#include "../GA.hpp"

void fitness(vector<Individual *> population){
    long int dec = 0;
    int max_chromossomo = population[0] -> max_chromossomo;

    for(int k = 0; k < population[0] -> individual; k++){
        dec = 0;
        
        dec = dec_to_bin(population[k], max_chromossomo, 0);
        
        double x = 0;

        x = mapeamento(dec, -4, 2, 16);
        //  + ((2 - (-4)) / (pow(2,16) - 1)) * dec;
        population[k] -> solution = (x + 4)/6.0;

    }
}