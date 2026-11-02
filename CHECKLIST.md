# Checklist Geral do Trabalho Avaliativo — AED I (Versão Unificada na `main`)

Este checklist consolida as **12 categorias e 24 situações-problema** exigidas no PDF do trabalho avaliativo do Prof. Hilson Silva (2026.2).

## 1. Estruturas de Dados Lineares (25% da nota)

- [x] **2.1 Filas (Java — Cássio):**
  - [x] **Situação 1 — Clínica Médica (`fila.Clinica`):** `enqueue`, `dequeue`, `front`, `isEmpty`, `size`, simulação com 15 pacientes, ordem de atendimento e tempo médio de espera (`21,00 min`).
  - [x] **Situação 2 — Fila de Impressão (`fila.FilaImpressao`):** 12 trabalhos (75 páginas), envio, impressão, listagem, cancelamento do último pendente (`removerUltimo`) e relatório de sequência.
- [x] **2.2 Pilhas (C — Lukas — `c(Lukas)/Pilha/`):**
  - [x] **Situação 3 — Sistema de Desfazer em Editor (`c(Lukas)/Pilha/Sistema de Undo.c`):** `push`, `pop`, `redo` (segunda pilha) e simulação automatizada passo a passo com 12 ações.
  - [x] **Situação 4 — Verificação de Expressões (`c(Lukas)/Pilha/Verificação de Sistemas.c`):** suporte a `()`, `[]` e `{}`, testes com expressões válidas/inválidas do enunciado e relatório indicando a posição exata do primeiro desbalanceamento.
- [x] **2.3 Listas Encadeadas (C — Lukas — `c(Lukas)/Lista_Encadeada/`):**
  - [x] **Situação 5 — Playlist de Músicas (`c(Lukas)/Lista_Encadeada/playlist.c`):** inserir no início, no fim e em posição específica, remover por título, buscar, reordenar (mover posição), listar e simulação com 12 músicas.
  - [x] **Situação 6 — Controle de Estoque (`c(Lukas)/Lista_Encadeada/estoque.c`):** cadastrar, atualizar quantidade, remover produto (incluindo esgotados), buscar por código/nome, listar abaixo do estoque mínimo e simulação semanal (7 dias).

## 2. Estruturas de Dados Não-Lineares (30% da nota)

- [x] **3.1 Árvore Binária de Busca — BST (Java — Cássio):**
  - [x] **Situação 7 — Cadastro de Alunos (`bst.CadastroAlunos`):** inserir, buscar por matrícula, remover, percurso em ordem e demonstração com 20 alunos.
  - [x] **Situação 8 — Autocomplete de Produtos (`bst.AutocompleteProdutos`):** BST de 30 produtos e busca por prefixo com percurso limitado (poda).
- [x] **3.2 Árvore Balanceada — AVL (Java — Cássio):**
  - [x] **Situação 9 — Índice de CPF para RH (`avl.IndiceCpf`):** inserção com rotações, busca, remoção, verificação de altura/fator de balanceamento e demonstração com 25 funcionários.
  - [x] **Situação 10 — Ranking de Jogadores (`avl.RankingJogadores`):** AVL ordenada por pontuação + nome, atualização de pontuação, consulta Top-K e simulação com 30 jogadores.
- [x] **3.3 Grafos (C — Lukas — `c(Lukas)/Grafo/`):**
  - [x] **Situação 11 — Roteamento de Entregas (`c(Lukas)/Grafo/Entregas.c`):** grafo ponderado em lista de adjacência, algoritmo de Dijkstra e simulação com 10 bairros/pontos de entrega.
  - [x] **Situação 12 — Rede de Amizades (`c(Lukas)/Grafo/rede_social.c`):** grafo não-direcionado com 15 usuários, adicionar amizade, listar amigos, amigos em comum, sugerir conexões e BFS para graus de separação.
- [x] **3.4 Tabela Hash (C — Lukas — `c(Lukas)/Tabela_Hash/`):**
  - [x] **Situação 13 — Cadastro e Login Rápido (`c(Lukas)/Tabela_Hash/login.c`):** tabela hash com tratamento de colisões por encadeamento, senha armazenada em hash (DJB2), busca/remoção O(1) médio e simulação com 20 usuários.
  - [x] **Situação 14 — Frequência de Palavras (`c(Lukas)/Tabela_Hash/frequencia.c`):** processamento de texto/artigo real, contagem por palavra na tabela hash, exibição das palavras mais frequentes e total de palavras distintas.

## 3. Algoritmos de Ordenação (20% da nota)

- [x] **4.1 Bubble Sort (Java — Cássio):**
  - [x] **Situação 15 — Notas da Turma (`bubblesort.NotasTurma`):** 20 notas, parada antecipada e comparação de comparações/trocas com Insertion Sort.
  - [x] **Situação 16 — Vitrine de Produtos (`bubblesort.ProdutosPreco`):** 12 produtos com opção de ordem crescente e decrescente.
- [x] **4.2 Selection Sort (C — Lukas — `c(Lukas)/Selection_Sort/`):**
  - [x] **Situação 17 — Processo Seletivo (`c(Lukas)/Selection_Sort/processo_seletivo.c`):** ordenação decrescente, extração dos Top-N candidatos e simulação com 15 candidatos.
  - [x] **Situação 18 — Organização de Tarefas (`c(Lukas)/Selection_Sort/tarefas.c`):** ordenação por nível de prioridade (1 a 5) e simulação de um dia de trabalho com 14 tarefas.
- [x] **4.3 Insertion Sort (Java — Cássio):**
  - [x] **Situação 19 — Jogo de Cartas (`insertionsort.JogoCartas`):** simulação de recebimento de 13 cartas exibindo a mão ordenada após cada inserção.
  - [x] **Situação 20 — Ranking de Vendedores (`insertionsort.RankingVendedores`):** 10 vendedores ao longo de 7 dias e comparação entre lista já ordenada (9 comparações) e lista aleatória (31 comparações).
- [x] **4.4 Merge Sort (Java — Cássio):**
  - [x] **Situação 21 — Transações Bancárias (`mergesort.TransacoesBancarias`):** ordenação estável por data/hora em 50 transações.
  - [x] **Situação 22 — Mesclagem de Contatos (`mergesort.MesclagemContatos`):** etapa de merge combinando duas listas ordenadas de 20 contatos com remoção de duplicatas (30 únicos).
- [x] **4.5 Quick Sort (C — Lukas — `c(Lukas)/Quick_Sort/`):**
  - [x] **Situação 23 — Catálogo de E-commerce (`c(Lukas)/Quick_Sort/ecommerce.c`):** Quick Sort com pivô mediana-de-três, ordenação por preço, nome ou popularidade, teste com 100 produtos e comparação com Merge Sort.
  - [x] **Situação 24 — Competição Esportiva (`c(Lukas)/Quick_Sort/competicao.c`):** Quick Sort por tempo de prova, identificação do pódio (Top 3) e simulação com 30 atletas.

## 4. Verificação, Relatório e Entrega Final

- [x] Executar `bash verificar.sh` e confirmar **107/107 casos aprovados** nas 7 suítes da parte Java.
- [x] Unificar as branches `Cassio` e `Lukas` na branch `main`.
- [x] Consolidar o relatório técnico completo das 12 categorias e 24 aplicações em `relatorio/MODELO_RELATORIO.md`.
- [ ] Preencher os números de matrícula dos dois alunos e o nome da turma (ADELLE ou SNYDER) na Ficha Obrigatória (página 2 do PDF) e no cabeçalho do relatório.
- [ ] Enviar o pacote final (código + relatório + ficha obrigatória) pela plataforma **iCEV Digital** até o dia da P2.
