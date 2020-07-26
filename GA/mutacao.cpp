#include "GA.hpp"

void GA::mutacao(){
    if(mutation_type == "BIT_FLIP"){
        bit_flip();
    }else if(mutation_type == "RANDOM"){
        random();
    }else if(mutation_type == "SWAP_MUTATION"){
        swap_mutation();
    }else if(mutation_type == "MICHALEWICZ"){

    }else{
        cout << "Falha na operação de mutação" << endl;
        exit(1);
    }

}

void GA::bit_flip(){
    if(gene_type == "BINARY"){

        auto dist_real = [](int min, int max) -> double {
            random_device g_rd;
            mt19937 g_e(g_rd());
            uniform_real_distribution<> g_dist(min, max);
        
            return g_dist(g_e);
        };

        for(int i = 0; i < population_size; i++){
            for(int j = 0; j < gene_size; j++){
                double rnd = dist_real(0, 1);

                if(rnd < mutation_probability){
                    population[i] -> chromossomo[j] = !population[i] -> chromossomo[j];
                }

            }
        }
    }else{
        cout << "Falha na operação de mutação." << endl;
        exit(1);
    }
}

void GA::random(){

    auto dist_bin = []() -> int {
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_int_distribution<> g_dist(0, 1);

        return g_dist(g_e);
    };

    auto dist_int = [](int min, int max) -> int {
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_int_distribution<> g_dist(min, max);

        return g_dist(g_e);
    };

    auto dist_real = [](int min, int max) -> double {
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_real_distribution<> g_dist(min, max);
    
        return g_dist(g_e);
    };

    for(int i = 0; i < population_size; i++){
        for(int j = 0; j < gene_size; j++){
            double rnd = dist_real(0, 1);

            if(rnd < mutation_probability){
                if(gene_type == "REAL"){
                    population[i] -> chromossomo[j] = dist_real(min, max);
                }else if(gene_type == "INT"){
                    population[i] -> chromossomo[j] = dist_int(min, max);
                }else{
                    population[i] -> chromossomo[j] = dist_bin();
                }
                    
            }

        }
    }
}

void GA::swap_mutation(){
    if(gene_type != "INT-PERM") exit(1);

    auto dist_real = [](int min, int max) -> double {
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_real_distribution<> g_dist(min, max);
    
        return g_dist(g_e);
    };

    auto dist_int = [](int min, int max) -> int {
        random_device g_rd; 
        mt19937 g_e(g_rd());
        uniform_int_distribution<> g_dist(min, max);

        return g_dist(g_e);
    };
    

    // cout << "Mutation Probability: " << mutation_probability << endl;
    for(int i = 0; i < population_size; i++){
        vector<double> vet_rnd;

        for(int j = 0; j < gene_size; j++){
            double rnd = dist_real(0, 1);
            vet_rnd.push_back(rnd);
            if(rnd <= mutation_probability){
                // cerr << "deveria ter trocado" << endl;
                int pos = 0;
                do{
                    pos = dist_int(0, gene_size-1);
                }while(j == pos);
                // cerr << "###" << endl; 
                // cerr << population[i] -> chromossomo[j] << " -- " << population[i] -> chromossomo[pos] << endl;
                swap(population[i] -> chromossomo[j], population[i] -> chromossomo[pos]);
                // cerr << population[i] -> chromossomo[j] << " -- " << population[i] -> chromossomo[pos] << endl;
                // cerr << "###" << endl;

            }
        }

        cout << "Indivíduo " << i << ": ";
        for(double x : vet_rnd){
            cout << x << ", ";
        }
        cout << endl;
        for(auto x : population[i] -> chromossomo) cout << x << " ";
        cout << endl;
    }


}
