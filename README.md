## Repositório no qual consiste as atividades e trabalhos da disciplina de OCEV

**Dupla:**
    Ariel Agne da Silveira,
    Eduarda Cristina Rosa

**Implementar: Rotinas de seleção**
   
- [X] Roleta sem reposição; (A cada par garante-se a não repetição de itens selecionados)

- [X] Torneio estocástico; (Parâmetro K e função dist(); )

- [ ] Vizinhança linear (anel); (Parâmetros D (distância) e critério de seleção dentro da vizinhança, melhor fitness, fitness proporcional e aleatório)

- [ ] Parâmetro de seleção elitista. (Booleano)

Deve conter o parâmetro de seleção elitista, ou seja, retira-se o pior individuo da geração atual e no lugar dele deve-se inserir o melhor indivíduo da geração anterior. (Parâmetro booleano)

As rotinas de seleção montam a população intermediária, onde será aplicado as perturbações de crossover e mutação posteriormente.

**Executando:**
$ g++ NQueen/fitness.cpp ga.cpp main.cpp -o ga
$ ./ga arq_nqueen