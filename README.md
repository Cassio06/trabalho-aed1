# Trabalho Prático — Algoritmos e Estruturas de Dados I (2026.2)

Implementação completa das **12 estruturas de dados e algoritmos de ordenação** aplicados às **24 situações-problema reais do cotidiano**, conforme o edital do **Prof. Hilson Silva** (Instituto de Ensino Superior iCEV — Engenharia de Software — Turmas ADELLE e SNYDER).

## Equipe (Dupla)

- **Cássio Filipe Meireles De Carvalho Braga** — 6 categorias / 12 aplicações em **Java** (`java(Cássio)/`)
- **Lukas Souza Melo** — 6 categorias / 12 aplicações em **C** (`c(Lukas)/`)

---

## Mapa Completo das 12 Categorias e 24 Situações-Problema

| # | Categoria | Situação-Problema | Linguagem | Caminho / Classe Principal |
|---|---|---|---|---|
| 1 | **Fila** | Sistema de Atendimento de uma Clínica Médica (15 pacientes) | Java | `fila.Clinica` (`java(Cássio)/fila/Clinica.java`) |
| 2 | **Fila** | Fila de Impressão em Laboratório (12 trabalhos + cancelar último) | Java | `fila.FilaImpressao` (`java(Cássio)/fila/FilaImpressao.java`) |
| 3 | **Pilha** | Sistema de Desfazer (Undo/Redo) em Editor de Texto (12 ações) | C | `c(Lukas)/Pilha/Sistema de Undo.c` |
| 4 | **Pilha** | Verificação de Expressões com `()`, `[]` e `{}` + posição de erro | C | `c(Lukas)/Pilha/Verificação de Sistemas.c` |
| 5 | **Lista Encadeada** | Gerenciamento de Playlist de Músicas (12 músicas) | C | `c(Lukas)/Lista_Encadeada/playlist.c` |
| 6 | **Lista Encadeada** | Controle de Estoque de uma Pequena Loja (simulação de 7 dias) | C | `c(Lukas)/Lista_Encadeada/estoque.c` |
| 7 | **BST** | Cadastro e Busca de Alunos por Matrícula (20 alunos) | Java | `bst.CadastroAlunos` (`java(Cássio)/bst/CadastroAlunos.java`) |
| 8 | **BST** | Sistema de Autocomplete de Nomes de Produtos (30 produtos) | Java | `bst.AutocompleteProdutos` (`java(Cássio)/bst/AutocompleteProdutos.java`) |
| 9 | **AVL** | Índice de CPF para Sistema de RH (25 funcionários) | Java | `avl.IndiceCpf` (`java(Cássio)/avl/IndiceCpf.java`) |
| 10 | **AVL** | Ranking de Jogadores em Jogo Online (30 jogadores + Top-K) | Java | `avl.RankingJogadores` (`java(Cássio)/avl/RankingJogadores.java`) |
| 11 | **Grafo** | Roteamento de Entrega de Mercadorias (Lista Adj. + Dijkstra, 10 bairros) | C | `c(Lukas)/Grafo/Entregas.c` |
| 12 | **Grafo** | Rede de Amizades em Rede Social (15 usuários + BFS graus de separação) | C | `c(Lukas)/Grafo/rede_social.c` |
| 13 | **Tabela Hash** | Cadastro de Usuários com Login Rápido (20 usuários + hash de senha) | C | `c(Lukas)/Tabela_Hash/login.c` |
| 14 | **Tabela Hash** | Contagem de Frequência de Palavras em um Texto Real | C | `c(Lukas)/Tabela_Hash/frequencia.c` |
| 15 | **Bubble Sort** | Ordenação de Notas de uma Turma Pequena (20 alunos + estatísticas) | Java | `bubblesort.NotasTurma` (`java(Cássio)/bubblesort/NotasTurma.java`) |
| 16 | **Bubble Sort** | Ordenação de Produtos por Preço em Vitrine Pequena (12 produtos) | Java | `bubblesort.ProdutosPreco` (`java(Cássio)/bubblesort/ProdutosPreco.java`) |
| 17 | **Selection Sort** | Seleção dos Melhores Candidatos em Processo Seletivo (15 candidatos) | C | `c(Lukas)/Selection_Sort/processo_seletivo.c` |
| 18 | **Selection Sort** | Organização de Tarefas por Prioridade 1 a 5 (14 tarefas) | C | `c(Lukas)/Selection_Sort/tarefas.c` |
| 19 | **Insertion Sort** | Inserção de Novas Cartas em Jogo de Cartas Ordenado (13 cartas) | Java | `insertionsort.JogoCartas` (`java(Cássio)/insertionsort/JogoCartas.java`) |
| 20 | **Insertion Sort** | Atualização de Ranking de Vendedores do Mês (10 vendedores, 7 dias) | Java | `insertionsort.RankingVendedores` (`java(Cássio)/insertionsort/RankingVendedores.java`) |
| 21 | **Merge Sort** | Ordenação de Histórico de Transações Bancárias (50 transações) | Java | `mergesort.TransacoesBancarias` (`java(Cássio)/mergesort/TransacoesBancarias.java`) |
| 22 | **Merge Sort** | Mesclagem de Duas Listas de Contatos Ordenadas (20+20 -> 30 únicos) | Java | `mergesort.MesclagemContatos` (`java(Cássio)/mergesort/MesclagemContatos.java`) |
| 23 | **Quick Sort** | Catálogo de E-commerce (100 produtos, Mediana-de-3 vs Merge Sort) | C | `c(Lukas)/Quick_Sort/ecommerce.c` |
| 24 | **Quick Sort** | Classificação de Resultados de Competição Esportiva (30 atletas, Top 3) | C | `c(Lukas)/Quick_Sort/competicao.c` |

---

## Estrutura de Diretórios

```text
trabalho-aed1/
├── java(Cássio)/               # 6 categorias e 12 aplicações em Java + 7 suítes de testes (107 casos)
│   ├── apoio/                  # Entrada, validações, dados reproduzíveis e motor de testes
│   ├── fila/                   # Situações 1 e 2 (Fila Circular, Clínica e Impressão)
│   ├── bst/                    # Situações 7 e 8 (BST, Cadastro de Alunos e Autocomplete)
│   ├── avl/                    # Situações 9 e 10 (AVL, Índice de CPF e Ranking de Jogadores)
│   ├── bubblesort/             # Situações 15 e 16 (Bubble Sort, Notas da Turma e Vitrine)
│   ├── insertionsort/          # Situações 19 e 20 (Insertion Sort, Jogo de Cartas e Vendedores)
│   └── mergesort/              # Situações 21 e 22 (Merge Sort, Transações e Mesclagem de Contatos)
├── c(Lukas)/                   # 6 categorias e 12 aplicações em C com simulações completas
│   ├── Pilha/                  # Situações 3 e 4 em C (Sistema de Undo e Verificação de Expressões)
│   ├── Lista_Encadeada/        # Situações 5 e 6 em C (Playlist de Músicas e Controle de Estoque)
│   ├── Grafo/                  # Situações 11 e 12 em C (Entregas com Dijkstra e Rede Social com BFS)
│   ├── Tabela_Hash/            # Situações 13 e 14 em C (Login Rápido e Frequência de Palavras)
│   ├── Selection_Sort/         # Situações 17 e 18 em C (Processo Seletivo e Tarefas por Prioridade)
│   └── Quick_Sort/             # Situações 23 e 24 em C (E-commerce 100 itens e Competição Esportiva)
├── relatorio/
│   └── MODELO_RELATORIO.md     # Relatório Técnico Completo (24 situações-problema)
├── CHECKLIST.md                # Checklist consolidado do projeto
└── verificar.sh                # Script que compila e executa os 107 testes da parte Java
```

---

## Como Compilar e Executar

### 1. Parte Java (Situações 1, 2, 7, 8, 9, 10, 15, 16, 19, 20, 21 e 22)

Requisito: **JDK 17 ou superior**.

Para compilar e executar todas as 7 suítes de testes automatizados (**107 casos aprovados, 0 pendentes, 0 falhas**):

```bash
bash verificar.sh
```

Para compilar manualmente e executar qualquer uma das 12 aplicações interativas:

```bash
mkdir -p out
find 'java(Cássio)' -name '*.java' -print0 | xargs -0 javac -encoding UTF-8 --release 17 -Xlint:all -d out
java -cp out fila.Clinica
```

| Suíte de Teste Java | Casos Aprovados (02/11/2026) |
|---|---:|
| `apoio.TesteApoio` | 21 OK |
| `fila.TesteFila` | 16 OK |
| `bubblesort.TesteBubbleSort` | 13 OK |
| `insertionsort.TesteInsertionSort` | 12 OK |
| `bst.TesteBST` | 14 OK |
| `mergesort.TesteMergeSort` | 16 OK |
| `avl.TesteAVL` | 15 OK |
| **Total** | **107 OK (0 pendentes, 0 falhas)** |

### 2. Parte C (Situações 3, 4, 5, 6, 11, 12, 13, 14, 17, 18, 23 e 24)

Requisito: **Compilador C (GCC / Clang)**. Todos os programas possuem menu interativo e uma opção dedicada para rodar a **simulação completa exigida pelo enunciado**:

```bash
gcc "c(Lukas)/Pilha/Sistema de Undo.c" -o undo && ./undo
gcc "c(Lukas)/Pilha/Verificação de Sistemas.c" -o expressoes && ./expressoes
gcc "c(Lukas)/Lista_Encadeada/playlist.c" -o playlist && ./playlist
gcc "c(Lukas)/Lista_Encadeada/estoque.c" -o estoque && ./estoque
gcc "c(Lukas)/Grafo/Entregas.c" -o entregas && ./entregas
gcc "c(Lukas)/Grafo/rede_social.c" -o rede_social && ./rede_social
gcc "c(Lukas)/Tabela_Hash/login.c" -o login && ./login
gcc "c(Lukas)/Tabela_Hash/frequencia.c" -o frequencia && ./frequencia
gcc "c(Lukas)/Selection_Sort/processo_seletivo.c" -o seletivo && ./seletivo
gcc "c(Lukas)/Selection_Sort/tarefas.c" -o tarefas && ./tarefas
gcc "c(Lukas)/Quick_Sort/ecommerce.c" -o ecommerce && ./ecommerce
gcc "c(Lukas)/Quick_Sort/competicao.c" -o competicao && ./competicao
```

---

## Relatório Técnico

O relatório técnico completo contendo justificativas de escolha, funcionamento interno, análises de complexidade de tempo e espaço, exemplos de entrada/saída, dificuldades encontradas e conclusão para todas as **12 categorias e 24 situações-problema** encontra-se em [`relatorio/MODELO_RELATORIO.md`](relatorio/MODELO_RELATORIO.md).
