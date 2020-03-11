#include <bits/stdc++.h>

using namespace std;

class NaturalSelection
{
private:
    vector<vector<int> > population;
    int individual;
    int chromossomo;

public:

    NaturalSelection(int codificacao, int individual, int chromossomo){
        this->individual = individual;
        this->chromossomo = chromossomo;
        population = vector<vector<int> >(individual, vector<int>(chromossomo, 0));

        for (int i = 0; i < population.size(); i++){
            for (int j = 0; j < population[i].size(); j++){
                population[i][j] = dist_int_perm(9);
            }
        }

    }

    int dist_bin(){
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_int_distribution<> g_dist(0, 1);

        return g_dist(g_e);
    }

    int dist_int(int x, int y){
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_int_distribution<> g_dist(x, y);

        return g_dist(g_e);
    }
    
    double dist_real(double x, double y){
        random_device g_rd;
        mt19937 g_e(g_rd());
        uniform_real_distribution<> g_dist(x, y);

        return g_dist(g_e);
    }
    
    void print_population(){
        for (int i = 0; i < population.size(); i++){
            for (int j = 0; j < population[i].size(); j++){
                cout << population[i][j] << " ";
            }
            cout << endl;
        }
        
    }

    int dist_int_perm(int max){
        map<int, bool> mapa;


        for (int i = 0; i < population.size(); i++){

            for(int k = 0; k < max; k++){
                mapa[k] = false;
            }
            
            for (int j = 0; j < population[i].size(); j++){
                int random = dist_int(0, max-1);
                bool result = mapa[random];

                while(result){
                    random = dist_int(0, max-1);
                    result = mapa[random];
                }

                mapa[random] = true;
                population[i][j] = random;
            }
        }

        return 0;
    }


};

int main(int argc, char const *argv[]){
    
    NaturalSelection *selection;
    selection = new NaturalSelection(0, 10, 10);

    selection -> print_population();


    return 0;
}
