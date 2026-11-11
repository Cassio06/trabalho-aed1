# Verificação final para entrega — 11/11/2026

**Dupla:** Cássio Filipe Meireles De Carvalho Braga (0031236) e Lukas Souza Melo (0031163), turma SNYDER, **2º Período de Engenharia de Software (2026.2)**.

## Código

| Verificação executada | Resultado |
|---|---|
| Compilação Java com `--release 17 -encoding UTF-8 -Xlint:all` | Sem erros ou avisos |
| `bash verificar.sh` — sete suítes Java | 107 OK, 0 pendentes, 0 falhas |
| Execução das 12 aplicações Java com entradas de demonstração | 12 OK, saída e encerramento conferidos |
| `node verificar-c.mjs --cc <zig.exe>` — compilador Zig/Clang | 48 verificações OK, 0 falhas |
| Compilação dos 12 programas C com `-std=c11 -Wall -Wextra -pedantic -Werror` | Sem erros ou avisos |
| Simulações dos 12 programas C | Todas executadas; resultados principais conferidos |
| Teste interno do contador de palavras | Oito casos: acentos, contagens, maiúsculas, pontuação, palavras/textos longos, hash e entrada sem palavras |
| `node --check verificar-c.mjs` e `git diff --check` | Sem erros de sintaxe ou espaços inválidos |

As 48 verificações C incluem etapas de compilação, execução das 12 simulações e regressões; os oito casos internos do contador pertencem a uma dessas etapas, não são 48 testes unitários distintos.

## Correções verificadas

- A situação 14 processa o primeiro parágrafo real de *Dom Casmurro*, capítulo I (Machado de Assis, 1899), com fonte indicada na demonstração e nos relatórios.
- Contagem independente do texto real: **89 palavras, 69 distintas**. Top: `e` (5), `que` (4), `da`, `de`, `os` e `versos` (3 cada).
- O contador mantém a distinção entre `avó` e `avô`, converte maiúsculas portuguesas precompostas em minúsculas e separa pontuação UTF-8. Palavras e linhas acima dos antigos limites não são truncadas.
- O hash usa base 33 e módulo 31, aproveitando os prefixos das palavras.
- Dijkstra encontra rotas de custo 1.000.000 e 2.147.483.648 sem confundir distância com infinito ou estourar a soma; também identifica pontos desconectados.
- Estoque, candidatos, atletas, catálogo e playlist rejeitam NaN/infinito. O catálogo limita popularidade a 0–1000.
- As implementações permanecem divididas entre **Java e C**, conforme solicitado.

## Documentos e entrega

- Relatórios Markdown, DOCX e PDF atualizados com texto real, resultados e detalhes das correções.
- O PDF foi reexportado do DOCX, com sumário automático atualizado e numeração de páginas recalculada.
- `FICHA_OBRIGATORIA_PREENCHIDA.pdf`: página original preenchida com turma, período, nomes e matrículas; o PDF do enunciado foi preservado.
- Revisão independente do código pelo Antigravity: sem bloqueadores encontrados nas correções.
- Revisão independente dos documentos pelo Antigravity: pronto para envio dos arquivos, sem bloqueadores; PDF com **43 páginas** e **22 entradas** no sumário conferidas com o corpo do documento.

O escopo verificado é o enunciado local e os cenários descritos acima. A submissão no **iCEV Digital** é uma etapa externa e permanece pendente até ser realizada na plataforma.
