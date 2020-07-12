#include "../GA.hpp"

void fitness(vector<Individual *> population){
    long int dec = 0;
    int max_chromossomo = population[0] -> max_chromossomo;

    for(int k = 0; k < population[0] -> individual; k++){
        dec = 0;
        
        for(int i = 0; i < max_chromossomo; i++){
            dec += population[k] -> chromossomo[(max_chromossomo - 1) - i] * pow(2,i);
        }

        double x = 0;

        x = -4 + ((2 - (-4)) / (pow(2,16) - 1)) * dec;

        population[k] -> solution = (x + 4)/6.0;

    }
}