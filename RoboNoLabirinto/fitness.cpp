#include "../GA/GA.hpp"
#include <map>

#define PAREDE 0
#define CAMINHO 1
#define PARTIDA 2
#define CHEGADA 3

void fitness(GA* &ga){

    vector<pair<int, int> > move = {
        {-1,0}, 
        {1,0}, 
        {0,1}, 
        {0,-1}
    };

    #pragma omp parallel for
    for(int i = 0; i < ga -> population_size; i++){

        map<pair<int, int>, int> visited;
        map<pair<int, int>, int>::iterator find_visited;
        int good_move = 0;
        int bad_move = 0;
        int x = ga -> init_x;
        int y = ga -> init_y;
        double score = 0;
        int j = 0;
        int cnt = 0;
        bool blocked = false;
        double fitcult = 0;

        visited[{x, y}] = 1;
        
        auto movimento = [move](int pos_x, int pos_y, map<pair<int, int>, int> visited, GA* &ga){
            vector<int> possible_move;

            for(int k = 0; k < 4; k++){
                int move_x = move[ k ].first;
                int move_y = move[ k ].second;

                if(visited.count({move_x + pos_x, move_y + pos_y}) == 0 && 
                    ga -> map[move_x + pos_x][move_y + pos_y] != PAREDE){
                        possible_move.push_back(k);
                }
            }

            return possible_move;

        };

        for(; j < ga -> gene_size; j++){
            vector<int> possible_move = movimento(x, y, visited, ga);
            if(possible_move.size() == 0){
                blocked = true;
                j = ga -> gene_size - 1;
                break;
            }
            int c = possible_move[ga -> population[i].chromossomo[j] % possible_move.size()];
            int move_x = move[ c ].first;
            int move_y = move[ c ].second;
            
            x += move_x;
            y += move_y;

            visited[{x, y}] = 1;

            if(ga -> map[x][y] == CHEGADA){
                break;
            }

            double z = ga -> map_cult[x][y];
            fitcult += sqrt(z);
            cnt += (z > 0);
            
        }
        if(cnt > 0){
            fitcult /= (double)cnt;
            
        }

        double manhattan_distance = abs(x - ga -> finish_x) + abs(y - ga -> finish_y);
        double fitness_move = (ga -> gene_size - j)/(double)(ga -> gene_size);


        ga -> population[i].x = x;
        ga -> population[i].y = y;
        ga -> population[i].cnt_move = j + 1;
        
        double fitness_manhattan = 1 - manhattan_distance/(double)(48.0);
        double p1, p2, p3, p4;
        // if(ng < ga -> generation/3.0){
        p1 = 0.4;
        p2 = 0.2;
        p3 = 0.4;
        
        // }else if(ng < 2*ga -> generation/3.0){
        //     p1 = sqrt(0.3);
        //     p2 = sqrt(0.2);
        //     p3 = sqrt(0.5);

        // }else{
        //     p1 = pow(0.3, 2);
        //     p2 = pow(0.2, 2);
        //     p3 = pow(0.5, 2);
        // }
        double move = (ga -> gene_size - j)/(double)ga -> gene_size;
        ga -> population[i].solution = (p1*fitcult + p2*fitness_manhattan + p3*fitness_move);
        ga -> population[i].FO = j;
        if(blocked){
            ga -> population[i].solution *= 0.1;
        }

        if(x == ga -> finish_x && y == ga -> finish_y){
            ga -> population[i].solution *= pow(62.0/j, 2);
        }


        //  + p3*fitness_move);
        // cout << "Fitcult: " << fitcult << endl;
        // cout << "Manhattan: " << fitness_manhattan << " --- ";
        // cout << "J: " << j << " --- ";
        // cout << "Fitness: " << ga -> population[i].solution  << " --- " << endl;

    }
    
    #pragma omp parallel for
    for(int i = 0; i < ga -> population_size; i++){

        map<pair<int, int>, int> visited;
        map<pair<int, int>, int>::iterator find_visited;
        int x = ga -> init_x;
        int y = ga -> init_y;
        int j = 0;

        visited[{x, y}] = 1;
        ga -> population[i].map_cult[x][y] = ga -> population[i].solution;

        auto movimento = [move](int pos_x, int pos_y, map<pair<int, int>, int> visited, GA* &ga){
                vector<int> possible_move;

                for(int k = 0; k < 4; k++){
                    int move_x = move[ k ].first;
                    int move_y = move[ k ].second;
                    if(visited.count({move_x + pos_x, move_y + pos_y}) == 0 && ga -> map[move_x + pos_x][move_y + pos_y] != PAREDE){
                        possible_move.push_back(k);
                    }
                }
                return possible_move;

            };

        for(; j < ga -> gene_size; j++){
            vector<int> possible_move = movimento(x, y, visited, ga);
            if(possible_move.size() == 0){
                break;
            }
            int c = possible_move[ga -> population[i].chromossomo[j] % possible_move.size()];
            int move_x = move[ c ].first;
            int move_y = move[ c ].second;
            
            x += move_x;
            y += move_y;

            visited[{x, y}] = 1;

            ga -> population[i].map_cult[x][y] = ga -> population[i].solution;

            if(ga -> map[x][y] == CHEGADA){
                break;
            }

        }

    }

    for(int i = 0; i < ga -> map.size(); i++){
        for(int j = 0; j < ga -> map[i].size(); j++){
            double aux = 0;
            int cnt = 0;

            for(int k = 0; k < ga -> population_size; k++){
                double x = ga -> population[k].map_cult[i][j];
                aux += x;
                cnt += x > 0;
            }
            double media = 0;

            if(cnt != 0){
                media = aux/(double)cnt;

                if(ga -> map_cult[i][j] == 0){
                    ga -> map_cult[i][j] = media;    
        
                }else{
                    ga -> map_cult[i][j] = (ga -> map_cult[i][j] + media)/2.0;

                }
            }
        
        }
    }


}