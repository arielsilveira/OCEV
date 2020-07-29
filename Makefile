FILES = mutacao.cpp selecao.cpp crossover.cpp main.cpp
GA = GA/ga.cpp
LIBRARY = -fopenmp -Ofast
END = -o ga

all:
	g++ $(PASTA)/fitness.cpp $(GA) $(FILES)  $(LIBRARY) $(END)