#include "../GA/GA.hpp"

void fitness(GA* &ga){

    for(int i = 0; i < ga -> population_size; i++){
        int st = dec_to_bin(ga -> population[i], (ga -> gene_size)/2, 0); 
        int lt = dec_to_bin(ga -> population[i], ga -> gene_size, ((ga -> gene_size)/2)); 

        st = int(mapeamento(st, 0, 24, 5));
        lt = int(mapeamento(st, 0, 16, 5));

        int fo = 30*st + 40*lt;
        // cout << "FO: " << fo << endl;
        double penalidade = max(0.0, (st + 2 * lt - 40) / 16.0);
        // cout << "Penalidade: " << penalidade << endl;

        ga -> population[i].solution = (st * 30 + lt * 40) / 1360.0 - penalidade;

        // cout << "Solução: " << population[i] -> solution << endl << endl;
    }

}