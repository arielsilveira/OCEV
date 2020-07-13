#include "../GA.hpp"

void fitness(vector<Individual *> population){

    for(int i = 0; i < population[0] -> individual; i++){
        int st = dec_to_bin(population[i], (population[i] -> max_chromossomo)/2, 0); 
        int lt = dec_to_bin(population[i], population[i] -> max_chromossomo, ((population[i] -> max_chromossomo)/2)); 

        st = int(mapeamento(st, 0, 24, 5));
        lt = int(mapeamento(st, 0, 16, 5));

        int fo = 30*st + 40*lt;
        // cout << "FO: " << fo << endl;
        double penalidade = max(0.0, (st + 2 * lt - 40) / 16.0);
        // cout << "Penalidade: " << penalidade << endl;

        population[i] -> solution = (st * 30 + lt * 40) / 1360.0 - penalidade;

        // cout << "Solução: " << population[i] -> solution << endl << endl;
    }

}