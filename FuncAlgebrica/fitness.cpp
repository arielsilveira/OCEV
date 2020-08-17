#include "../GA/GA.hpp"

void fitness(GA* &ga){
    int dec = 0;
    int max_chromossomo = ga -> gene_size;

    auto to_dec = [&](int start, int qnt, int k) -> int {
        int res = 0;
        for(int i = start; i < qnt; i++){
            res += ga->population[k].chromossomo[i] * pow(2, i);
        }
        return res;
    };

    auto mapa = [](int valor, int minimo, int maximo) -> double {
        double res = minimo + ((maximo - minimo) / (double) ((1 << 16) - 1)) * valor;
        return res;
    };

    for(int k = 0; k < ga -> population_size; k++){
        dec = to_dec(0, ga->gene_size, k);

        double x = mapa(dec, -2, 2);

        double func_objetivo = cos(20*x) - (abs(x)/2.0) + (pow(x, 3)/4.0);

        ga -> population[k].solution = (func_objetivo + 4)/6.0;
        ga -> population[k].FO = func_objetivo;
        ga -> population[k].collision = 0;

    }
}