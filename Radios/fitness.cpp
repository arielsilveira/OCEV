#include "../GA/GA.hpp"

void fitness(GA* &ga){

    auto to_dec = [&](int start, int qnt, int k) -> int {
        int res = 0;
        for(int i = start; i < start + qnt; i++){
            res += ga->population[k].chromossomo[i] * pow(2, i - start);
        }
        return res;
    };


    auto mapa = [](int valor, int minimo, int maximo) -> int {
        double res = minimo + ((maximo - minimo) / (double) ((1 << 5) - 1)) * valor;
        return std::round(res);
    };

    for(int i = 0; i < ga -> population_size; i++){

        int st = to_dec(0, 5, i);
        int lt = to_dec(5, 5, i);

        st = int(mapa(st, 0, 24));
        lt = int(mapa(lt, 0, 16));

        int fo = 30*st + 40*lt;
        double penalidade = max(0.0, (st + 2 * lt - 40) / 16.0);

        ga -> population[i].solution = (st * 30 + lt * 40) / 1360.0 - penalidade;
        ga -> population[i].FO = (st * 30 + lt * 40);
        ga -> population[i].collision = 0;
    }

}