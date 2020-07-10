#include <bits/stdc++.h>

using namespace std;

class Individual{

private:

public:
    vector<double> chromossomo;
    int max_chromosomo;
    string cod;
    int min, max;

    Individual(string cod, int max_chromosomo, int min, int max){

        this->max_chromosomo = max_chromosomo;
        this->cod = cod;
        this->min = min;
        this->max = max;

        chromossomo = vector<double>(max_chromosomo);

        if (cod == "bin"){
            
            auto dist = []() -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(0, 1);

                return g_dist(g_e);
            };

            for (int i = 0; i < max_chromosomo; i++){
                chromossomo[i] = dist();
            }
        
        }else if (cod == "int-perm"){

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
            
            for (int i = 0; i < max_chromosomo; i++){
                dist(chromossomo, min, max);
            }

        }else if (cod == "int"){
            auto dist = [](int min, int max) -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(min, max);

                return g_dist(g_e);
            };

            for (int i = 0; i < max_chromosomo; i++){
                chromossomo[i] = dist(min, max);
            }

        }else if (cod == "real"){
            auto dist = [](int min, int max) -> double {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_real_distribution<> g_dist(min, max);
            
                return g_dist(g_e);
            };

            for (int i = 0; i < max_chromosomo; i++){
                chromossomo[i] = dist(min, max);
            }
        
        }else{
            cout << "Erro na passagem de cod" << endl;
            exit(0);
        
        }

    }

    void print_individual(){

        for (int i = 0; i < chromossomo.size(); i++){
            cout << chromossomo[i] << " ";
        }

        cout << endl;
    }

    int fitness(){
        int collision = 0, total = 0;

        for(int i = 0; i < max_chromosomo; i++){
            for(int k = 0; k < max_chromosomo; k++){
                if(i != k){
                    if(abs(chromossomo[i] - chromossomo[k]) == abs(i - k)){
                        collision++;
                    }
                }

            }
        }

        return collision;
    }

    void print_individual_total(){

        for(int i = 0; i < max_chromosomo; i++){
            for(int j = 0; j < max_chromosomo; j++){
                if(chromossomo[i] == j){
                    cout << setprecision(2) << " Q " << " "; 
                }else{
                    cout << setprecision(2) << " . " << " ";
                }
            }

            cout << endl << endl;
        }
    }
    

};

int main(int argc, char const *argv[]){

    vector<Individual *> population;
    string cod;
    int chromossomo, individual, min, max;

    cin >> cod >> chromossomo >> individual >> min >> max;

    for (int i = 0; i < individual; ++i){
        population.push_back(new Individual(cod, chromossomo, min, max));
    }

    for (int i = 0; i < individual; i++){
        cout << "Indivíduo " << i << ": ";
        population[i] -> print_individual();
    }

    vector<int> solutions(individual, 0); 
    

    for(int i = 0; i < individual; i++){
        solutions[i] = population[i] -> fitness();
    }

    for(int i = 0; i < solutions.size(); i++){
        cout << solutions[i] << " ";
    }

    cout << endl;
    int val_best = solutions[0];
    int index_best = -1;
    
    int val_worse = solutions[0];
    int index_worse = 0;
    
    for (int i = 0; i < individual; i++){
        if(solutions[i] < val_best){
            val_best = solutions[i];
            index_best = i;
        }

        if(solutions[i] > val_worse){
            val_worse = solutions[i];
            index_worse = i;
        }
    }
    cout << endl;
    
    cout << "Melhor indivíduo " << index_best << endl;
    cout << "Valor fitness: " << val_best << endl;

    population[index_best] -> print_individual();
    population[index_best] -> print_individual_total();
    cout << endl;

    cout << "Pior indivíduo " << index_worse << endl;
    cout << "Valor fitness: " << val_worse << endl;

    population[index_worse] -> print_individual();
    population[index_worse] -> print_individual_total();

    return 0;
}
