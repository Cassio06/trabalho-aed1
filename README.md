# Trabalho de AED 1 — Parte C (Lukas)

Esta branch contém as 6 categorias e 12 aplicações implementadas em **C** por **Lukas Souza Melo**:

| Categoria | Situações-Problema | Arquivos em C |
|---|---|---|
| **Pilha** | 3. Sistema de Desfazer (Undo/Redo)<br>4. Verificação de Expressões | `Pilha/Sistema de Undo.c`<br>`Pilha/Verificação de Sistemas.c` |
| **Lista Encadeada** | 5. Gerenciamento de Playlist (12 músicas)<br>6. Controle de Estoque Semanal | `Lista_Encadeada/playlist.c`<br>`Lista_Encadeada/estoque.c` |
| **Grafo** | 11. Roteamento de Entregas (Lista de Adjacência + Dijkstra)<br>12. Rede de Amizades (15 usuários + BFS) | `Grafo/Entregas.c`<br>`Grafo/rede_social.c` |
| **Tabela Hash** | 13. Login Rápido com Hash de Senha (20 usuários)<br>14. Frequência de Palavras em Artigo Real | `Tabela_Hash/login.c`<br>`Tabela_Hash/frequencia.c` |
| **Selection Sort** | 17. Processo Seletivo Top-N (15 candidatos)<br>18. Organização de Tarefas Diárias (14 tarefas) | `Selection_Sort/processo_seletivo.c`<br>`Selection_Sort/tarefas.c` |
| **Quick Sort** | 23. Catálogo de E-commerce (100 produtos, Mediana-de-3 vs Merge Sort)<br>24. Competição Esportiva (30 atletas e Pódio Top 3) | `Quick_Sort/ecommerce.c`<br>`Quick_Sort/competicao.c` |

## Como compilar e executar (GCC)

```bash
gcc "Pilha/Sistema de Undo.c" -o undo && ./undo
gcc "Pilha/Verificação de Sistemas.c" -o expressoes && ./expressoes
gcc "Lista_Encadeada/playlist.c" -o playlist && ./playlist
gcc "Lista_Encadeada/estoque.c" -o estoque && ./estoque
gcc "Grafo/Entregas.c" -o entregas && ./entregas
gcc "Grafo/rede_social.c" -o rede_social && ./rede_social
gcc "Tabela_Hash/login.c" -o login && ./login
gcc "Tabela_Hash/frequencia.c" -o frequencia && ./frequencia
gcc "Selection_Sort/processo_seletivo.c" -o seletivo && ./seletivo
gcc "Selection_Sort/tarefas.c" -o tarefas && ./tarefas
gcc "Quick_Sort/ecommerce.c" -o ecommerce && ./ecommerce
gcc "Quick_Sort/competicao.c" -o competicao && ./competicao
```
