# Trabalho de AED 1

Projeto acadêmico da disciplina de **Algoritmos e Estruturas de Dados I**, ministrada pelo professor **Hilson Silva**, no semestre **2026.2**.

O trabalho aplica estruturas de dados e algoritmos de ordenação a problemas do cotidiano, com implementação própria, testes e análise de complexidade.

## Equipe

- **Cássio Filipe Meireles De Carvalho Braga**
- **Lukas Souza Melo**

## Objetivos

- Compreender e implementar o funcionamento interno das estruturas e dos algoritmos.
- Resolver situações práticas e justificar a escolha de cada abordagem.
- Analisar a complexidade de tempo e espaço das implementações.
- Documentar exemplos de entrada e saída e tratar casos de erro.

## Escopo do trabalho

O enunciado completo reúne **12 categorias e 24 aplicações**, com dois problemas por estrutura ou algoritmo.

| Categoria | Situações propostas |
|---|---|
| Fila | 1. Atendimento de clínica; 2. Fila de impressão |
| Pilha | 3. Desfazer em editor de texto; 4. Verificação de delimitadores |
| Lista | 5. Playlist de músicas; 6. Controle de estoque |
| Árvore Binária de Busca (BST) | 7. Cadastro de alunos; 8. Autocomplete de produtos |
| Árvore Balanceada | 9. Índice de CPF; 10. Ranking de jogadores |
| Grafo | 11. Rotas de entrega; 12. Rede de amizades |
| Tabela Hash | 13. Cadastro e autenticação de usuários; 14. Frequência de palavras |
| Bubble Sort | 15. Notas de uma turma; 16. Produtos por preço |
| Selection Sort | 17. Candidatos por pontuação; 18. Tarefas por prioridade |
| Insertion Sort | 19. Cartas de um jogo; 20. Ranking de vendedores |
| Merge Sort | 21. Transações bancárias; 22. Mesclagem de contatos |
| Quick Sort | 23. Catálogo de produtos; 24. Classificação esportiva |

Na parte Java de Cássio, a árvore balanceada escolhida é a **AVL**.

## Estado atual

Na consulta de **12/10/2026**:

- A branch `main` contém apenas a configuração inicial de atributos do Git.
- A branch `Cassio` contém a preparação de **seis categorias e 12 aplicações em Java**: Fila, Bubble Sort, Insertion Sort, BST, Merge Sort e AVL.
- Essa preparação inclui classes de domínio, dados de demonstração, entradas, menus, testes e modelo de relatório.
- O README e o checklist dessa branch registram os métodos centrais das estruturas e dos algoritmos como **pendentes de implementação**.
- As demais categorias e a integração da dupla ainda precisam ser incorporadas à versão geral do projeto.

A presença dos menus e testes não significa que as aplicações estejam concluídas. O status deverá ser atualizado conforme as implementações forem validadas.

## Organização disponível na branch Cassio

| Caminho | Conteúdo |
|---|---|
| `java(Cássio)/apoio/` | Entrada, validações, dados e apoio aos testes |
| `java(Cássio)/fila/` | Fila, clínica e impressão |
| `java(Cássio)/bubblesort/` | Ordenação de notas e preços |
| `java(Cássio)/insertionsort/` | Cartas e ranking de vendedores |
| `java(Cássio)/bst/` | Cadastro de alunos e autocomplete |
| `java(Cássio)/mergesort/` | Transações e mesclagem de contatos |
| `java(Cássio)/avl/` | Índice de CPF e ranking de jogadores |
| `relatorio/MODELO_RELATORIO.md` | Modelo para documentar o desenvolvimento |
| `CHECKLIST.md` | Acompanhamento das pendências da parte Java |
| `verificar.sh` | Compilação e execução dos testes de console |
| `out/` | Classes compiladas; diretório ignorado pelo Git |

## Tecnologias

O enunciado permite **C, Python ou Java**. A parte disponível na branch `Cassio` utiliza:

- Java puro, com **JDK 17 ou superior**.
- `javac` e `java`, sem Maven ou Gradle.
- Testes próprios de console, sem JUnit.
- Bash para o script de verificação.

As tecnologias dos demais módulos deverão ser documentadas quando forem integrados.

## Como executar a parte Java

Os comandos abaixo correspondem à estrutura atual da branch `Cassio` e usam Bash/Linux. É necessário ter Git e um JDK 17 ou superior, com `java` e `javac` disponíveis no PATH.

### Obter o código

```bash
git clone --branch Cassio https://github.com/Cassio06/trabalho-aed1.git
cd trabalho-aed1
```

### Compilar

```bash
mkdir -p out
find 'java(Cássio)' -name '*.java' -print0 | xargs -0 javac -encoding UTF-8 --release 17 -Xlint:all -d out
```

### Executar uma aplicação

```bash
java -cp out fila.Clinica
```

Outras classes disponíveis:

| Aplicação | Classe |
|---|---|
| Impressão | `fila.FilaImpressao` |
| Notas | `bubblesort.NotasTurma` |
| Preços | `bubblesort.ProdutosPreco` |
| Cartas | `insertionsort.JogoCartas` |
| Vendedores | `insertionsort.RankingVendedores` |
| Alunos | `bst.CadastroAlunos` |
| Autocomplete | `bst.AutocompleteProdutos` |
| Transações | `mergesort.TransacoesBancarias` |
| Contatos | `mergesort.MesclagemContatos` |
| Índice de CPF | `avl.IndiceCpf` |
| Jogadores | `avl.RankingJogadores` |

Substitua `fila.Clinica` pelo nome da classe desejada. Aplicações que dependem de métodos ainda não implementados podem encerrar com uma mensagem de pendência.

### Executar as verificações

```bash
bash verificar.sh
```

Para executar apenas um conjunto de testes após a compilação:

```bash
java -cp out fila.TesteFila
```

Interpretação dos resultados:

- **[OK]:** o caso foi executado e aprovado.
- **[PENDENTE]:** o caso depende de um método ainda não implementado; não equivale a aprovação.
- **[FALHOU]:** resultado incorreto ou exceção inesperada.

O script pode retornar código zero mesmo com pendências. Consulte os resumos para avaliar a conclusão de cada módulo. Este README não registra uma nova execução dos testes.

## Diretrizes de implementação

- Implementar as estruturas e os algoritmos do zero, conforme o enunciado.
- Usar arrays ou listas nativas como base dentro das permissões da atividade.
- Separar estruturas, aplicações e testes em módulos ou classes.
- Não substituir a implementação solicitada por uma estrutura ou ordenação pronta.
- Tratar situações como estrutura vazia, chave inexistente e entrada inválida.
- Testar dados comuns e casos-limite e registrar saídas reais.

## Relatório técnico e entrega

O relatório deverá apresentar:

- Justificativas das estruturas e algoritmos utilizados.
- Análise de complexidade de tempo e espaço.
- Exemplos de entrada e saída.
- Dificuldades encontradas e soluções adotadas.
- Conclusão sobre a aplicação das estruturas em problemas reais.

A entrega deve incluir o código-fonte, o relatório e a **ficha obrigatória preenchida**, por meio da plataforma **iCEV Digital**. O enunciado informa a entrega no dia da aplicação da P2; a data específica deverá seguir o calendário da disciplina.

## Próximas etapas

- [ ] Concluir e validar os algoritmos da parte Java.
- [ ] Incorporar os demais módulos da dupla.
- [ ] Registrar exemplos de execução e análises de complexidade.
- [ ] Finalizar o relatório técnico e preencher a ficha.
- [ ] Integrar a versão de entrega na branch principal.
- [ ] Atualizar este README com a estrutura e as instruções finais.
