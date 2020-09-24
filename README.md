# Repositório de OCEV  :seedling: :leaves: :deciduous_tree:

![](https://img.shields.io/badge/Code-C%2B%2B-00599C) ![](https://img.shields.io/badge/Python-3.8.2-3776AB)
## Dupla:
    Ariel Agne da Silveira,
    Eduarda Cristina Rosa

---


## Tabela de conteúdos

<!--ts-->
   * [Dupla](#Dupla)
   * [File](#Entrada-do-Arquivo)
   * [Gene](#Gene)
   * [Seleção](#Seleção)
   * [Crossover](#Crossover)
   * [Mutação](#Mutação)
   * [Execução](#Execução)
<!--te-->

## Entrada do arquivo

`num_Generation int`

`population_Size int`

`gene_Size int`

`gene_Type (Gene) int int`

`crossover_Probability double`

`crossover_Type (Crossover)`

`mutation_Probability double`

`mutation_Type (Mutação)`

`selection_Type (Seleção)`

## Gene
    - BINARY
    - INT-PERM int int
    - INT int int
    - REAL int int


## Seleções
      
      As rotinas de seleção montam a população intermediária.

      - [X] Torneio

      - [X] Roleta *

      - [ ] Vizinhança *

      * Para o caso da Roleta, passar como parâmetro
        - int
    
      ** Para o caso da Vizinhança, passar como parâmetro
        - int string¹

        ¹ MELHOR|PROPORCIONAL|RANDOM

## Crossover 

    - [X] PMX

    - [X] One point

    - [X] Two point
    
    - [X] Uniforme 
    
    - [X] Aritmético
    
    - [ ] BLX-a

## Mutação 

    - [X] Swap mutation

    - [X] Bit flip

    - [X] Valor aleatório do domínio de variáveis

    - [ ] Michalewicz

---

## Execução:

`$ make PASTA=_nome_pasta_`

`$ ./ga nome_arquivo`

Para gerar o gráfico: 

`$ python3 graph.py `





