#include <bits/stdc++.h>

using namespace std;

class NaturalSelection{
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
                // population[i][j] = dist_int_perm(chromossomo - 1);
                // population[i][j] = dist_int(5, chromossomo - 1);
                population[i][j] = dist_bin();
                // population[i][j] = dist_real(0,1);
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


    void dist_int_perm(int max){
        for(int i = 0; i < population.size(); i++){
            for(int j = 0; j < population[i].size(); j++){
                population[i][j] = j;
            }
        }


        for (int i = 0; i < population.size(); i++){
            for (int j = 0; j < population[i].size(); j++){
                int r = dist_int(0, max);

                int temp = population[i][j];
                population[i][j] = population[i][r];
                population[i][r] = temp;
            }
        }
    }



    void print_population(){
        for (int i = 0; i < population.size(); i++){
            for (int j = 0; j < population[i].size(); j++){
                cout << population[i][j] << " ";
            }
            cout << endl;
        }

    }

    void print_individual(int ind){
        for (size_t i = 0; i < population.size(); i++) {
            cout << population[ind][i] << " ";
        }

        cout << endl;
    }

};

int main(int argc, char const *argv[]){

    NaturalSelection *selection;
    selection = new NaturalSelection(0, 10, 10);

    selection -> print_population();
    cout << endl;
    selection -> print_individual(5);
    return 0;
}
