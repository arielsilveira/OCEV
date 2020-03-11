#include <bits/stdc++.h>

using namespace std;

class Individual{
private:
public:
    vector<int> chromossomo;

    Individual(string cod, int max_chromosomo){

        chromossomo = vector<int>(max_chromosomo);
        if(cod == "bin"){
            auto dist =  [](){
                random_device g_rd;
                mt19937 g_e(g_rd());
                uniform_int_distribution<> g_dist(0, 1);

                return g_dist(g_e);
            };

        }else if(cod == "int-perm"){
            auto dist = [](int x, int y){
                for(int i = 0; i < population.size(); i++){
                    for(int j = 0; j < population[i].size(); j++){
                        population[i][j] = j;
                    }
                }


                for (int i = 0; i < population.size(); i++){
                    for (int j = 0; j < population[i].size(); j++){
                        int r = dist_int(0, max-1);

                        int temp = population[i][j];
                        population[i][j] = population[i][r];
                        population[i][r] = temp;
                    }
                }
            };

        for (size_t i = 0; i < max_chromosomo; i++) {
            chromossomo[i] = binario();
        }
    }

    void print_individual(){
        for (size_t i = 0; i < chromossomo.size(); i++) {
            cout << chromossomo[i] << " ";
        }

        cout << endl;
    }
};

int main(int argc, char const *argv[]) {
    vector<Individual *> population;
    string cod;
    int chromossomo, individual;

    cin >> cod >> chromossomo >> individual;

	for (int i = 0; i < individual; ++i){
		population.push_back(new Individual(cod, chromossomo));
	}

    for (size_t i = 0; i < individual; i++) {
        population[i] -> print_individual();
        cout << endl;
    }

    return 0;
}
