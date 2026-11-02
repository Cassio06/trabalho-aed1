# Relatório Técnico — Estruturas de Dados e Algoritmos de Ordenação (Parte Java)

## Identificação

- **Curso / Turma:** Engenharia de Software — ADELLE / SNYDER (Preencher na ficha obrigatória)
- **Período:** 1º Período (2026.2)
- **Aluno 1 / matrícula:** Cássio Filipe Meireles De Carvalho Braga — [Preencher matrícula]
- **Aluno 2 / matrícula:** Lukas Souza Melo — [Preencher matrícula]
- **Professor:** Hilson Silva
- **Data:** 02/11/2026
- **JDK / sistema operacional usado nos testes:** OpenJDK 25.0.4.1 (`--release 17`) / Windows 11 + Git Bash
- **Responsável por estas seis estruturas e 12 aplicações (Java):** Cássio Filipe Meireles De Carvalho Braga

---

## Escopo e método de verificação

O trabalho completo abrange 12 categorias e 24 situações-problema. Na divisão da dupla, esta parte em **Java puro** implementa 6 categorias e 12 aplicações de console: **Fila**, **Bubble Sort**, **Insertion Sort**, **Árvore Binária de Busca (BST)**, **Merge Sort** e **Árvore AVL**. Todas as estruturas e algoritmos foram construídos do zero sem uso de coleções prontas (`java.util.Queue`, `TreeMap`, `Arrays.sort`, `Collections.sort`), utilizando apenas arrays nativos e referências encadeadas.

A verificação automatizada é executada pelo script `bash verificar.sh`, que compila todos os arquivos `.java` com `-encoding UTF-8 --release 17 -Xlint:all` e executa 7 suítes de testes (`apoio.TesteApoio`, `fila.TesteFila`, `bubblesort.TesteBubbleSort`, `insertionsort.TesteInsertionSort`, `bst.TesteBST`, `mergesort.TesteMergeSort` e `avl.TesteAVL`), totalizando **107 casos de teste aprovados (`[OK]`), 0 pendentes e 0 falhas**.

---

## 1. Fila (`fila`)

### Aplicação 1: Sistema de Atendimento de uma Clínica Médica (`fila.Clinica`)

- **Classe de execução:** `fila.Clinica`
- **Cenário documentado:** Simulação de um dia de atendimento (início às `08:00`, duração estimada de 10 minutos por paciente) com 15 pacientes chegando a cada 7 minutos a partir das `08:05`.
- **Entradas utilizadas:** Modo `1` (Simular 15 pacientes) → Opção `5` (Atender todos) → Opção `0` (Sair e exibir relatório).
- **Resultado esperado e justificativa:** Como os pacientes chegam a cada 7 minutos e cada consulta dura 10 minutos, o primeiro paciente (`Ana Lima`, chegada `08:05`) é atendido imediatamente (`0 min` de espera), e cada paciente seguinte acumula `+3 min` de espera (`0, 3, 6, ..., 42 min`), resultando em uma espera média exata de `21,00 min`, preservando rigorosamente a ordem FIFO.
- **Saída realmente observada (`java -cp out fila.Clinica` em 02/11/2026):**

```text
Clínica: atendimento FIFO, estimativa de 10 minutos por paciente.
Chegadas (mesmo dia, em ordem de registro):
Ana Lima - chegada: 08:05 - atendimento: Consulta
Bruno Costa - chegada: 08:12 - atendimento: Exame
...
Olivia Gomes - chegada: 09:43 - atendimento: Retorno

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

### Aplicação 2: Fila de Impressão em Laboratório de Informática (`fila.FilaImpressao`)

- **Classe de execução:** `fila.FilaImpressao`
- **Cenário documentado:** Fila com 12 trabalhos iniciais (75 páginas no total), cancelamento do último trabalho enviado (`Lucas - seminario.pdf - 9 páginas`) e impressão dos 11 restantes.
- **Entradas utilizadas:** Opção `6` (Cancelar último) → Opção `5` (Imprimir todos) → Opção `0` (Sair e gerar relatório).
- **Resultado esperado e justificativa:** O cancelamento remove apenas o último trabalho inserido ainda pendente (`Lucas`, 9 páginas), mantendo os 11 anteriores em ordem de chegada e totalizando `75 - 9 = 66` páginas impressas.
- **Saída realmente observada (`java -cp out fila.FilaImpressao` em 02/11/2026):**

```text
Simulação: 12 trabalhos de impressão.
Último trabalho aguardando cancelado: Lucas - seminario.pdf - 9 página(s)
1 - Imprimindo: Ana - algoritmos.pdf - 8 página(s)
2 - Imprimindo: Bruno - resumo.docx - 3 página(s)
...
11 - Imprimindo: Karen - tabela.pdf - 3 página(s)
Relatório: 11 trabalho(s), 66 página(s). A sequência efetiva foi exibida a cada impressão.
```

### Registro de verificações deste módulo (`fila.TesteFila` — 16 OK)

| Caso / entrada | Resultado esperado | Resultado observado | Status |
|---|---|---|---|
| Caso normal (15 pacientes / 12 trabalhos) | Ordem FIFO preservada | Ordem FIFO preservada | OK |
| Estrutura vazia (`dequeue`, `front`, `removerUltimo`) | Lança `NoSuchElementException` | Lança `NoSuchElementException` | OK |
| Reutilização circular e capacidade máxima (20) | Reaproveita índices com aritmética modular; cheia lança `IllegalStateException` | Índices circulares validados sem perda de elementos | OK |
| Cancelamento do último (`removerUltimo`) | Remove o mais recente pendente sem afetar a ordem FIFO dos demais | Removido corretamente inclusive após wrap-around | OK |

### Análise técnica da Fila

- **Justificativa:** A Fila (FIFO — *First-In, First-Out*) garante justiça e previsibilidade no atendimento ambulatorial e no spooler de impressão, processando cada solicitação na ordem exata de chegada.
- **Funcionamento:** Implementada sobre um vetor circular (`Object[20]`) controlado pelos ponteiros `inicio`, `fim` e pelo contador `quantidade`. Avanços utilizam `(indice + 1) % elementos.length`, e o cancelamento do último pendente recua `fim` com `(fim - 1 + elementos.length) % elementos.length`.
- **Complexidade de tempo:** `enqueue`: $O(1)$; `dequeue`: $O(1)$; `front`: $O(1)$; `removerUltimo`: $O(1)$; `isEmpty` / `size`: $O(1)$; `listar`: $O(n)$.
- **Complexidade de espaço:** $O(N)$ fixo para a capacidade máxima do array circular ($N = 20$), com uso auxiliar $O(1)$ por operação.
- **Dificuldades e soluções:** Garantir o recuo correto do índice `fim` no cancelamento quando `fim == 0` após a volta circular; resolvido somando `elementos.length` antes do operador módulo.
- **Conclusão:** O array circular oferece todas as operações fundamentais da fila em tempo constante $O(1)$ sem necessidade de deslocar elementos na memória.

---

## 2. Bubble Sort (`bubblesort`)

### Aplicação 15: Ordenação de Notas de uma Turma Pequena (`bubblesort.NotasTurma`)

- **Classe de execução:** `bubblesort.NotasTurma`
- **Cenário documentado:** Ordenação crescente de 20 notas de alunos, cálculo da média da turma e comparação do número de comparações/trocas com o Insertion Sort.
- **Entradas utilizadas:** Modo `1` (Simular 20 notas).
- **Resultado esperado e justificativa:** As 20 notas (de `0.0` a `10.0`) devem ficar em ordem crescente com média `5,05`. O Bubble Sort com parada antecipada realiza mais comparações que o Insertion Sort porque varre o sufixo não ordenado a cada passagem, enquanto realiza o mesmo número de trocas/deslocamentos (igual ao número de inversões do vetor).
- **Saída realmente observada (`java -cp out bubblesort.NotasTurma` em 02/11/2026):**

```text
Média da turma (independente da ordenação): 5,05
Notas em ordem crescente:
Ana Lima - nota: 0.0
Nicolas Freitas - nota: 0.5
...
Rafaela Torres - nota: 9.5
Isabela Dias - nota: 10.0

Estatísticas do Bubble Sort:
Comparações: 184
Trocas: 87

Estatísticas do Insertion Sort:
Comparações: 106
Deslocamentos: 87

Comparação entre os algoritmos:
Comparações a menos com Insertion Sort: 78
```

### Aplicação 16: Ordenação de Produtos por Preço em uma Vitrine Pequena (`bubblesort.ProdutosPreco`)

- **Classe de execução:** `bubblesort.ProdutosPreco`
- **Cenário documentado:** Ordenação de 12 produtos de uma vitrine virtual por preço crescente (`1`) e decrescente (`2`).
- **Entradas utilizadas:** Opção `1` (Preço crescente) e Opção `2` (Preço decrescente).
- **Saída realmente observada (`java -cp out bubblesort.ProdutosPreco` em 02/11/2026):**

```text
Preços crescentes:
Cabo HDMI - R$ 32,50
Adaptador - R$ 39,90
Pendrive - R$ 44,90
...
Microfone - R$ 250,00
Monitor - R$ 899,90

Preços decrescentes:
Monitor - R$ 899,90
Microfone - R$ 250,00
...
Adaptador - R$ 39,90
Cabo HDMI - R$ 32,50
```

### Registro de verificações deste módulo (`bubblesort.TesteBubbleSort` — 13 OK)

| Caso / entrada | Resultado esperado | Resultado observado | Status |
|---|---|---|---|
| Caso normal (20 notas / 12 produtos) | Ordenado crescente/decrescente; 184 comparações e 87 trocas | Ordenado corretamente; 184 comp. e 87 trocas | OK |
| Vetor vazio e unitário | 0 comparações e 0 trocas | 0 comparações e 0 trocas | OK |
| Valores repetidos / empates | Ordem relativa original preservada (estável) | Estabilidade preservada | OK |
| Entrada já ordenada | Parada antecipada na 1ª passagem ($n - 1$ comparações, 0 trocas) | Parada antecipada confirmada | OK |

### Análise técnica do Bubble Sort

- **Justificativa:** Adequado para coleções muito pequenas (turma de até 30 alunos ou vitrine de 12 itens), onde a simplicidade de código, a ordenação *in-place* e a estabilidade superam a necessidade de desempenho assintótico.
- **Funcionamento:** Compara pares adjacentes `(j, j + 1)` e troca-os apenas quando `comparador.compare(a, b) > 0`. Uma flag booleana `trocou` interrompe o laço externo caso nenhuma troca ocorra na passagem.
- **Complexidade de tempo:** Melhor caso (já ordenado): $O(n)$ com parada antecipada; Caso médio e pior caso (ordem inversa): $O(n^2)$.
- **Complexidade de espaço:** $O(1)$ de memória auxiliar (ordenação *in-place*).
- **Dificuldades e soluções:** Preservar a estabilidade usando comparação estrita (`> 0`) e instrumentar as contagens de comparações e trocas sem interferir na lógica do algoritmo.
- **Conclusão:** A parada antecipada reduz o melhor caso para $O(n)$, mas em vetores desordenados o Insertion Sort realizou 78 comparações a menos sobre a mesma base de 20 notas.

---

## 3. Insertion Sort (`insertionsort`)

### Aplicação 19: Inserção de Novas Cartas em um Jogo de Cartas Ordenado (`insertionsort.JogoCartas`)

- **Classe de execução:** `insertionsort.JogoCartas`
- **Cenário documentado:** Recebimento incremental de 13 cartas (`K de Copas`, `3 de Paus`, `A de Espadas`, ..., `6 de Copas`), exibindo a mão ordenada após cada nova carta recebida.
- **Saída realmente observada (`java -cp out insertionsort.JogoCartas` em 02/11/2026):**

```text
Recebimento de 13 cartas. Ás vale 1; desempate por naipe.
...
Recebida: 6 de Copas
Mão após a inserção:
A de Espadas, 2 de Espadas, 3 de Paus, 4 de Espadas, 5 de Copas, 6 de Copas,
7 de Copas, 8 de Ouros, 9 de Paus, 10 de Ouros, J de Paus, Q de Ouros, K de Copas
```

### Aplicação 20: Atualização de Ranking de Vendedores do Mês (`insertionsort.RankingVendedores`)

- **Classe de execução:** `insertionsort.RankingVendedores`
- **Cenário documentado:** Simulação de 10 vendedores ao longo de 7 dias com atualização diária do ranking e comparação de desempenho entre lista já ordenada e lista embaralhada (semente 42).
- **Saída realmente observada (`java -cp out insertionsort.RankingVendedores` em 02/11/2026):**

```text
Dia 7 da semana (totais acumulados):
Ranking atualizado:
1º - Isabela Dias - total vendido: R$ 4.259,50
2º - Bruno Costa - total vendido: R$ 4.127,50
3º - Joao Silva - total vendido: R$ 4.091,50
...
10º - Daniel Rocha - total vendido: R$ 3.191,50
ranking já ordenado: 9 comparações observadas.
ranking embaralhado (semente 42): 31 comparações observadas.
```

### Registro de verificações deste módulo (`insertionsort.TesteInsertionSort` — 12 OK)

| Caso / entrada | Resultado esperado | Resultado observado | Status |
|---|---|---|---|
| Caso normal (13 cartas / 10 vendedores) | Mão ordenada a cada carta; ranking atualizado nos 7 dias | Ordenação confirmada em todos os passos | OK |
| Vetor vazio e unitário | 0 comparações e 0 deslocamentos | 0 comparações e 0 deslocamentos | OK |
| Valores repetidos / empates | Ordem relativa mantida (estável) | Estabilidade preservada | OK |
| Entrada já ordenada vs. embaralhada (n=10) | 9 comparações (ordenada) vs. 31 comparações (embaralhada) | 9 vs. 31 comparações confirmadas | OK |

### Análise técnica do Insertion Sort

- **Justificativa:** Ideal para dados recebidos de forma incremental (mão de cartas) ou listas que sofrem pequenas atualizações diárias a partir de uma ordem prévia (ranking de vendedores).
- **Funcionamento:** Para cada posição `i` de `1` a `n - 1`, armazena `chave = elementos[i]` e desloca para a direita todos os elementos anteriores maiores que `chave`, inserindo-a na posição correta `j + 1`.
- **Complexidade de tempo:** Melhor caso (já ordenado): $O(n)$ ($n - 1$ comparações e $0$ deslocamentos); Caso médio e pior caso: $O(n^2)$.
- **Complexidade de espaço:** $O(1)$ auxiliar (*in-place*).
- **Dificuldades e soluções:** Contabilizar com precisão a comparação que encerra o laço `while` quando `comparador.compare(elementos[j], chave) <= 0`.
- **Conclusão:** A experiência prática comprovou a eficiência adaptativa do Insertion Sort: na lista de 10 vendedores já ordenada foram necessárias apenas 9 comparações ($n - 1$), contra 31 na lista embaralhada.

---

## 4. Árvore Binária de Busca — BST (`bst`)

### Aplicação 7: Cadastro e Busca de Alunos por Matrícula (`bst.CadastroAlunos`)

- **Classe de execução:** `bst.CadastroAlunos`
- **Cenário documentado:** Cadastro inicial de 20 alunos (matrículas `1001` a `1020` inseridas fora de ordem), busca pela matrícula `1001`, remoção da matrícula `1008` e listagem ordenada (percurso em-ordem).
- **Entradas utilizadas:** `2` (Buscar `1001`) → `3` (Remover `1008`) → `4` (Listar em ordem) → `0` (Sair).
- **Saída realmente observada (`java -cp out bst.CadastroAlunos` em 02/11/2026):**

```text
Base inicial: 20 alunos.
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

### Aplicação 8: Sistema de Autocomplete de Nomes de Produtos (`bst.AutocompleteProdutos`)

- **Classe de execução:** `bst.AutocompleteProdutos`
- **Cenário documentado:** Catálogo com 30 produtos de papelaria; teste de autocomplete para o prefixo `"ca"` e para prefixo inexistente `"xyz"`.
- **Entradas utilizadas:** `2` (Prefixo `ca`) → `2` (Prefixo `xyz`) → `0` (Sair).
- **Saída realmente observada (`java -cp out bst.AutocompleteProdutos` em 02/11/2026):**

```text
Catálogo inicial: 30 produtos.
Prefixo: Sugestões para ca (nenhuma linha se não houver):
Caderno
Calculadora
Caneta Azul
Caneta Preta
Caneta Vermelha
Cartolina

Prefixo: Sugestões para xyz (nenhuma linha se não houver):
```

### Registro de verificações deste módulo (`bst.TesteBST` — 14 OK)

| Caso / entrada | Resultado esperado | Resultado observado | Status |
|---|---|---|---|
| Caso normal (20 matrículas / 30 produtos) | Busca, remoção e listagem em-ordem corretas | Todos os itens retornados em ordem | OK |
| Árvore vazia | Busca/remoção retornam `null`; percurso não imprime | `null` e saída vazia confirmados | OK |
| Chave repetida | Atualiza o valor associado sem duplicar nó | Valor atualizado na mesma chave | OK |
| Remoção de folha, 1 filho, 2 filhos e raiz | Substituição pelo sucessor em-ordem mantendo propriedade BST | Árvore íntegra após remoções | OK |

### Análise técnica da BST

- **Justificativa:** Mantém o cadastro de alunos e o catálogo de produtos dinamicamente ordenados, permitindo buscas pontuais, remoções e consultas por intervalo/prefixo sem reordenar um vetor a cada inserção.
- **Funcionamento:** Cada nó possui `chave`, `valor`, `esquerda` e `direita`. Na remoção de nó com dois filhos, substitui-se o par chave/valor pelo menor nó da subárvore direita (`menorNo(atual.direita)`). O `listarPorPrefixo` realiza poda: só visita a esquerda se `chaveAtual.compareTo(prefixo) > 0` e só visita a direita se `chaveAtual.compareTo(prefixo) < 0 || chaveAtual.startsWith(prefixo)`.
- **Complexidade de tempo:** Inserção, busca e remoção: $O(\log n)$ no caso médio e $O(n)$ no pior caso (árvore degenerada). Percurso em-ordem: $O(n)$.
- **Complexidade de espaço:** $O(n)$ para os $n$ nós armazenados e $O(h)$ na pilha de recursão, onde $h$ é a altura da árvore.
- **Dificuldades e soluções:** Evitar varredura completa da árvore no autocomplete; solucionado com o percurso limitado pelas propriedades lexicográficas das chaves.
- **Conclusão:** A BST é simples e eficiente para buscas exatas e por prefixo quando as inserções não ocorrem em ordem estritamente monótona.

---

## 5. Merge Sort (`mergesort`)

### Aplicação 21: Ordenação de Histórico de Transações Bancárias (`mergesort.TransacoesBancarias`)

- **Classe de execução:** `mergesort.TransacoesBancarias`
- **Cenário documentado:** Ordenação cronológica de 50 transações bancárias (PIX e pagamentos), contendo múltiplos registros no mesmo instante para comprovar estabilidade.
- **Saída realmente observada (`java -cp out mergesort.TransacoesBancarias` em 02/11/2026):**

```text
Histórico recebido: 50 transações fictícias
Transações em ordem de data e hora:
01/08/2026 08:00 - R$ 25,00 - PIX recebido #1
01/08/2026 08:00 - R$ -500,00 - Pagamento de compra #26
01/08/2026 09:00 - R$ -154,00 - Pagamento de compra #4
01/08/2026 09:00 - R$ 29,00 - PIX recebido #29
...
02/08/2026 08:00 - R$ 371,00 - PIX recebido #23
02/08/2026 08:00 - R$ -246,00 - Pagamento de compra #48
```

### Aplicação 22: Mesclagem de Duas Listas de Contatos Ordenadas (`mergesort.MesclagemContatos`)

- **Classe de execução:** `mergesort.MesclagemContatos`
- **Cenário documentado:** Mesclagem direta (etapa `merge`) de duas listas já ordenadas de 20 contatos cada (Departamentos A e B), com 10 nomes em comum, gerando uma lista única ordenada de 30 contatos sem duplicatas.
- **Saída realmente observada (`java -cp out mergesort.MesclagemContatos` em 02/11/2026):**

```text
Departamento A (já ordenado) (20) / Departamento B (já ordenado) (20)
Critério: nome sem distinguir caixa. Empates mantêm o contato de A.
Contatos mesclados sem duplicatas (30):
Alice Teixeira - alice.teixeira@exemplo.com
Ana Lima - ana.lima@exemplo.com
...
Victor Braga - victor.braga@exemplo.com
Total resultante: 30 (esperado nesta base: 30).
```

### Registro de verificações deste módulo (`mergesort.TesteMergeSort` — 16 OK)

| Caso / entrada | Resultado esperado | Resultado observado | Status |
|---|---|---|---|
| Caso normal (50 transações / 20+20 contatos) | 50 transações ordenadas; 30 contatos únicos | Ordenação e deduplicação exatas | OK |
| Vetor vazio / listas vazias | Retorna vetor vazio sem exceção | Vetor de tamanho 0 retornado | OK |
| Transações no mesmo instante | Ordem de registro (#1 antes de #26 às 08:00) mantida | Estabilidade preservada | OK |
| Duplicatas entre listas e internas | `mesclarContatos` retém a 1ª ocorrência em $O(n + m)$ | Sem duplicatas e sem `null`s sobrando | OK |

### Análise técnica do Merge Sort

- **Justificativa:** Garante desempenho previsível $O(n \log n)$ mesmo no pior caso e é intrinsecamente estável, requisito essencial em relatórios financeiros e na intercalação linear de listas já ordenadas.
- **Funcionamento:** Divide recursivamente o intervalo `[inicio, fim]` ao meio e intercala as duas metades usando um único vetor auxiliar compartilhado (`auxiliar`), escolhendo o elemento da esquerda quando `comparador.compare(esq, dir) <= 0`. Em `mesclarContatos`, dois cursores (`i`, `j`) percorrem as listas ordenadas em passagem única, descartando nomes repetidos (`equalsIgnoreCase`).
- **Complexidade de tempo:** Melhor, médio e pior casos: $O(n \log n)$ para a ordenação completa; $O(n + m)$ para a mesclagem de duas listas já ordenadas.
- **Complexidade de espaço:** $O(n)$ de memória auxiliar para o vetor temporário e $O(\log n)$ na pilha de recursão.
- **Dificuldades e soluções:** Evitar duplicatas consecutivas na mesclagem mesmo quando uma mesma lista de entrada possui nomes repetidos; resolvido comparando cada item candidato com o último elemento já inserido em `resultado[quantidade - 1]`.
- **Conclusão:** O Merge Sort é imune a piores casos quadráticos e sua rotina de intercalação resolve a união deduplicada de listas ordenadas em tempo linear.

---

## 6. Árvore Balanceada — AVL (`avl`)

### Aplicação 9: Índice de CPF para Sistema de RH (`avl.IndiceCpf`)

- **Classe de execução:** `avl.IndiceCpf`
- **Cenário documentado:** Inserção de 25 funcionários com CPFs sequenciais (`731.205.100-00` a `731.205.124-68`), verificação de altura e balanceamento e busca por CPF.
- **Entradas utilizadas:** `4` (Verificar altura e balanceamento) → `2` (Buscar `731.205.100-00`) → `0` (Sair).
- **Resultado esperado e justificativa:** Enquanto uma BST comum degeneraria em uma lista de altura 25 para chaves inseridas em ordem crescente, a AVL aplica rotações automáticas e mantém os 25 funcionários em altura `5` ($\lfloor \log_2 25 \rfloor + 1 = 5$), com todos os nós balanceados (`true`).
- **Saída realmente observada (`java -cp out avl.IndiceCpf` em 02/11/2026):**

```text
Base inicial: 25 funcionários; CPFs fictícios, validação de formato.
Altura: 5
Fator da raiz: 0
Todos os nós balanceados: true
CPF: Encontrado: 731.205.100-00 - Ana Lima - Analista
```

### Aplicação 10: Ranking de Jogadores em um Jogo Online (`avl.RankingJogadores`)

- **Classe de execução:** `avl.RankingJogadores`
- **Cenário documentado:** Simulação com 30 jogadores, três atualizações de pontuação na rodada (incluindo empate em 750 pontos entre `Ana Lima` e `Fabio Santos`, e liderança de `Marina Barros` com 920 pontos) e consulta ao Top-5.
- **Entradas utilizadas:** `2` (Top-K com `K = 5`) → `4` (Altura/balanceamento) → `0` (Sair).
- **Saída realmente observada (`java -cp out avl.RankingJogadores` em 02/11/2026):**

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

Altura: 6
Fator da raiz: -1
Todos os nós balanceados: true
```

### Registro de verificações deste módulo (`avl.TesteAVL` — 15 OK)

| Caso / entrada | Resultado esperado | Resultado observado | Status |
|---|---|---|---|
| Caso normal (25 CPFs em ordem / 30 jogadores) | Altura 5 (25 nós) e Altura 6 (30 nós); `estaBalanceada() == true` | Alturas 5 e 6, 100% balanceada | OK |
| Árvore vazia | Altura 0, fator 0, busca/remoção retornam `null` | Confirmado | OK |
| Rotações LL, RR, LR e RL + remoções sucessivas | Fator de balanceamento em $[-1, 0, 1]$ em todos os nós | Confirmado por `alturaVerificada` | OK |
| Top-K com pontuações empatadas | Chave composta `%010d:%s` preserva jogadores com mesma pontuação | Empates preservados e listados no Top-K | OK |

### Análise técnica da AVL

- **Justificativa:** Garante busca, inserção e remoção em $O(\log n)$ estrito mesmo no pior caso (como a carga de CPFs em ordem crescente), impedindo a degeneração em lista encadeada.
- **Funcionamento:** Cada nó armazena sua `altura`. Após cada inserção ou remoção recursiva, `rebalancear(atual)` recalcula a altura e verifica `fator = altura(esq) - altura(dir)`. Se `fator > 1`, aplica rotação simples à direita (LL) ou dupla esquerda-direita (LR); se `fator < -1`, aplica rotação simples à esquerda (RR) ou dupla direita-esquerda (RL). O Top-K usa percurso reverso (direita → raiz → esquerda) interrompendo assim que `K` elementos são visitados.
- **Complexidade de tempo:** Inserção, busca e remoção: $O(\log n)$ no melhor, médio e pior casos; `listarMaiores(K)`: $O(\log n + K)$.
- **Complexidade de espaço:** $O(n)$ para os nós e $O(\log n)$ na pilha de recursão.
- **Dificuldades e soluções:** Representar múltiplos jogadores com a mesma pontuação na AVL sem sobrescrever nós; resolvido compondo a chave como `String.format("%010d:%s", pontuacao, nome)` e atualizando pontuações via remoção da chave antiga seguida de inserção da nova.
- **Conclusão:** A AVL comprovou na prática o controle de altura ($h = 5$ para 25 CPFs sequenciais e $h = 6$ para 30 jogadores), viabilizando consultas de índice e Top-K em tempo logarítmico garantido.

---

## Comparação e conclusão geral

| Estrutura / Algoritmo | Operação / Cenário | Tempo (Melhor / Médio / Pior) | Espaço Adicional | Evidência observada na implementação |
|---|---|---|---|---|
| **Fila Circular** | `enqueue`, `dequeue`, `front`, `removerUltimo` | $O(1) / O(1) / O(1)$ | $O(1)$ por operação | 15 pacientes atendidos em FIFO (espera média `21,00 min`) e cancelamento O(1) na impressão |
| **Bubble Sort** | Ordenação com parada antecipada | $O(n) / O(n^2) / O(n^2)$ | $O(1)$ (*in-place*) | 20 notas ordenadas com `184` comparações e `87` trocas; parada em 1 passagem quando já ordenado |
| **Insertion Sort** | Ordenação incremental / quase ordenada | $O(n) / O(n^2) / O(n^2)$ | $O(1)$ (*in-place*) | 20 notas com `106` comp. (`78` a menos que Bubble); em 10 vendedores: `9` comp. (ordenado) vs. `31` (embaralhado) |
| **BST** | `inserir`, `buscar`, `remover` | $O(\log n) / O(\log n) / O(n)$ | $O(h)$ recursão | 20 alunos ordenados por matrícula e autocomplete de 30 produtos com poda de subárvores |
| **Merge Sort** | `ordenar` e `mesclarContatos` | $O(n \log n)$ em todos os casos; mesclagem $O(n+m)$ | $O(n)$ vetor auxiliar | 50 transações ordenadas preservando ordem de registro em horários iguais; 20+20 contatos mesclados em 30 únicos |
| **AVL** | `inserir`, `buscar`, `remover`, `listarMaiores(K)` | $O(\log n) / O(\log n) / O(\log n)$ | $O(\log n)$ recursão | 25 CPFs sequenciais mantidos em altura `5` (`estaBalanceada = true`) e Top-5 de 30 jogadores em altura `6` |

---

## Referências

- Enunciado oficial: `java(Cássio)/Trabalho Avaliativo- Algorítimo e Estrutura de Dados-2P-Prof. Hilson Silva-ADELLE e SNYDER.pdf`.
- CORMEN, T. H. et al. *Algoritmos: Teoria e Prática*. 3. ed. Rio de Janeiro: Elsevier, 2012.
- SEDGEWICK, R.; WAYNE, K. *Algorithms*. 4. ed. Boston: Addison-Wesley, 2011.
