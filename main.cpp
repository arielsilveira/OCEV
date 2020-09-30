#include "GA/GA.hpp"
#include <chrono> 
#include <omp.h>
#include <SFML/Graphics.hpp>
#include <unistd.h>

using namespace std::chrono; 

double position = 0;

void draw(sf::RenderWindow &window, Individual<int> best, GA* &ga){
    int rect_size = 15;

    sf::RectangleShape rect(sf::Vector2f(rect_size, rect_size));
    rect.setOutlineThickness(0.75f);
    rect.setOutlineColor(sf::Color(122,122,122));
    rect.setOrigin(sf::Vector2f(0,0));
    vector<pair<int, int> > move = {
            {-1,0}, 
            {1,0}, 
            {0,1}, 
            {0,-1}
        };

    int x_best = ga -> init_x;
    int y_best = ga -> init_y;

    cerr << "Fitness: " <<  best.solution << endl;
    cerr << "Move: " << best.cnt_move << endl;

    map<pair<int, int>, int> visited;
    map<pair<int, int>, int>::iterator find_visited;
    visited[{ga -> init_x, ga-> init_y}] = 1;

    for(int k = 0; k < ga -> gene_size; k++){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                exit(0);
            }
        }
        // int move_x = move[ best.chromossomo[k] ].first;
        // int move_y = move[ best.chromossomo[k] ].second;

        // if(ga -> map[move_x + x_best][ move_y + y_best] == 1){
        //     visited[{move_x + x_best, move_y + y_best}]++;
        //     x_best += move_x;
        //     y_best += move_y;
        // }
        
        window.clear(sf::Color::White);
        for(int i = 0; i < ga -> line; i++){
            for(int j = 0; j < ga -> column; j++){
                rect.setPosition(rect_size * j, rect_size * i);

                if(ga -> map[i][j] == 0){
                    rect.setFillColor(sf::Color::Black);
                }else if(ga -> map[i][j] == 1){
                    rect.setFillColor(sf::Color(255, 0, 0, 255 * ga -> map_cult[i][j]));

                }else if(ga -> map[i][j] == 2){
                    rect.setFillColor(sf::Color::Green);

                }else if(ga -> map[i][j] == 3){
                    rect.setFillColor(sf::Color::Red);
                }

                // if(i == x_best && j == y_best){
                //     rect.setFillColor(sf::Color::Blue);
                // }

                // if(i == best.x && j == best.y){
                //     rect.setFillColor(sf::Color::Magenta);
                // }

                window.draw(rect);
            }
        }
        
        window.display();
        // sf::sleep(sf::milliseconds(1000));
        
    }

}


class Best_Individual{
public:
    double solution;
    vector<int> chromossomo;
    int colisao;
    double FO;

    Best_Individual(){
        solution = 0;
        colisao = 0;
        FO = 0;
        
    }
};

void swap_worse(GA* &ga, Individual<int> best){
    double worse = ga -> population[0].solution;
    int index = 0;

    for(int i = 0; i < ga -> population_size; i++){
        if(ga -> population[i].solution < worse){
            index = i;
            worse = ga -> population[i].solution;
        }
    }
    ga -> population[index] = best;

}

Individual<int> getBest(GA* &ga){
    double best_solution = 0;
    Individual<int> best;
    for(int i = 0; i < ga -> population_size; i++){
        if(ga -> population[i].solution > best_solution){
            best_solution = ga -> population[i].solution;
            best = ga -> population[i];
        }
    }
    return best;
}



int main(int argc, char const * argv[]){
    if(argc != 2){
        cout << "Falha na passagem de parâmetros" << endl;
        cout << "./ga arq_name" << endl;
        exit(1);
    }
    
    vector<vector<int> > map;
    string title; 
    string arq = argv[1];

    int line, column;
    int init_x, init_y;
    int finish_x, finish_y;
    
    if(arq == "arq_Nqueen"){
        title = "NQueens";
    }else if(arq == "arq_funcAlgebrica"){
        title = "Função Algébrica";
    }else if(arq == "arq_Radios"){
        title = "Radios";
    }

    Best_Individual BI;

    GA *ga;
    ga = read_file(argv[1]);
    cin >> ga -> line >> ga -> column;


    for(int i = 0; i < ga -> line; i++){
        ga -> map.push_back(vector<int>());
        ga -> map_cult.push_back(vector<double>());
        for(int j = 0; j < ga -> column; j++){
            int l;
            cin >> l;
            // if(l == 0 && i != 0 && i != ga ->line-1 && j != 0 && j != ga -> column-1){
            //     l = 1;
            // }
            ga -> map[i].push_back(l);
            ga -> map_cult[i].push_back(0.0);
            
            if(l == 2){
                ga -> init_x = i;
                ga -> init_y = j;
                // cout << "x" << i << endl;
                // cout << "y" << j << endl;
            }

            if(l == 3){
                ga -> finish_x = i;
                ga -> finish_y = j;
            }
        }
    }

    double media_time = 0.0;

	sf::RenderWindow window(sf::VideoMode(380, 460), "Robo no Labirinto");
    bool open = true;

    Individual<int> best;
    
    for(int i = 0; i < ga -> num_execucao; i++){
        auto start = high_resolution_clock::now(); 
        cerr << "Iteração: " << i << endl;
        ga -> start_generation();

        ga -> melhor.push_back(vector<double>());
        ga -> media.push_back(vector<double>());
        ga -> pior.push_back(vector<double>());
        ga -> melhor_media.push_back(vector<double>());
        ga -> reset_generation();
        fitness(ga);

        for(int j = 0; j < ga -> generation; j++){
            cerr << "Geração: " << j << endl;
            ga -> geracao = j+1;
            sf::Event event;

            while(window.pollEvent(event)){
                if(event.type == sf::Event::Closed){
                    exit(0);
                }
            }

            if(ga -> elitismo){
                best = getBest(ga);

                // if(x_final == best.x && y_final == best.y && (x_final != ga -> finish_x || y_final != ga -> finish_y)){
                //     position += 0.02;

                // }else{
                //     position = 0;
                // }
                // auto dist_real = [](int min, int max) -> double {
                //         random_device g_rd;
                //         mt19937 g_e(g_rd());
                //         uniform_real_distribution<> g_dist(min, max);
                    
                //         return g_dist(g_e);
                //     };

                // if(position >= 0.3 && position >= dist_real(0, 1) && (x_final != ga -> finish_x || y_final != ga -> finish_y)){
                //     best.solution /= 2;
                //     position = 0;
                //     cerr << "TROCOU" << endl;
                // }

                // x_final = best.x;
                // y_final = best.y;
                if(j % 25 == 0)
                    draw(window, best, ga);
                
            }            
            double fit_min = ga -> population[0].solution;
            double fit_max = ga -> population[0].solution;
            for(int k = 0; k < ga -> population_size; k++){
                fit_min = min(fit_min, ga -> population[k].solution);
                fit_max = max(fit_max, ga -> population[k].solution);
            }

            cout << "Fitness antes: " << fit_max - fit_min << endl;
            ga -> controlaPressaoSeletiva();
            fit_min = ga -> population[0].solution;
            fit_max = ga -> population[0].solution;
            for(int k = 0; k < ga -> population_size; k++){
                fit_min = min(fit_min, ga -> population[k].solution);
                fit_max = max(fit_max, ga -> population[k].solution);
            }
            cout << "Fitness depois: " << fit_max - fit_min << endl << endl;
            selecao_menu(ga);
            
            crossover_menu(ga);

            mutacao_menu(ga);

            ga -> reset_generation();
            fitness(ga);
            


            if(ga -> elitismo){
                swap_worse(ga, best);
            }
            
            // final_result(ga, i);



            // for (int l = 0; l < ga -> population_size; l++){
            //     if(ga -> population[l].solution > BI.solution){
            //         BI.solution = ga -> population[l].solution;
            //         BI.chromossomo = ga -> population[l].chromossomo;
            //         BI.colisao = ga -> population[l].collision;
            //         BI.FO = ga -> population[l].FO;
            //     }
            // }

            // for(int m = 0; m < ga -> map.size(); m++){
            //     for(int n = 0; n < ga -> map[m].size(); n++){
            //         cout << setprecision(2) << fixed << ga -> map_cult[m][n] << " ";
            //     }
            //     cout << endl;
            // }

            // cout << endl << endl;

        }

        if(i != ga -> num_execucao - 1){
            ga -> population.clear();
        }   
        
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<seconds>(stop - start);          //Calcula o tempo
        media_time += duration.count();
        cerr << "Duração= " << duration.count() << endl;
    }
    
    bool flag = true;
    while(flag){
        sf::Event event;

        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                flag = false;
            }
        }
        draw(window, best, ga);

    }
    
    

    /*
    cerr << (media_time/ga->num_execucao)  << endl;  

    ofstream saida_melhor;
    saida_melhor.open("melhor.txt");

    ofstream saida_media;
    saida_media.open("media.txt");
    
    ofstream saida_pior;
    saida_pior.open("pior.txt");
    

    for(int j = 0; j < ga -> generation; j++){
        double soma_melhor = 0.0;
        double soma_media = 0.0;
        double soma_pior = 0.0;
        
        for(int i = 0; i < ga -> num_execucao; i++){
            soma_melhor += ga -> melhor[i][j];
            soma_media += ga -> media[i][j];
            soma_pior += ga -> pior[i][j];
        }

        saida_melhor << soma_melhor/ga -> num_execucao << endl;
        saida_media << soma_media/ga -> num_execucao << endl;
        saida_pior << soma_pior/ga -> num_execucao << endl;
    }
    


    ofstream config;
    config.open("config.txt");
    config << "PROBLEM=" << title << endl;
    config << "BEST=";
    for(int i = 0; i < BI.chromossomo.size(); i++){
        config << " " << BI.chromossomo[i];
    }
    config << endl;
    config << "Objective Function=";
    

    if(arq == "arq_nqueen"){
        config << BI.FO << endl;
        config << "Quantidade de colisão=" << BI.colisao << endl;

    }else if(arq == "arq_Radios"){
        int st, lt;
        auto lambda_radios = [&](vector<int> best_solution) -> int{
            int collision = 0;
            auto to_dec = [&](int start, int qnt) -> int {
                int res = 0;
                for(int i = start; i < start + qnt; i++){
                    res += best_solution[i] * pow(2, i - start);
                }
                return res;
            };


            auto mapa = [](int valor, int minimo, int maximo) -> int {
                double res = minimo + ((maximo - minimo) / (double) ((1 << 5) - 1)) * valor;
                return std::round(res);
            };
            st = int(mapa(to_dec(0,5),0,24));
            lt = int(mapa(to_dec(5,5),0,16));
            return 30*mapa(to_dec(0,5), 0, 24) + 40*mapa(to_dec(5,5), 0, 16);

        };
        
        config << "Standard=" << st << endl;
        config << "Luxuosos=" << lt << endl;

    }else if(arq == "arq_funcAlgebrica"){
        double val_x = 0;
        auto lambda_funcao = [&val_x](vector<int> best_solution) -> double{
            auto to_dec = [&](int start, int qnt) -> int {
                int res = 0;
                for(int i = start; i < qnt; i++){
                    res += best_solution[i] * pow(2, i);
                }
                return res;
            };

            auto mapa = [](int valor, int minimo, int maximo) -> double {
                double res = minimo + ((maximo - minimo) / (double) ((1 << 16) - 1)) * valor;
                return res;
            };

            int dec = to_dec(0, best_solution.size());

            double x = mapa(dec, -2, 2);
            val_x = x;
            return cos(20*x) - (abs(x)/2.0) + (pow(x, 3)/4.0);
        };
                
        config << "X = " << val_x << endl;
    }
            
    config << "Fitness Function=" << BI.solution << endl;

    double media = 0;
    long double desvio = 0;
    double div = 0;
    
    for(int i = 0; i < ga -> num_execucao; i++){
            if(ga -> melhor_media[i][ga -> generation - 1] != 0){
                media += ga -> melhor_media[i][ga -> generation - 1];
                div++;
            }
    }

    if(div == 0){
        div = 1;
    }

    media = (media/div); 

    
    for(int i = 0; i < ga -> num_execucao; i++){
        desvio += pow(ga -> melhor_media[i][ga -> generation - 1] - media, 2);
    }

    desvio = (desvio /div);
    desvio = sqrt(desvio);

    config << "Média=" << media << endl;
    config << "Desvio=" << desvio << endl;

    //Printando o tabuleiro
    for(int i = 0; i < BI.chromossomo.size(); i++){
            config << "| " ;
        for(int j = 0; j < BI.chromossomo.size(); j++){
            if(BI.chromossomo[i] == j){
                config << "R" << " " ;
            }else{
                config << "-" << " " ;
            }
        }
        config << "|" << endl;
    }
    */
    return 0;
}