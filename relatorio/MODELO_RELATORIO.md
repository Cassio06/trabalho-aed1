# Relatório Técnico Completo — Estrutura de Dados I (2026.2)

## Ficha Obrigatória de Identificação

- **Instituição:** Instituto de Ensino Superior iCEV
- **Curso / Período:** Engenharia de Software — 1º Período (2026-2)
- **Disciplina:** Algoritmo e Estrutura de Dados I (Tipo: P2)
- **Professor:** Hilson Silva
- **Nome da Turma:** [Preencher: ADELLE ou SNYDER]
- **Aluno 1:** Cássio Filipe Meireles De Carvalho Braga — **Matrícula 1:** [Preencher]
- **Aluno 2:** Lukas Souza Melo — **Matrícula 2:** [Preencher]
- **Data:** 02/11/2026

---

## 1. Introdução, Escopo e Divisão da Dupla

Este trabalho prático aplica os conceitos fundamentais de **Estruturas de Dados Lineares**, **Estruturas de Dados Não-Lineares** e **Algoritmos de Ordenação** a **24 problemas reais do cotidiano** (dois problemas por estrutura/algoritmo), implementando todas as estruturas do zero sem recorrer a coleções ou rotinas de ordenação prontas das bibliotecas padrão.

A divisão de desenvolvimento entre a dupla foi organizada em 6 categorias (12 problemas) para cada integrante:

- **Cássio Filipe Meireles De Carvalho Braga (Java — `java(Cássio)/`):**
  - Filas (Situações 1 e 2), Árvore Binária de Busca — BST (Situações 7 e 8), Árvore Balanceada — AVL (Situações 9 e 10), Bubble Sort (Situações 15 e 16), Insertion Sort (Situações 19 e 20) e Merge Sort (Situações 21 e 22), acompanhadas de 7 suítes de testes automatizados (`verificar.sh` com **107 casos aprovados, 0 pendentes e 0 falhas**).
- **Lukas Souza Melo (C — `Pilha/`, `Lista_Encadeada/`, `Grafo/`, `Tabela_Hash/`, `Selection_Sort/`, `Quick_Sort/`):**
  - Pilhas (Situações 3 e 4), Listas Encadeadas (Situações 5 e 6), Grafos (Situações 11 e 12), Tabela Hash (Situações 13 e 14), Selection Sort (Situações 17 e 18) e Quick Sort (Situações 23 e 24), com menus interativos e simulações automatizadas para todos os cenários do edital.

---

## 2. Estruturas de Dados Lineares

### 2.1 Filas (Queues) — `java(Cássio)/fila/`

- **Justificativa de Escolha:** A fila segue a política **FIFO (*First-In, First-Out*)**, na qual o primeiro elemento inserido é o primeiro a ser atendido. É a estrutura ideal para clínicas médicas e spoolers de impressão, pois assegura justiça na ordem de chegada e previsibilidade de atendimento com custo $O(1)$ nas extremidades.
- **Funcionamento Interno:** Implementada em [`Fila.java`](../java(Cássio)/fila/Fila.java) sobre um array circular (`Object[20]`) gerenciado pelos índices `inicio`, `fim` e `quantidade`. Inserções (`enqueue`) e remoções (`dequeue`) avançam os ponteiros via aritmética modular `(indice + 1) % elementos.length`. A operação `removerUltimo()` recua `fim` com `(fim - 1 + elementos.length) % elementos.length` para cancelar o último trabalho enviado que ainda aguarda na fila.
- **Complexidade:**
  - **Tempo:** `enqueue`: $O(1)$; `dequeue`: $O(1)$; `front`: $O(1)$; `removerUltimo`: $O(1)$; `isEmpty` / `size`: $O(1)$; `listar`: $O(n)$.
  - **Espaço:** $O(N)$ para o array circular ($N = 20$) e $O(1)$ auxiliar por operação.

#### Situação Problema 1 – Sistema de Atendimento de uma Clínica Médica (`fila.Clinica`)
- **Cenário e Entrada:** Simulação de 15 pacientes chegando a cada 7 minutos a partir das `08:05`, com atendimento iniciando às `08:00` e duração estimada de 10 minutos por consulta (`Modo 1 -> Opção 5 -> Opção 0`).
- **Saída Observada:**
```text
Clínica: atendimento FIFO, estimativa de 10 minutos por paciente.
Chamado às 08:05: Ana Lima - chegada: 08:05 - atendimento: Consulta | espera estimada: 0 min
Chamado às 08:15: Bruno Costa - chegada: 08:12 - atendimento: Exame | espera estimada: 3 min
...
Chamado às 10:25: Olivia Gomes - chegada: 09:43 - atendimento: Retorno | espera estimada: 42 min

Ordem efetiva de atendimento: 15 paciente(s)
1 - Ana Lima - chegada: 08:05 - atendimento: Consulta
...
15 - Olivia Gomes - chegada: 09:43 - atendimento: Retorno
Espera média estimada: 21,00 min
```

#### Situação Problema 2 – Fila de Impressão em Laboratório de Informática (`fila.FilaImpressao`)
- **Cenário e Entrada:** Simulação com 12 trabalhos de impressão (75 páginas), cancelamento do último trabalho enviado (`Lucas - seminario.pdf - 9 páginas`, Opção `6`) e impressão dos 11 trabalhos restantes (Opção `5`).
- **Saída Observada:**
```text
Simulação: 12 trabalhos de impressão.
Último trabalho aguardando cancelado: Lucas - seminario.pdf - 9 página(s)
1 - Imprimindo: Ana - algoritmos.pdf - 8 página(s)
2 - Imprimindo: Bruno - resumo.docx - 3 página(s)
...
11 - Imprimindo: Karen - tabela.pdf - 3 página(s)
Relatório: 11 trabalho(s), 66 página(s). A sequência efetiva foi exibida a cada impressão.
```

---

### 2.2 Pilhas (Stacks) — `Pilha/`

- **Justificativa de Escolha:** A pilha segue a política **LIFO (*Last-In, First-Out*)**, na qual o último elemento inserido é o primeiro a ser removido. É a estrutura natural para reverter ações recentes em um editor de texto (Undo/Redo) e para validar delimitadores aninhados em expressões matemáticas, onde o último parêntese/colchete/chave aberto precisa ser o primeiro a fechar.
- **Funcionamento Interno:** Implementada com vetor estático e índice `topo` (inicializado em `-1`). `empilhar` incrementa `topo` e grava o registro em $O(1)$; `desempilhar` lê `dados[topo]` e decrementa `topo` em $O(1)$. No editor de texto, uma segunda pilha (`redo`) recebe as ações desfeitas da pilha `undo`. No verificador de expressões, cada caractere de abertura é empilhado junto com seu índice na string para reportar a posição exata de qualquer desbalanceamento.
- **Complexidade:**
  - **Tempo:** `empilhar` (`push`), `desempilhar` (`pop`) e `topo` (`peek`): $O(1)$; validação de expressão de tamanho $n$: $O(n)$.
  - **Espaço:** $O(n)$ proporcional à capacidade máxima da pilha.

#### Situação Problema 3 – Sistema de Desfazer (Undo) em Editor de Texto Simples (`Pilha/Sistema de Undo.c`)
- **Cenário e Entrada:** Opção `7` — Simulação automatizada com 12 ações (digitação, formatação e exclusão), seguida de 4 operações de Undo e 2 operações de Redo.
- **Saída Observada:**
```text
--- PASSO 1: Inserindo 12 Acoes na Pilha ---
Acao 'Ola, este e um documento de teste.' (Digitacao) registrada com sucesso!
...
Acao 'Fim da primeira secao.' (Exclusao) registrada com sucesso!

--- PASSO 2: Desfazendo 4 Acoes Seguidas (Undo) ---
[DESFAZENDO] Acao revertida: [Exclusao] "Fim da primeira secao."
[DESFAZENDO] Acao revertida: [Digitacao] "Fim da primeira secao."
[DESFAZENDO] Acao revertida: [Formatacao] "Fonte alterada para tamanho 12"
[DESFAZENDO] Acao revertida: [Digitacao] " usando Pilhas em C."

--- PASSO 3: Refazendo 2 Acoes (Redo) ---
[REFAZENDO] Acao refeita: [Digitacao] " usando Pilhas em C."
[REFAZENDO] Acao refeita: [Formatacao] "Fonte alterada para tamanho 12"
```

#### Situação Problema 4 – Verificação de Expressões com Parênteses, Colchetes e Chaves (`Pilha/Verificação de Sistemas.c`)
- **Cenário e Entrada:** Opção `2` — Execução dos casos de teste obrigatórios do enunciado (`"{ [ ( ) ] }"`, `"( [ ) ]"`, `"((()))"`, `"([)]"`, `"([]]"`).
- **Saída Observada:**
```text
Analisando expressao: "{ [ ( ) ] }"
-> RESULTADO: CORRETA (Expressao perfeitamente balanceada)!

Analisando expressao: "( [ ) ]"
-> RESULTADO: INCORRETA!
   [RELATORIO DE ERRO] Desbalanceamento no caractere ')' (posicao 4): Nao combina com '[' aberto na posicao 2.

Analisando expressao: "((()))"
-> RESULTADO: CORRETA (Expressao perfeitamente balanceada)!

Analisando expressao: "([)]"
-> RESULTADO: INCORRETA!
   [RELATORIO DE ERRO] Desbalanceamento no caractere ')' (posicao 2): Nao combina com '[' aberto na posicao 1.
```

---

### 2.3 Listas Encadeadas — `Lista_Encadeada/`

- **Justificativa de Escolha:** Listas encadeadas alocam nós dinamicamente conforme a demanda e permitem inserir, remover e reordenar elementos em qualquer posição (início, meio ou fim) ajustando apenas ponteiros, sem necessidade de realocar blocos contíguos de memória.
- **Funcionamento Interno:** Cada nó (`Musica` ou `Produto`) contém os dados de domínio e um ponteiro `proximo`. A inserção no início atualiza `inicio` em $O(1)$; inserções em posição específica, buscas, remoções e reordenações percorrem os ponteiros até o nó alvo em $O(n)$, liberando memória com `free()` nas remoções.
- **Complexidade:**
  - **Tempo:** Inserir no início: $O(1)$; Inserir no fim / em posição específica / remover / buscar / reordenar / listar: $O(n)$.
  - **Espaço:** $O(n)$ alocado dinamicamente para $n$ elementos ativos.

#### Situação Problema 5 – Gerenciamento de Playlist de Músicas (`Lista_Encadeada/playlist.c`)
- **Cenário e Entrada:** Opção `8` — Simulação com 12 músicas inseridas no início, fim e posição específica (posição 4), busca por título, reordenação (movendo da posição 12 para a 2) e remoção de música.
- **Saída Observada:**
```text
--- MINHA PLAYLIST (12 musicas) ---
 1. Aquarela                     | Toquinho             | 4.25 min
 2. Bohemian Rhapsody            | Queen                | 5.92 min
 3. Hotel California             | Eagles               | 6.50 min
 4. Evidencias                   | Chitaozinho & Xororo | 4.65 min
...
12. tempo Perdido                | Legiao Urbana        | 5.03 min
Tempo total da playlist: 59.98 min

[BUSCA] Encontrada na posicao 4: 'Evidencias' - Chitaozinho & Xororo (4.65 min)
[REORDENACAO] Musica 'tempo Perdido' movida da posicao 12 para 2!
[-] Musica 'Imagine' removida com sucesso!
```

#### Situação Problema 6 – Controle de Estoque de uma Pequena Loja (`Lista_Encadeada/estoque.c`)
- **Cenário e Entrada:** Opção `8` — Simulação de uma semana (7 dias) de movimentação em uma loja de materiais de construção, com cadastro, baixas de vendas, remoção automática de produto esgotado (`Caixa D'Agua 1000L`), buscas por código/nome e alerta de estoque mínimo (`< 10`).
- **Saída Observada:**
```text
[Dia 4 - Quinta] Venda total do estoque de Caixas D'Agua (produto esgotado):
[ATUALIZACAO] Cod 105 (Caixa D'Agua 1000L) -> Nova quantidade: 0
[ESGOTADO] Produto 'Caixa D'Agua 1000L' zerado; removendo da lista ativa...
[-] Produto removido da lista ativa: Cod 105 (Caixa D'Agua 1000L)

--- PRODUTOS ABAIXO DO ESTOQUE MINIMO (< 10 unidades) ---
Cod: 108 | Nome: Disjuntor Bipolar 40A  | Qtd:   6 | R$ 42.00
Cod: 104 | Nome: Tijolo Baiano Milheiro | Qtd:   3 | R$ 850.00
Cod: 103 | Nome: Tinta Acrilica 18L     | Qtd:   4 | R$ 219.90
Cod: 102 | Nome: Argamassa AC-III 20kg  | Qtd:   7 | R$ 29.50
```

---

## 3. Estruturas de Dados Não-Lineares

### 3.1 Árvore Binária de Busca — BST (`java(Cássio)/bst/`)

- **Justificativa de Escolha:** A BST mantém os elementos hierarquicamente ordenados (menores à esquerda, maiores à direita), permitindo buscas exatas, inserções, remoções e consultas ordenadas por prefixo em tempo médio $O(\log n)$, sem precisar reordenar toda a base a cada alteração.
- **Funcionamento Interno:** Implementada em [`BST.java`](../java(Cássio)/bst/BST.java). Na remoção de nó com dois filhos, o nó é substituído pelo seu sucessor em-ordem (`menorNo(atual.direita)`). O método `listarPorPrefixo` utiliza as propriedades de ordem da BST para podar subárvores que não podem conter o prefixo buscado.
- **Complexidade:**
  - **Tempo:** Inserir, buscar e remover: $O(\log n)$ no caso médio e $O(n)$ no pior caso; Percurso em-ordem: $O(n)$.
  - **Espaço:** $O(n)$ para os nós e $O(h)$ na pilha de recursão.

#### Situação Problema 7 – Cadastro e Busca de Alunos por Matrícula (`bst.CadastroAlunos`)
- **Cenário e Entrada:** Cadastro de 20 alunos (`1001` a `1020`), busca pela matrícula `1001`, remoção da matrícula `1008` e listagem ordenada em-ordem.
- **Saída Observada:**
```text
Matrícula: Encontrado: 1001 - Ana Lima - Computação
Matrícula: Removido: 1008 - Bruno Costa - Engenharia
1001 - Ana Lima - Computação
1002 - Daniel Rocha - Administração
...
1007 - Tais Carvalho - Matemática
1009 - Elisa Sousa - Computação
...
1020 - Samuel Pinto - Engenharia
```

#### Situação Problema 8 – Sistema de Autocomplete de Nomes de Produtos (`bst.AutocompleteProdutos`)
- **Cenário e Entrada:** Catálogo de 30 produtos; consulta de autocomplete para o prefixo `"ca"` e para prefixo inexistente `"xyz"`.
- **Saída Observada:**
```text
Prefixo: Sugestões para ca (nenhuma linha se não houver):
Caderno
Calculadora
Caneta Azul
Caneta Preta
Caneta Vermelha
Cartolina
```

---

### 3.2 Árvore Balanceada — AVL (`java(Cássio)/avl/`)

- **Justificativa de Escolha:** Em sistemas críticos (como índice de RH por CPF ou ranking online em tempo real), a BST comum pode degenerar em lista encadeada ($O(n)$) se os dados chegarem ordenados. A árvore AVL mantém o fator de balanceamento de todos os nós em $\{-1, 0, 1\}$ mediante rotações simples e duplas, garantindo $O(\log n)$ no pior caso.
- **Funcionamento Interno:** Implementada em [`AVL.java`](../java(Cássio)/avl/AVL.java). Após cada inserção ou remoção, atualiza-se a altura do nó e verifica-se `fator = altura(esq) - altura(dir)`, aplicando rotações LL, RR, LR ou RL quando $|fator| > 1$. No ranking de jogadores, a chave combina pontuação formatada com 10 dígitos e nome (`%010d:%s`), preservando empates e permitindo extrair os Top-K em percurso reverso (direita → raiz → esquerda).
- **Complexidade:**
  - **Tempo:** Inserir, buscar e remover: $O(\log n)$ no melhor, médio e pior casos; Top-K (`listarMaiores`): $O(\log n + K)$.
  - **Espaço:** $O(n)$ para os nós e $O(\log n)$ na pilha de recursão.

#### Situação Problema 9 – Índice de CPF para Sistema de RH (`avl.IndiceCpf`)
- **Cenário e Entrada:** Inserção de 25 funcionários em ordem crescente de CPF (`731.205.100-00` a `731.205.124-68`), verificação de altura/balanceamento e busca de CPF.
- **Saída Observada:**
```text
Altura: 5
Fator da raiz: 0
Todos os nós balanceados: true
CPF: Encontrado: 731.205.100-00 - Ana Lima - Analista
```

#### Situação Problema 10 – Ranking de Jogadores em um Jogo Online (`avl.RankingJogadores`)
- **Cenário e Entrada:** 30 jogadores iniciais, três atualizações de pontuação na rodada e consulta ao Top-5 (`K = 5`).
- **Saída Observada:**
```text
Três atualizações de pontuação da rodada:
Ana Lima - 520 ponto(s) -> Ana Lima - 750 ponto(s)
Fabio Santos - 705 ponto(s) -> Fabio Santos - 750 ponto(s)
Marina Barros - 664 ponto(s) -> Marina Barros - 920 ponto(s)

K (0 a 30):
Marina Barros - 920 ponto(s)
Isabela Dias - 816 ponto(s)
Rafaela Torres - 812 ponto(s)
Eduarda Lopes - 808 ponto(s)
Heitor Melo - 779 ponto(s)
Altura: 6 | Fator da raiz: -1 | Todos os nós balanceados: true
```

---

### 3.3 Grafos — `Grafo/`

- **Justificativa de Escolha:** Grafos modelam diretamente redes de conexões e rotas. Na logística de entregas, um grafo ponderado em lista de adjacência associado ao algoritmo de **Dijkstra** determina o caminho de menor custo entre bairros. Em redes sociais, um grafo não-direcionado associado à **Busca em Largura (BFS)** determina amigos em comum, sugestões de amizade e o menor grau de separação entre duas pessoas.
- **Funcionamento Interno:**
  - Em [`Grafo/Entregas.c`](../Grafo/Entregas.c), cada bairro possui uma lista encadeada de adjacência (`NoAdj`) com o vértice destino e o peso em km; `dijkstra` relaxa as arestas escolhendo iterativamente o vértice não visitado de menor distância acumulada e reconstrói a rota ótima pelo vetor `anterior[]`.
  - Em [`Grafo/rede_social.c`](../Grafo/rede_social.c), conexões simétricas são registradas em `matriz[u][v] = matriz[v][u] = 1`; `grauSeparacaoBFS` utiliza uma fila FIFO para explorar os níveis de amizade em largura, garantindo a menor distância em número de arestas.
- **Complexidade:**
  - **Tempo:** Dijkstra: $O(V^2 + E)$; BFS (graus de separação): $O(V^2)$ em matriz de adjacência; Amigos em comum: $O(V)$.
  - **Espaço:** $O(V + E)$ na lista de adjacência (`Entregas.c`) e $O(V^2)$ na matriz (`rede_social.c`).

#### Situação Problema 11 – Roteamento de Entrega de Mercadorias (`Grafo/Entregas.c`)
- **Cenário e Entrada:** Opção `4` — Simulação com 10 bairros/pontos de entrega e cálculo de rotas mínimas com Dijkstra entre diferentes pares de pontos.
- **Saída Observada:**
```text
[DIJKSTRA] Menor rota de 'CD Central' ate 'Campus Universitario':
  -> Custo minimo total: 20 km
  -> Caminho: CD Central -> Distrito Industrial -> Vila Nova -> Bela Vista -> Morumbi -> Parque das Flores -> Campus Universitario

[DIJKSTRA] Menor rota de 'CD Central' ate 'Morumbi':
  -> Custo minimo total: 13 km
  -> Caminho: CD Central -> Distrito Industrial -> Vila Nova -> Bela Vista -> Morumbi

[DIJKSTRA] Menor rota de 'Distrito Industrial' ate 'Santa Cecilia':
  -> Custo minimo total: 14 km
  -> Caminho: Distrito Industrial -> Vila Nova -> Sao Jose -> Santa Cecilia
```

#### Situação Problema 12 – Rede de Amizades em uma Rede Social Simples (`Grafo/rede_social.c`)
- **Cenário e Entrada:** Opção `6` — Simulação com 15 usuários conectados, listagem de amigos, amigos em comum, sugestões de conexão e cálculo de graus de separação via BFS.
- **Saída Observada:**
```text
Amigos em comum entre Ana e Bruno:
  - Carla

Amigos em comum entre Elisa e Fabio:
  - Heitor

Sugestoes de amizade para Ana (amigos de amigos):
  - Elisa (1 amigo(s) em comum)
  - Fabio (1 amigo(s) em comum)
  - Gabriela (1 amigo(s) em comum)

[BFS] Grau de separacao entre Ana e Heitor: 3 grau(s)
  -> Cadeia de conexao: Ana -> Bruno -> Elisa -> Heitor

[BFS] Grau de separacao entre Ana e Olivia: 6 grau(s)
  -> Cadeia de conexao: Ana -> Daniel -> Gabriela -> Isabela -> Karen -> Marina -> Olivia
```

---

### 3.4 Tabela Hash (Hash Table) — `Tabela_Hash/`

- **Justificativa de Escolha:** A tabela hash oferece inserção, busca e remoção em tempo constante médio $O(1)$ a partir de uma chave textual (e-mail de usuário ou palavra de um texto), sem necessitar manter os dados ordenados.
- **Funcionamento Interno:** Ambos os programas utilizam função de espalhamento polinomial modular (base 31) e **tratamento de colisões por encadeamento externo** (listas encadeadas em cada bucket). Em [`Tabela_Hash/login.c`](../Tabela_Hash/login.c), a senha é convertida em hash numérico via algoritmo DJB2 (`gerarHashSenha`) e tanto `autenticar` quanto `removerUsuario` calculam `idx = funcaoHash(email)` para acessar diretamente o bucket correspondente em $O(1)$ médio. Em [`Tabela_Hash/frequencia.c`](../Tabela_Hash/frequencia.c), cada palavra é normalizada para minúsculas sem pontuação e sua contagem é incrementada no bucket correspondente.
- **Complexidade:**
  - **Tempo:** Inserção, busca/autenticação e remoção: $O(1)$ no caso médio e $O(n)$ no pior caso (colisão total); processamento de texto com $N$ palavras: $O(N)$ médio.
  - **Espaço:** $O(M + N)$, onde $M$ é o número de buckets e $N$ o número de chaves distintas armazenadas.

#### Situação Problema 13 – Cadastro de Usuários com Login Rápido (`Tabela_Hash/login.c`)
- **Cenário e Entrada:** Opção `5` — Simulação com 20 usuários cadastrados em 11 buckets (gerando colisões tratadas por encadeamento), testes de autenticação válida, senha incorreta, usuário inexistente e remoção de conta.
- **Saída Observada:**
```text
Total de usuarios ativos: 20 | Buckets com colisao encadeada: 6

--- Testes de Autenticacao (Login O(1)) ---
1. Login valido (ana.lima@empresa.com / Senha#01): SUCESSO
2. Login em bucket com colisao (victor.braga@empresa.com / Senha#20): SUCESSO
3. Senha incorreta (ana.lima@empresa.com / errada123): FALHA (Esperado)
4. Usuario inexistente (nao.existe@empresa.com / 123): FALHA (Esperado)

--- Teste de Remocao de Conta ---
[REMOCAO] Conta 'carla.alves@empresa.com' removida com sucesso do bucket 9!
5. Login apos remocao (carla.alves@empresa.com): FALHA (Conta removida)
```

#### Situação Problema 14 – Contagem de Frequência de Palavras em um Texto (`Tabela_Hash/frequencia.c`)
- **Cenário e Entrada:** Opção `2` — Processamento de um artigo técnico real sobre estruturas de dados e tabelas hash.
- **Saída Observada:**
```text
--- RELATORIO DE FREQUENCIA DE PALAVRAS ---
Total de palavras processadas : 94
Total de palavras distintas   : 56

Top 12 palavras mais frequentes:
   1º de                 -> 10 ocorrencia(s)
   2º e                  -> 5 ocorrencia(s)
   3º hash               -> 5 ocorrencia(s)
   4º dados              -> 4 ocorrencia(s)
   5º tabela             -> 4 ocorrencia(s)
   6º a                  -> 3 ocorrencia(s)
   7º em                 -> 3 ocorrencia(s)
   8º uma                -> 3 ocorrencia(s)
   9º chaves             -> 2 ocorrencia(s)
  10º estrutura          -> 2 ocorrencia(s)
  11º na                 -> 2 ocorrencia(s)
  12º palavras           -> 2 ocorrencia(s)
```

---

## 4. Algoritmos de Ordenação

### 4.1 Bubble Sort — `java(Cássio)/bubblesort/`

- **Justificativa de Escolha:** Algoritmo estável, *in-place* e de implementação simples, adequado para conjuntos pequenos (notas de uma turma de até 30 alunos ou vitrine de 12 produtos) e para análise didática de comparações e trocas.
- **Funcionamento e Complexidade:** Compara elementos adjacentes e realiza trocas quando fora de ordem, interrompendo antecipadamente se uma passagem terminar sem trocas. Tempo: $O(n)$ no melhor caso (já ordenado) e $O(n^2)$ no caso médio e pior caso. Espaço auxiliar: $O(1)$.

#### Situação Problema 15 – Ordenação de Notas de uma Turma Pequena (`bubblesort.NotasTurma`)
- **Saída Observada (20 alunos, comparação com Insertion Sort):**
```text
Média da turma (independente da ordenação): 5,05
Estatísticas do Bubble Sort:    Comparações: 184 | Trocas: 87
Estatísticas do Insertion Sort: Comparações: 106 | Deslocamentos: 87
Comparações a menos com Insertion Sort: 78
```

#### Situação Problema 16 – Ordenação de Produtos por Preço em uma Vitrine Pequena (`bubblesort.ProdutosPreco`)
- **Saída Observada (12 produtos em ordem crescente e decrescente):**
```text
Preços crescentes:  Cabo HDMI (R$ 32,50), Adaptador (R$ 39,90), ..., Monitor (R$ 899,90)
Preços decrescentes: Monitor (R$ 899,90), Microfone (R$ 250,00), ..., Cabo HDMI (R$ 32,50)
```

---

### 4.2 Selection Sort — `Selection_Sort/`

- **Justificativa de Escolha:** Embora realize $O(n^2)$ comparações, o Selection Sort executa no máximo $n - 1$ trocas ($O(n)$ escritas). É indicado quando se deseja selecionar diretamente os maiores/menores elementos (Top-N candidatos) ou organizar listas pequenas de tarefas diárias minimizando movimentações de registros.
- **Funcionamento e Complexidade:** A cada posição $i$, localiza o índice do maior (ou menor) elemento em $[i..n-1]$ e efetua uma única troca com a posição $i$. Tempo: $O(n^2)$ no melhor, médio e pior casos. Trocas: $O(n)$. Espaço auxiliar: $O(1)$.

#### Situação Problema 17 – Seleção dos Melhores Candidatos em um Processo Seletivo (`Selection_Sort/processo_seletivo.c`)
- **Cenário e Entrada:** Opção `3` — Simulação com 15 candidatos e extração dos Top-5 classificados.
- **Saída Observada:**
```text
--- SELECIONADOS (TOP-5) ---
[APROVADO 1º] Elisa Sousa            | Pontuacao: 95.00
[APROVADO 2º] Isabela Dias           | Pontuacao: 93.50
[APROVADO 3º] Bruno Costa            | Pontuacao: 91.00
[APROVADO 4º] Lucas Martins          | Pontuacao: 90.00
[APROVADO 5º] Nicolas Freitas        | Pontuacao: 89.00
Estatisticas do Selection Sort: 105 comparacoes e 12 trocas realizadas.
```

#### Situação Problema 18 – Organização de Tarefas por Prioridade (`Selection_Sort/tarefas.c`)
- **Cenário e Entrada:** Opção `3` — Simulação de um dia de trabalho com 14 tarefas ordenadas pelo nível de prioridade (1 = Urgente a 5 = Baixa).
- **Saída Observada:**
```text
--- TAREFAS REORGANIZADAS POR PRIORIDADE (SELECTION SORT) (14 tarefas) ---
 1. [Prioridade 1] Corrigir falha critica no servidor de producao
 2. [Prioridade 1] Aplicar patch de seguranca no banco de dados
 3. [Prioridade 1] Restaurar backup de contingencia
 4. [Prioridade 2] Reuniao de alinhamento diario (Daily Scrum)
...
14. [Prioridade 5] Limpar logs temporarios de homologacao
Estatisticas: 91 comparacoes e 8 trocas realizadas.
```

---

### 4.3 Insertion Sort — `java(Cássio)/insertionsort/`

- **Justificativa de Escolha:** Extremamente eficiente para entradas pequenas, incrementais (mão de cartas recebidas uma a uma) ou quase ordenadas (atualização diária de ranking), atingindo tempo linear $O(n)$ no melhor caso e mantendo estabilidade.
- **Funcionamento e Complexidade:** Insere cada novo elemento na posição correta do prefixo já ordenado deslocando os maiores para a direita. Tempo: $O(n)$ no melhor caso e $O(n^2)$ no caso médio e pior caso. Espaço auxiliar: $O(1)$.

#### Situação Problema 19 – Inserção de Novas Cartas em um Jogo de Cartas Ordenado (`insertionsort.JogoCartas`)
- **Saída Observada (13 cartas inseridas uma a uma):**
```text
Mão final após a 13ª carta (6 de Copas):
A de Espadas, 2 de Espadas, 3 de Paus, 4 de Espadas, 5 de Copas, 6 de Copas,
7 de Copas, 8 de Ouros, 9 de Paus, 10 de Ouros, J de Paus, Q de Ouros, K de Copas
```

#### Situação Problema 20 – Atualização de Ranking de Vendedores do Mês (`insertionsort.RankingVendedores`)
- **Saída Observada (10 vendedores ao longo de 7 dias + comparação de desempenho):**
```text
Dia 7 - 1º lugar: Isabela Dias (R$ 4.259,50) | 2º lugar: Bruno Costa (R$ 4.127,50)
ranking já ordenado: 9 comparações observadas.
ranking embaralhado (semente 42): 31 comparações observadas.
```

---

### 4.4 Merge Sort — `java(Cássio)/mergesort/`

- **Justificativa de Escolha:** Algoritmo de divisão e conquista com garantia estrita de tempo $O(n \log n)$ mesmo no pior caso e estabilidade natural (preservando a ordem de registro de transações bancárias ocorridas no mesmo minuto). Além disso, sua etapa de intercalação (`merge`) combina listas já ordenadas em tempo linear $O(n + m)$.
- **Funcionamento e Complexidade:** Divide o vetor ao meio recursivamente e intercala as metades ordenadas com apoio de um vetor auxiliar. Tempo: $O(n \log n)$ em todos os casos; intercalação direta: $O(n + m)$. Espaço auxiliar: $O(n)$.

#### Situação Problema 21 – Ordenação de Histórico de Transações Bancárias (`mergesort.TransacoesBancarias`)
- **Saída Observada (50 transações ordenadas preservando ordem de registro em horários idênticos):**
```text
01/08/2026 08:00 - R$ 25,00 - PIX recebido #1
01/08/2026 08:00 - R$ -500,00 - Pagamento de compra #26
...
02/08/2026 08:00 - R$ 371,00 - PIX recebido #23
02/08/2026 08:00 - R$ -246,00 - Pagamento de compra #48
```

#### Situação Problema 22 – Mesclagem de Duas Listas de Contatos Ordenadas (`mergesort.MesclagemContatos`)
- **Saída Observada (20 contatos do Depto. A + 20 contatos do Depto. B, com 10 nomes em comum):**
```text
Contatos mesclados sem duplicatas (30):
Alice Teixeira, Ana Lima, Bernardo Castro, ..., Victor Braga
Total resultante: 30 (esperado nesta base: 30).
```

---

### 4.5 Quick Sort — `Quick_Sort/`

- **Justificativa de Escolha:** É o algoritmo de ordenação de propósito geral mais rápido na prática em memória principal ($O(n \log n)$ no caso médio, constantes pequenas e uso de memória auxiliar restrito à pilha de recursão $O(\log n)$). Em [`Quick_Sort/ecommerce.c`](../Quick_Sort/ecommerce.c), a escolha de pivô por **mediana-de-três** evita a degradação para $O(n^2)$ em entradas já ordenadas.
- **Funcionamento e Complexidade:** Seleciona um pivô (mediana entre `low`, `mid` e `high`), particiona o subvetor colocando elementos menores/iguais à esquerda e maiores à direita, e ordena recursivamente as partições. Tempo: $O(n \log n)$ no melhor e médio casos, $O(n^2)$ no pior caso. Espaço auxiliar: $O(\log n)$.

#### Situação Problema 23 – Ordenação de Catálogo de Produtos de E-commerce (`Quick_Sort/ecommerce.c`)
- **Cenário e Entrada:** Opção `3` — Simulação com **100 produtos**, ordenação por três critérios distintos (Preço crescente, Nome A-Z e Popularidade decrescente) e benchmark comparativo entre **Quick Sort (Mediana-de-Três)** e **Merge Sort**.
- **Saída Observada:**
```text
--- ORDENADO POR PRECO CRESCENTE (QUICK SORT MEDIANA-DE-TRES) (100 produtos) ---
  1. [ID  79] Mouse Modelo 024         | R$    57.10 | Popularidade: 571
  2. [ID  53] Mouse Modelo 062         | R$   195.70 | Popularidade: 695
...
[COMPARACAO QUICK SORT vs MERGE SORT (100 produtos por preco)]
  -> Quick Sort (Mediana-de-3): ~650 comparacoes, ~380 trocas
  -> Merge Sort               : ~542 comparacoes
(Também ordena e exibe o catálogo por Nome Alfabético e por Popularidade Decrescente)
```

#### Situação Problema 24 – Classificação de Resultados de uma Competição Esportiva (`Quick_Sort/competicao.c`)
- **Cenário e Entrada:** Opção `3` — Simulação de corrida de 100m rasos com **30 atletas**, geração da classificação final e destaque do **Pódio (Top 3)**.
- **Saída Observada:**
```text
=================== PODIO OFICIAL (TOP 3) ===================
  [OURO   - 1º Lugar] Victor Braga           | Tempo: 9.91 s
  [PRATA  - 2º Lugar] Heitor Melo            | Tempo: 9.98 s
  [BRONZE - 3º Lugar] Lucas Martins          | Tempo: 10.05 s
=============================================================
--- CLASSIFICACAO FINAL COMPLETA (30 ATLETAS) ---
 1º Lugar: Victor Braga           | Tempo: 9.91 s
...
30º Lugar: Karen Ribeiro          | Tempo: 12.45 s
```

---

## 5. Síntese de Complexidade, Dificuldades e Conclusão Geral

| Categoria | Estrutura / Algoritmo | Complexidade de Tempo (Melhor / Médio / Pior) | Espaço Auxiliar | Principais Casos de Uso no Projeto |
|---|---|---|---|---|
| **2.1** | **Fila Circular** | $O(1) / O(1) / O(1)$ | $O(1)$ | Atendimento por ordem de chegada (Clínica e Impressão) |
| **2.2** | **Pilha (LIFO)** | $O(1) / O(1) / O(1)$ | $O(1)$ | Reversão de histórico (Undo/Redo) e validação de delimitadores |
| **2.3** | **Lista Encadeada** | $O(1)$ início / $O(n)$ busca e meio | $O(n)$ dinâmico | Coleções com inserções/remoções dinâmicas (Playlist e Estoque) |
| **3.1** | **Árvore BST** | $O(\log n) / O(\log n) / O(n)$ | $O(h)$ | Índices ordenados e busca por prefixo (Alunos e Autocomplete) |
| **3.2** | **Árvore AVL** | $O(\log n) / O(\log n) / O(\log n)$ | $O(\log n)$ | Índices com garantia de pior caso e Top-K (CPF e Ranking) |
| **3.3** | **Grafos (Dijkstra / BFS)** | Dijkstra $O(V^2+E)$; BFS $O(V^2)$ | $O(V+E)$ / $O(V^2)$ | Menor rota logística e graus de separação em rede social |
| **3.4** | **Tabela Hash** | $O(1) / O(1) / O(n)$ | $O(M + N)$ | Autenticação rápida por chave e contagem de frequência em texto |
| **4.1** | **Bubble Sort** | $O(n) / O(n^2) / O(n^2)$ | $O(1)$ | Ordenação simples e estável de pequenas amostras (Notas e Vitrine) |
| **4.2** | **Selection Sort** | $O(n^2) / O(n^2) / O(n^2)$ | $O(1)$ | Minimização de trocas $O(n)$ e seleção Top-N (Seletivo e Tarefas) |
| **4.3** | **Insertion Sort** | $O(n) / O(n^2) / O(n^2)$ | $O(1)$ | Inserção incremental e listas quase ordenadas (Cartas e Vendedores) |
| **4.4** | **Merge Sort** | $O(n \log n)$ em todos os casos | $O(n)$ | Estabilidade garantida e mesclagem $O(n+m)$ (Extrato e Contatos) |
| **4.5** | **Quick Sort** | $O(n \log n) / O(n \log n) / O(n^2)$ | $O(\log n)$ | Ordenação rápida em memória para catálogos e rankings esportivos |

### Dificuldades Encontradas e Soluções Adotadas
1. **Aritmética circular no cancelamento da Fila:** Ao implementar o cancelamento do último trabalho de impressão na fila circular, foi necessário tratar o recuo de `fim = 0` usando `(fim - 1 + elementos.length) % elementos.length`.
2. **Empates de pontuação na Árvore AVL:** Como árvores de busca não duplicam chaves, o ranking de jogadores combinou a pontuação formatada em 10 dígitos com o nome do jogador (`%010d:%s`), preservando todos os jogadores empatados.
3. **Colisões e busca $O(1)$ na Tabela Hash:** Na autenticação de usuários, garantiu-se que o login e a remoção calculem diretamente `funcaoHash(email)` para percorrer apenas a lista encadeada do bucket correspondente, além de armazenar o hash da senha (DJB2).
4. **Estabilidade e escolha de pivô nas ordenações:** No Merge Sort e no Insertion Sort, o uso de `<= 0` preservou a ordem relativa de transações no mesmo minuto; no Quick Sort, a mediana-de-três evitou o pior caso em listas ordenadas.

### Conclusão
O desenvolvimento das 24 situações-problema demonstrou na prática que nenhuma estrutura de dados ou algoritmo de ordenação é universalmente superior: a escolha técnica correta depende do padrão de acesso (FIFO, LIFO, busca por chave exata, busca por prefixo/intervalo ou travessia de caminhos), do volume de dados e das garantias exigidas de estabilidade, memória e tempo no pior caso.
