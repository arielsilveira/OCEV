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

    - [X] Bit flip

    - [X] Valor aleatório do domínio de variáveis

    - [ ] Michalewicz

4.  Parâmetro de seleção elitista 

    - [X] Elitismo

5. Exercicíos
    
    [X] Processamento de jobs em máquinas paralelas (Exercicío 6)

    [X] NQueens valoradas (Exercicío 7) 

6. Gráficos de convergência 

    * N rainhas
        - [X] Melhor
        - [X] Média da população
 
    * Maximização
        - [X] Melhor
        - [X] Média da população

    * Rádios
        - [X] Melhor
        - [X] Média da população
        
    Para uma execução, o gráfico traz:

        1. O fitness do melhor indivíduo de cada geração e 

        2. A média do fitness da população de cada geração.

    Para uma quantidade de execuções, o gráfico traz:

        1. A média do fitness do melhor indivíduo de cada geração e 

        2. A média da média do fitness da população de cada geração.

---

### Executando:

`$ make PASTA=_nome_pasta_`

`$ ./ga nome_arquivo`

Para gerar o gráfico: 

`$ python3 graph.py `





