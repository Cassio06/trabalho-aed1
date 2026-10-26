# Algoritmos e Estruturas de Dados em Java

## Objetivo e escopo

Esta parte do trabalho de Algoritmos e Estruturas de Dados I contém seis estruturas e algoritmos, com 12 aplicações de console em Java: Fila, Bubble Sort, Insertion Sort, Árvore Binária de Busca (BST), Merge Sort e Árvore AVL.

As implementações utilizam Java puro, sem Maven, Gradle, JUnit ou dependências externas. As estruturas e os algoritmos são implementados no próprio projeto, sem substituir seu funcionamento por coleções ou métodos de ordenação prontos.

As aplicações incluem dados de demonstração, entradas, menus e testes próprios. O script `verificar.sh` compila o projeto e executa as suítes de testes.

Na execução registrada em 26 de outubro de 2026, antes das últimas alterações, as sete suítes totalizaram 104 testes aprovados. Depois disso, foram acrescentados um teste de cancelamento da fila e um teste de sintaxe do CPF. A versão atual prevê 106 casos no total; é necessário executar `bash verificar.sh` novamente para confirmar os resultados dessa versão.

## Organização

```text
java(Cássio)/
├── apoio/          # Entrada, validações, dados de nomes e verificação de console
├── fila/           # Fila, clínica e impressão
├── bubblesort/     # Bubble Sort, notas e preços
├── insertionsort/  # Insertion Sort, cartas e vendedores
├── bst/            # BST, alunos e autocomplete
├── mergesort/      # Merge Sort, transações e contatos
└── avl/            # AVL, CPF e jogadores
relatorio/MODELO_RELATORIO.md
CHECKLIST.md
verificar.sh
out/                # .class gerados e ignorados pelo Git
```

Cada pasta de código corresponde a um pacote Java. Os modelos existentes continuam imutáveis: alterações de totais ou pontuações criam novos objetos, preservando getters, construtores e `toString`. Não há necessidade de setters para os fluxos atuais. `Comparator` define o critério de ordenação; não executa o algoritmo. Não são usadas coleções nem ordenações prontas.

## Compilação e execução

Requisito: JDK 17 ou superior, com `java` e `javac` no PATH. Execute na raiz do repositório. Os comandos abaixo foram verificados em Bash/Linux:

```bash
mkdir -p out
find 'java(Cássio)' -name '*.java' -print0 | xargs -0 javac -encoding UTF-8 --release 17 -Xlint:all -d out
java -cp out fila.Clinica
```

Para compilar e executar todos os testes:

```bash
bash verificar.sh
```

Para executar apenas um teste após compilar:

```bash
java -cp out mergesort.TesteMergeSort
```

Substitua o nome completo da classe para executar qualquer aplicação da tabela seguinte. Aplicações com menu aceitam `0` para sair; fim de entrada também encerra normalmente. Valores inválidos são solicitados novamente. Números decimais aceitam ponto ou vírgula, sem separador de milhar; horários usam `HH:mm`.

### IntelliJ

1. Abra a pasta do projeto.
2. Configure o SDK do projeto para JDK 17 ou superior.
3. Marque `java(Cássio)` como **Sources Root**, se necessário.
4. Abra a classe e execute o `main` pelo triângulo verde.

## Aplicações e dados reproduzíveis

| Exercício | Classe com `main` | Base e interação preparada |
|---|---|---|
| 1 - Clínica | `fila.Clinica` | 15 pacientes de demonstração ou cadastro manual; chegada, chamada, próximo, tamanho, atender todos e relatório |
| 2 - Impressão | `fila.FilaImpressao` | 12 trabalhos existentes, 75 páginas; enviar, imprimir, listar, tamanho, cancelar o último pendente e relatório |
| 15 - Notas | `bubblesort.NotasTurma` | 20 notas de demonstração ou 1 a 30 notas digitadas; média e ordenação crescente |
| 16 - Preços | `bubblesort.ProdutosPreco` | 12 produtos existentes; opção de preço crescente ou decrescente |
| 19 - Cartas | `insertionsort.JogoCartas` | 13 cartas existentes, recebidas uma a uma; mão após cada ordenação |
| 20 - Vendedores | `insertionsort.RankingVendedores` | 10 vendedores; sete atualizações diárias; comparação de chamadas ao comparador entre entrada ordenada e entrada embaralhada com semente fixa (42) |
| 7 - Alunos | `bst.CadastroAlunos` | 20 alunos; cadastrar/atualizar, buscar, remover e listar por matrícula |
| 8 - Autocomplete | `bst.AutocompleteProdutos` | 30 produtos existentes; busca exata, prefixo e listagem |
| 21 - Transações | `mergesort.TransacoesBancarias` | 50 registros, incluindo débitos, créditos e instantes repetidos para verificar estabilidade |
| 22 - Contatos | `mergesort.MesclagemContatos` | Duas listas já ordenadas de 20 contatos, com dez nomes em comum; resultado esperado de 30 contatos únicos |
| 9 - CPF | `avl.IndiceCpf` | 25 funcionários; cadastrar/atualizar, buscar, remover e consultar altura/balanceamento |
| 10 - Jogadores | `avl.RankingJogadores` | 30 jogadores e três atualizações de rodada; atualizar pontuação, Top-K e consulta |

Os dados são fictícios, fixos ou gerados por fórmulas determinísticas. Os CPFs são identificadores de teste: somente o formato é validado, sem cálculo de dígitos verificadores. O catálogo usa minúsculas com `Locale.ROOT`; a normalização preserva acentos.

A clínica registra chegadas em ordem não decrescente no mesmo dia (03/08/2026), com início do serviço às 08:00 e duração estimada de dez minutos. A espera é calculada apenas a partir de pacientes realmente retirados da fila. O vetor auxiliar armazena o histórico de até 200 registros, sem substituir a fila. A impressão exibe sua sequência efetiva a cada retirada. A opção 6 cancela o trabalho mais recentemente inserido que ainda esteja aguardando; trabalhos já impressos não podem ser cancelados.

As cartas usam Ás = 1, J = 11, Q = 12, K = 13, com desempate por naipe. As vendas são acumuladas diariamente mantendo a ordem do ranking anterior antes da próxima chamada ao Insertion Sort. As contagens observadas no comparador só são exibidas depois da execução real do algoritmo; não medem deslocamentos.

O ranking de jogadores usa uma chave textual com dez dígitos de pontuação e nome, para preservar jogadores empatados. O Top-K percorre as chaves em ordem decrescente, incluindo nome decrescente no desempate. Atualizar a pontuação remove a chave antiga e insere a nova pela AVL; o vetor dos jogadores serve apenas como cadastro de identificadores, sem ordenar nem responder o Top-K.

## Contratos usados nos testes

- **Fila:** FIFO; `front` não remove; `front`, `dequeue` e `removerUltimo` em fila vazia lançam `NoSuchElementException`; `removerUltimo` cancela o elemento mais recentemente inserido ainda pendente; `listar` imprime um elemento por linha sem alterar a fila.
- **BST/AVL:** busca e remoção inexistentes retornam `null`; inserção de chave repetida atualiza o valor; remoção retorna o valor removido.
- **Percursos:** imprimem somente os valores, um por linha; árvore vazia não imprime valores. Os títulos pertencem às aplicações.
- **Autocomplete:** `listarPorPrefixo` recebe prefixo normalizado, faz percurso limitado e exibe somente correspondências ordenadas; prefixo vazio lista todos, prefixo inexistente não imprime valores.
- **AVL:** altura em nós (vazia = 0, folha = 1); fator = altura esquerda menos altura direita; `estaBalanceada` verifica todos os nós; `listarMaiores(0)` não imprime valores e K maior que a base exibe todos.
- **Ordenações:** respeitam o comparador, preservam os elementos e a ordem relativa de empates; vetores vazios e unitários são válidos.
- **Contatos:** `mesclarContatos` intercala entradas já ordenadas sem chamar uma ordenação completa. Nome sem distinguir caixa define duplicata; mantém a primeira ocorrência, com preferência pela primeira lista. Deve devolver vetor de tamanho exato, sem `null`s sobrando, e não alterar as entradas.

## O que está pronto

- [x] Implementação da fila circular e das duas aplicações associadas.
- [x] Implementação do Bubble Sort, com parada antecipada e estatísticas de comparações e trocas.
- [x] Implementação do Insertion Sort, com estatísticas de comparações e deslocamentos.
- [x] Implementação da Árvore Binária de Busca (BST), incluindo cadastro, busca, remoção e autocomplete.
- [x] Implementação do Merge Sort e da mesclagem de listas de contatos ordenadas com eliminação de duplicatas.
- [x] Implementação da árvore AVL, incluindo operações de busca, inserção, remoção, balanceamento e consulta Top-K.
- [x] Desenvolvimento das 12 aplicações de console associadas às seis categorias implementadas.
- [x] Testes para estruturas, algoritmos, dados de demonstração e validações de entrada.
- [x] Script `verificar.sh` para compilar o projeto e executar as suítes de testes.
- [x] Modelo de relatório técnico e documentação dos comandos para compilação e execução.

A execução registrada em 26 de outubro de 2026 corresponde à versão anterior às últimas mudanças e totalizou 104 casos aprovados. As alterações recentes acrescentaram dois casos de teste (fila e validação de CPF), elevando a contagem prevista para 106. Até a reexecução de `bash verificar.sh`, o status do conjunto atualizado deve ser considerado pendente de confirmação.

## Verificações e interpretação

O script `verificar.sh` compila o projeto e executa sete suítes de testes: `apoio.TesteApoio`, `fila.TesteFila`, `bubblesort.TesteBubbleSort`, `insertionsort.TesteInsertionSort`, `bst.TesteBST`, `mergesort.TesteMergeSort` e `avl.TesteAVL`.

Os resultados são apresentados com os seguintes indicadores:

- `[OK]`: o caso foi executado e aprovado.
- `[PENDENTE]`: o caso depende de uma funcionalidade ainda não implementada; não equivale a aprovação.
- `[FALHOU]`: o resultado foi incorreto ou ocorreu uma exceção inesperada.

O script deve ser interpretado em conjunto com os resumos de cada suíte. Um código de saída zero, isoladamente, não garante que todos os casos foram aprovados caso existam pendências.

A tabela abaixo registra a execução anterior, de 26 de outubro de 2026. Após ela, um caso foi acrescentado a `apoio.TesteApoio` e outro a `fila.TesteFila`. A quantidade esperada na versão atual é mostrada na última coluna; ela não deve ser considerada aprovada até uma nova execução de `bash verificar.sh`.

| Suíte | Execução anterior | Casos previstos na versão atual |
|---|---:|---:|
| `apoio.TesteApoio` | 20 | 21 |
| `fila.TesteFila` | 14 | 15 |
| `bubblesort.TesteBubbleSort` | 13 | 13 |
| `insertionsort.TesteInsertionSort` | 12 | 12 |
| `bst.TesteBST` | 14 | 14 |
| `mergesort.TesteMergeSort` | 16 | 16 |
| `avl.TesteAVL` | 15 | 15 |
| **Total** | **104** | **106** |

As aprovações da execução anterior não substituem uma nova verificação depois das alterações de código. Confirme que a versão atual termina sem falhas ou pendências antes de atualizar este registro.

Os testes cobrem operações das estruturas, ordenações, casos-limite, dados das aplicações e validações de entrada. A execução das suítes não substitui a revisão das aplicações nem a confirmação de que os resultados descritos no relatório correspondem às saídas efetivamente observadas.

Use `CHECKLIST.md` para acompanhar as etapas restantes e `relatorio/MODELO_RELATORIO.md` como referência para a documentação técnica.
