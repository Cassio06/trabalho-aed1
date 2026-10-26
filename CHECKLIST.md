# Checklist da parte implementada na branch Cassio

Este checklist descreve somente as seis categorias desenvolvidas neste ramo: Filas, Bubble Sort, Insertion Sort, BST, Merge Sort e AVL. Pilhas, listas encadeadas/dinâmicas, grafos, tabela hash, Selection Sort e Quick Sort continuam reservados para a integração posterior; não fazem parte do escopo desta etapa.

## Implementações e aplicações

- [x] **Fila** — clínica médica (15 pacientes) e fila de impressão (12 trabalhos / 75 páginas).
- [x] **Bubble Sort** — notas (20 registros) e vitrine (12 produtos), com parada antecipada e contagem de comparações/trocas.
- [x] **Insertion Sort** — cartas (13 cartas, mão exibida após cada inserção) e ranking de vendedores (10 vendedores durante sete dias, comparação de entradas ordenada e embaralhada).
- [x] **BST** — cadastro de 20 alunos e autocomplete de 30 produtos.
- [x] **Merge Sort** — ordenação de 50 transações e mesclagem de duas listas ordenadas de 20 contatos, eliminando duplicatas.
- [x] **AVL** — índice de 25 funcionários e ranking de 30 jogadores com atualizações e consulta Top-K.
- [x] Operações principais implementadas nas seis estruturas/algoritmos, incluindo casos-limite documentados.
- [x] Testes próprios para estruturas, algoritmos, aplicações e entradas.
- [x] Script `verificar.sh` disponível para compilar e executar as sete suítes.

## Alterações recentes e verificação obrigatória

- [x] Implementar `removerUltimo()` na fila circular para cancelar o trabalho mais recentemente inserido que ainda aguarda impressão.
- [x] Expor a opção de cancelamento no menu da fila de impressão.
- [x] Adicionar teste que verifica cancelamento e preservação da ordem FIFO.
- [x] Validar CPF sem pontuação ou com pontuação no formato `000.000.000-00`, rejeitando pontuação deslocada.
- [x] Adicionar teste de regressão para os formatos de CPF.
- [x] Padronizar data/hora e valores monetários das transações para a apresentação brasileira.
- [x] Padronizar valores monetários de produtos e vendedores para a apresentação brasileira.
- [x] Remover comentário desatualizado que indicava a mesclagem de contatos como pendente.
- [ ] Executar `bash verificar.sh` após as alterações recentes e confirmar zero falhas e zero pendências.
- [ ] Atualizar este checklist e o README com os resultados efetivamente observados após a nova execução.

## Contagem de testes

A execução anterior, registrada em 26/10/2026, apresentou 104 casos aprovados. As alterações recentes acrescentaram um caso à suíte de apoio e dois à suíte da fila, totalizando **107 casos previstos** na versão atual. Essa contagem é uma expectativa baseada nos casos adicionados; não confirma aprovação até que `bash verificar.sh` seja executado novamente.

## Integração posterior da dupla

- [ ] Integrar as categorias e aplicações restantes do enunciado.
- [ ] Consolidar a numeração e o sumário do relatório final.
- [ ] Executar todas as suítes após a integração completa.
- [ ] Conferir que o relatório final corresponde às saídas reais do código consolidado.
