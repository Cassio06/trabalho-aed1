# Algoritmos e Estruturas de Dados em Java

## Objetivo e escopo

Esta parte do trabalho de AED contém seis estruturas/algoritmos e 12 aplicações de console. Usa Java puro e vetores, sem Maven, Gradle, JUnit ou dependências externas, por escolha de organização do projeto. O enunciado exige implementar as estruturas do zero; a escolha das ferramentas de compilação é do projeto.

As classes de domínio, entradas, menus, dados e testes estão preparados. A implementação didática continua com Cássio: os métodos centrais preservam os `TODO`s e lançam `UnsupportedOperationException`. Compilar ou executar um caso `[PENDENTE]` não demonstra que o algoritmo funciona.

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
| 2 - Impressão | `fila.FilaImpressao` | 12 trabalhos existentes, 75 páginas; enviar, imprimir, listar, tamanho e relatório |
| 15 - Notas | `bubblesort.NotasTurma` | 20 notas de demonstração ou 1 a 30 notas digitadas; média e ordenação crescente |
| 16 - Preços | `bubblesort.ProdutosPreco` | 12 produtos existentes; opção de preço crescente ou decrescente |
| 19 - Cartas | `insertionsort.JogoCartas` | 13 cartas existentes, recebidas uma a uma; mão após cada ordenação |
| 20 - Vendedores | `insertionsort.RankingVendedores` | 10 vendedores; sete atualizações diárias; comparação de chamadas ao comparador em entrada ordenada e em permutação fixa |
| 7 - Alunos | `bst.CadastroAlunos` | 20 alunos; cadastrar/atualizar, buscar, remover e listar por matrícula |
| 8 - Autocomplete | `bst.AutocompleteProdutos` | 30 produtos existentes; busca exata, prefixo e listagem |
| 21 - Transações | `mergesort.TransacoesBancarias` | 50 registros, incluindo débitos, créditos e instantes repetidos para verificar estabilidade |
| 22 - Contatos | `mergesort.MesclagemContatos` | Duas listas já ordenadas de 20 contatos, com dez nomes em comum; resultado esperado de 30 contatos únicos |
| 9 - CPF | `avl.IndiceCpf` | 25 funcionários; cadastrar/atualizar, buscar, remover e consultar altura/balanceamento |
| 10 - Jogadores | `avl.RankingJogadores` | 30 jogadores e três atualizações de rodada; atualizar pontuação, Top-K e consulta |

Os dados são fictícios, fixos ou gerados por fórmulas determinísticas. Os CPFs são identificadores de teste: somente o formato é validado, sem cálculo de dígitos verificadores. O catálogo usa minúsculas com `Locale.ROOT`; a normalização preserva acentos.

A clínica registra chegadas em ordem não decrescente no mesmo dia (03/08/2026), com início do serviço às 08:00 e duração estimada de dez minutos. A espera é calculada apenas a partir de pacientes realmente retirados da fila. O vetor auxiliar armazena o histórico de até 200 registros, sem substituir a fila. A impressão exibe sua sequência efetiva a cada retirada. O cancelamento do último trabalho, opcional no enunciado, fica fora desta preparação.

As cartas usam Ás = 1, J = 11, Q = 12, K = 13, com desempate por naipe. As vendas são acumuladas diariamente mantendo a ordem do ranking anterior antes da próxima chamada ao Insertion Sort. As contagens observadas no comparador só são exibidas depois da execução real do algoritmo; não medem deslocamentos.

O ranking de jogadores usa uma chave textual com dez dígitos de pontuação e nome, para preservar jogadores empatados. O Top-K percorre as chaves em ordem decrescente, incluindo nome decrescente no desempate. Atualizar a pontuação remove a chave antiga e insere a nova pela AVL; o vetor dos jogadores serve apenas como cadastro de identificadores, sem ordenar nem responder o Top-K.

Enquanto a inserção inicial de uma estrutura estiver pendente, a aplicação mostra os dados e `[PENDENTE]`, encerrando antes do menu que depende dessa estrutura. Na clínica e nas notas, a escolha entre demonstração e cadastro ocorre antes dessa chamada. Os fluxos de atendimento, ranking e resultados ordenados só poderão ser verificados integralmente após implementar os algoritmos.

## Contratos usados nos testes

- **Fila:** FIFO; `front` não remove; `front` e `dequeue` vazios lançam `NoSuchElementException`; `listar` imprime um elemento por linha sem alterar a fila.
- **BST/AVL:** busca e remoção inexistentes retornam `null`; inserção de chave repetida atualiza o valor; remoção retorna o valor removido.
- **Percursos:** imprimem somente os valores, um por linha; árvore vazia não imprime valores. Os títulos pertencem às aplicações.
- **Autocomplete:** `listarPorPrefixo` recebe prefixo normalizado, faz percurso limitado e exibe somente correspondências ordenadas; prefixo vazio lista todos, prefixo inexistente não imprime valores.
- **AVL:** altura em nós (vazia = 0, folha = 1); fator = altura esquerda menos altura direita; `estaBalanceada` verifica todos os nós; `listarMaiores(0)` não imprime valores e K maior que a base exibe todos.
- **Ordenações:** respeitam o comparador, preservam os elementos e a ordem relativa de empates; vetores vazios e unitários são válidos.
- **Contatos:** `mesclarContatos` intercala entradas já ordenadas sem chamar uma ordenação completa. Nome sem distinguir caixa define duplicata; mantém a primeira ocorrência, com preferência pela primeira lista. Deve devolver vetor de tamanho exato, sem `null`s sobrando, e não alterar as entradas.

## O que está pronto

- [x] Reaproveitamento das classes, aplicações, assinaturas e casos de teste existentes.
- [x] Validações de textos, horários, números, notas, cartas e formato de CPF.
- [x] Leitura robusta de console e tratamento específico de fim de entrada.
- [x] Mensagens, menus, exibição de dados e relatórios conectados às estruturas.
- [x] Bases que respeitam as quantidades dos 12 exercícios.
- [x] Testes de console com resultados esperados, resumos e saída de erro em falhas reais.
- [x] Comandos de compilação e modelo do relatório com campos para preenchimento pessoal.

## Implementação didática pendente

| Classe | Métodos/partes para Cássio implementar |
|---|---|
| `Fila<T>` | `enqueue`, `dequeue`, `front`, `isEmpty`, `size`, `listar` e representação interna |
| `BubbleSort` | `ordenar`: comparações, trocas, parada antecipada e instrumentação interna de trocas |
| `InsertionSort` | `ordenar`: comparações e deslocamentos |
| `BST<K,V>` | Nós, `inserir`, `buscar`, `remover`, `listarEmOrdem`, `listarPorPrefixo` e percurso limitado |
| `MergeSort` | `ordenar`: recursão e intercalação; `mesclarContatos`: merge com eliminação de duplicatas |
| `AVL<K,V>` | Nós, rotações, balanceamento, `inserir`, `buscar`, `remover`, `altura`, `fatorBalanceamento`, `estaBalanceada`, `listarMaiores` |
| Relatório | Justificativas próprias, complexidades da implementação, execuções completas, medições e dificuldades pessoais |

Os corpos dos métodos centrais existentes foram preservados. As novas operações são somente contratos com `TODO`. Não há implementação alternativa para produzir resultados enquanto estiverem pendentes. Para cumprir a comparação de desempenho de Bubble Sort do enunciado, ainda será necessário instrumentar suas trocas e registrar comparações com outros algoritmos após implementá-los.

Comece por `Fila.enqueue`, definindo a representação interna, e complete `isEmpty`, `size`, `front` e `dequeue`. Depois execute `fila.TesteFila` e as duas aplicações; implemente `listar` para a consulta da impressão.

## Verificações e interpretação

`verificar.sh` compila e executa `apoio.TesteApoio`, os seis `Teste*` e seus resumos:

- `[OK]`: verificações do caso realmente executadas e aprovadas.
- `[PENDENTE]`: uma chamada lançou `UnsupportedOperationException` com mensagem iniciada por `TODO:`. O caso não foi aprovado.
- `[FALHOU]`: resultado incorreto ou exceção inesperada; mostra detalhes e faz o programa terminar com código diferente de zero.

O script retorna zero quando não há falhas reais, mesmo havendo pendências; consulte os resumos antes de considerar um módulo concluído. Exceções inesperadas não são convertidas em pendência.

Na preparação, com OpenJDK 25 e compilação `--release 17`, foram executados 97 casos: **30 aprovados, 67 pendentes e nenhuma falha real restante**. Os aprovados cobrem domínio, entradas, quantidade/ordem dos dados e diagnóstico dos testes. As 12 aplicações também tiveram a inicialização e a mensagem de pendência verificadas; as entradas manuais de clínica/notas, opções inválidas e fim de entrada foram exercitados. Menus após a carga das árvores/filas e resultados dos algoritmos continuam aguardando implementação.

Use [CHECKLIST.md](CHECKLIST.md) para acompanhar o término didático e [MODELO_RELATORIO.md](relatorio/MODELO_RELATORIO.md) para registrar seus resultados reais. Os números desta verificação são um registro desta preparação, não resultados pessoais nem aprovação das estruturas.
