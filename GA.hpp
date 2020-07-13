#include <bits/stdc++.h>

using namespace std;

class Individual{

private:

public:
    vector<double> chromossomo;
    int max_chromossomo;
    string cod;
    int min, max, individual;

    double solution = 0.0;

    Individual(string cod, int individual, int max_chromossomo, int min, int max){

        this -> max_chromossomo = max_chromossomo;
        this -> cod = cod;
        this -> min = min;
        this -> max = max;
        this -> individual = individual;

        chromossomo = vector<double>(max_chromossomo);

        if (cod == "bin"){
            
            auto dist = []() -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(0, 1);

                return g_dist(g_e);
            };

            for (int i = 0; i < max_chromossomo; i++){
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
            
            for (int i = 0; i < max_chromossomo; i++){
                dist(chromossomo, min, max);
            }

        }else if (cod == "int"){
            auto dist = [](int min, int max) -> int {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(min, max);

                return g_dist(g_e);
            };

            for (int i = 0; i < max_chromossomo; i++){
                chromossomo[i] = dist(min, max);
            }

        }else if (cod == "real"){
            auto dist = [](int min, int max) -> double {
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_real_distribution<> g_dist(min, max);
            
                return g_dist(g_e);
            };

            for (int i = 0; i < max_chromossomo; i++){
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
    
};


vector<Individual *> read_file(string name);

void fitness(vector<Individual *> population);

void print_best_worse(vector<Individual *> population);

void print_individuals(vector<Individual *> population);

void print_solutions(vector<Individual *> population);

int dec_to_bin(Individual * population, int end, int init);

double mapeamento(int valor, int min, int max, int l);