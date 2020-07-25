#include "GA.hpp"

Individual::Individual(string gene_type, int gene_size, int min, int max){

    this -> gene_type = gene_type;
    this -> min = min;
    this -> max = max;

    chromossomo = vector<double>(gene_size);

    if (gene_type == "BINARY"){
        
        auto dist = []() -> int {
            random_device g_rd;
            mt19937 g_e(g_rd());
            uniform_int_distribution<> g_dist(0, 1);

            return g_dist(g_e);
        };

        for (int i = 0; i < gene_size; i++){
            chromossomo[i] = dist();
        }
    
    }else if (gene_type == "INT-PERM"){

        auto dist = [](vector<double> &c, int min, int max) -> void{
            for (int i = 0; i < c.size(); i++){
                c[i] = i;
            }

            for (int i = 0; i < c.size(); i++){
                auto r = [](int min, int max) {
                    random_device g_rd;
                    mt19937 g_e(g_rd());
                    uniform_int_distribution<> g_dist(min, max);

                    return g_dist(g_e);
                };

                int pos = r(min, max-1);

                int temp = c[i];
                c[i] = c[pos];
                c[pos] = temp;
            }
        };
        
        for (int i = 0; i < gene_size; i++){
            dist(chromossomo, min, max);
        }

    }else if (gene_type == "INT"){
        auto dist = [](int min, int max) -> int {
            random_device g_rd;
            mt19937 g_e(g_rd());
            uniform_int_distribution<> g_dist(min, max);

            return g_dist(g_e);
        };

        for (int i = 0; i < gene_size; i++){
            chromossomo[i] = dist(min, max);
        }

    }else if (gene_type == "REAL"){
        auto dist = [](int min, int max) -> double {
            random_device g_rd;
            mt19937 g_e(g_rd());
            uniform_real_distribution<> g_dist(min, max);
        
            return g_dist(g_e);
        };

        for (int i = 0; i < gene_size; i++){
            chromossomo[i] = dist(min, max);
        }
    
    }else{
        cout << "Erro na passagem de cod" << endl;
        exit(0);
    
    }

}

void Individual::print_individual(){

    for (int i = 0; i < chromossomo.size(); i++){
        cout << chromossomo[i] << " ";
    }

    cout << endl;
}