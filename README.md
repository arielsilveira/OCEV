# Repositório de OCEV  :seedling: :leaves: :deciduous_tree:

### Dupla:
    Ariel Agne da Silveira,
    Eduarda Cristina Rosa

---

### To do list:
   
1. Seleções
      
      As rotinas de seleção montam a população intermediária

      - [X] Torneio

      - [X] Roleta

      - [ ] Vizinhança

2. Crossover 

    - [X] PMX

    - [X] One point

    - [X] Two point
    
    - [X] Uniforme 
    
    - [X] Aritmético
    
    - [ ] BLX-a

3. Mutações 

    - [X] Swap mutation

    - [ ] Bit flip

    - [ ] Valor aleatório do domínio de variáveis

    - [ ] Michalewicz

4.  Incluir parâmetro de seleção elitista 

    Retira-se o pior individuo da geração atual e no lugar dele deve-se inserir o melhor indivíduo da geração anterior - booleano

5. Exercicío 5 
    
    Processamento de jobs em máquinas paralelas

6. Gráficos de convergência 

    * N rainhas
        - [ ] Melhor
        - [ ] Média da população
 
    * Maximização
        - [ ] Melhor
        - [ ] Média da população

    * Rádios
        - [ ] Melhor
        - [ ] Média da população
        
    Para uma execução, o gráfico traz:

        1. O fitness do melhor indivíduo de cada geração e 

        2. A média do fitness da população de cada geração.

    Para uma quantidade de execuções, o gráfico traz:

        1. A média do fitness do melhor indivíduo de cada geração e 

        2. A média da média do fitness da população de cada geração.

---

### Executando:

`$ g++ NQueen/* GA/* mutacao.cpp selecao.cpp crossover.cpp main.cpp -o ga`

`$ ./ga arq_nqueen`