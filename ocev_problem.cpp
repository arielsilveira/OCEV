#include <bits/stdc++.h>

using namespace std;

class Individual{
private:
public:
    vector<int> chromossomo;

    Individual(string cod, int max_chromosomo){

        chromossomo = vector<int>(max_chromosomo);



        for (size_t i = 0; i < max_chromosomo; i++) {
            chromossomo[i] = distribution();
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
        cout << population[i] -> chromossomo << " ";
    }

    return 0;
}
