FILES = mutacao.cpp selecao.cpp crossover.cpp main.cpp 
GA = GA/ga.cpp
LIBRARY = -lsfml-graphics -lsfml-window -lsfml-system -fopenmp -O2
END = -o ga -g

all:
	g++ $(PASTA)/fitness.cpp $(GA) $(FILES)  $(LIBRARY) $(END)