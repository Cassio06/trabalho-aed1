package apoio;

import avl.Funcionario;
import avl.Jogador;
import bst.Aluno;
import bst.Produto;
import bubblesort.NotaAluno;
import bubblesort.ProdutoPreco;
import fila.Paciente;
import fila.TrabalhoImpressao;
import insertionsort.Carta;
import insertionsort.Vendedor;
import java.time.LocalDateTime;
import java.util.NoSuchElementException;
import java.util.Scanner;
import mergesort.Contato;
import mergesort.Transacao;
import static apoio.Testes.rejeita;
import static apoio.Testes.verificar;

/** Verificações executáveis mesmo antes da implementação dos algoritmos. */
public class TesteApoio {

    public static void main(String[] args) {
        Testes testes = new Testes();
        testes.executar("paciente: campos, trim e exibição", () -> {
            Paciente paciente = new Paciente(" Ana ", "08:05", " Consulta ");
            verificar(paciente.getNome().equals("Ana") && paciente.getHorarioChegada().equals("08:05")
                    && paciente.getTipoAtendimento().equals("Consulta"), "Campos do paciente.");
            verificar(paciente.toString().equals("Ana - chegada: 08:05 - atendimento: Consulta"), "Exibição do paciente.");
        });
        testes.executar("paciente: nome vazio e horário inválido", () -> {
            rejeita(() -> new Paciente(" ", "08:05", "Consulta"));
            rejeita(() -> new Paciente("Ana", "24:00", "Consulta"));
            rejeita(() -> new Paciente("Ana", "08:60", "Consulta"));
            rejeita(() -> new Paciente("Ana", "8:05", "Consulta"));
        });
        testes.executar("impressão: campos e exibição", () -> {
            TrabalhoImpressao trabalho = new TrabalhoImpressao("Ana", "aed.pdf", 8);
            verificar(trabalho.getAluno().equals("Ana") && trabalho.getArquivo().equals("aed.pdf")
                    && trabalho.getNumeroPaginas() == 8, "Campos do trabalho.");
            verificar(trabalho.toString().equals("Ana - aed.pdf - 8 página(s)"), "Exibição do trabalho.");
            rejeita(() -> new TrabalhoImpressao("Ana", "aed.pdf", 0));
        });
        testes.executar("aluno: campos e matrícula válida", () -> {
            Aluno aluno = new Aluno(1001, "Ana", "Computação");
            verificar(aluno.getMatricula() == 1001 && aluno.getNome().equals("Ana")
                    && aluno.getCurso().equals("Computação"), "Campos do aluno.");
            verificar(aluno.toString().equals("1001 - Ana - Computação"), "Exibição do aluno.");
            rejeita(() -> new Aluno(-1, "Ana", "Computação"));
        });
        testes.executar("produto BST: campo e exibição", () -> {
            Produto produto = new Produto(" Caderno ");
            verificar(produto.getNome().equals("Caderno") && produto.toString().equals("Caderno"), "Nome do produto.");
            rejeita(() -> new Produto(null));
        });
        testes.executar("funcionário: campos e normalização de CPF", () -> {
            Funcionario funcionario = new Funcionario("73120510000", "Ana", "Analista");
            verificar(funcionario.getCpf().equals("731.205.100-00") && funcionario.getNome().equals("Ana")
                    && funcionario.getCargo().equals("Analista"), "Campos do funcionário.");
            verificar(funcionario.toString().equals("731.205.100-00 - Ana - Analista"), "Exibição do funcionário.");
            rejeita(() -> new Funcionario("abc", "Ana", "Analista"));
            rejeita(() -> new Funcionario("123", "Ana", "Analista"));
        });
        testes.executar("CPF: aceitar formatos válidos e rejeitar pontuação deslocada", () -> {
            verificar(Validacao.cpf("73120510000").equals("731.205.100-00"), "Aceitar 11 dígitos.");
            verificar(Validacao.cpf("731.205.100-00").equals("731.205.100-00"), "Aceitar formato pontuado.");
            rejeita(() -> Validacao.cpf("73.1205.100-00"));
            rejeita(() -> Validacao.cpf("731-205.100.00"));
        });
        testes.executar("jogador: zero pontos e negativos", () -> {
            Jogador jogador = new Jogador("Ana", 0);
            verificar(jogador.getNome().equals("Ana") && jogador.getPontuacao() == 0
                    && jogador.toString().equals("Ana - 0 ponto(s)"), "Campos do jogador.");
            rejeita(() -> new Jogador("Ana", -1));
        });
        testes.executar("notas: campos e limites 0 e 10", () -> {
            NotaAluno nota = new NotaAluno("Ana", 10);
            verificar(nota.getNome().equals("Ana") && nota.getNota() == 10
                    && nota.toString().equals("Ana - nota: 10.0"), "Campos da nota.");
            verificar(new NotaAluno("Bruno", 0).getNota() == 0, "Zero é uma nota válida.");
            rejeita(() -> new NotaAluno("Ana", 10.1));
            rejeita(() -> new NotaAluno("Ana", -1));
            rejeita(() -> new NotaAluno("Ana", Double.NaN));
        });
        testes.executar("preço: campos e não finitos", () -> {
            ProdutoPreco produto = new ProdutoPreco("Mouse", 65.9);
            verificar(produto.getNome().equals("Mouse") && produto.getPreco() == 65.9
                    && produto.toString().startsWith("Mouse - R$ "), "Campos do produto com preço.");
            rejeita(() -> new ProdutoPreco("Mouse", Double.POSITIVE_INFINITY));
            rejeita(() -> new ProdutoPreco("Mouse", -1));
        });
        testes.executar("carta: valor, naipe e normalização", () -> {
            Carta carta = new Carta(" k ", "copas");
            verificar(carta.getValor().equals("K") && carta.getNaipe().equals("Copas")
                    && carta.toString().equals("K de Copas"), "Campos da carta.");
            rejeita(() -> new Carta("14", "Copas"));
            rejeita(() -> new Carta("A", "Flores"));
        });
        testes.executar("vendedor: campos e total válido", () -> {
            Vendedor vendedor = new Vendedor("Ana", 120.5);
            verificar(vendedor.getNome().equals("Ana") && vendedor.getTotalVendido() == 120.5
                    && vendedor.toString().startsWith("Ana - total vendido: R$ "), "Campos do vendedor.");
            rejeita(() -> new Vendedor("Ana", Double.NEGATIVE_INFINITY));
        });
        testes.executar("contato: campos e informação obrigatória", () -> {
            Contato contato = new Contato("Ana", "ana@exemplo.com");
            verificar(contato.getNome().equals("Ana") && contato.getInformacaoContato().equals("ana@exemplo.com")
                    && contato.toString().equals("Ana - ana@exemplo.com"), "Campos do contato.");
            rejeita(() -> new Contato("Ana", " "));
        });
        testes.executar("transação: saída negativa e data/hora", () -> {
            LocalDateTime data = LocalDateTime.of(2026, 8, 1, 8, 0);
            Transacao transacao = new Transacao(data, -25, "Compra");
            verificar(transacao.getDataHora().equals(data) && transacao.getValor() == -25
                    && transacao.getDescricao().equals("Compra")
                    && transacao.toString().equals("01/08/2026 08:00 - R$ -25,00 - Compra"),
                    "Campos e formatação brasileira da transação.");
            rejeita(() -> new Transacao(data, Double.NaN, "Compra"));
            try {
                new Transacao(null, 10, "PIX");
            } catch (NullPointerException esperado) {
                return;
            }
            throw new AssertionError("Data/hora nula deve ser rejeitada.");
        });
        testes.executar("console: recuperar inteiro inválido e fora do intervalo", () -> {
            try (Scanner scanner = new Scanner("abc\n999\n\n2\n")) {
                String saida = Testes.saida(() -> verificar(new Entrada(scanner).inteiro("Opção: ", 0, 2) == 2,
                        "Deve ler 2 após rejeitar as entradas anteriores."));
                verificar(saida.contains("Digite um inteiro") && saida.contains("não vazio"), "Orientar nova tentativa.");
            }
        });
        testes.executar("console: decimal com vírgula e rejeição de NaN", () -> {
            try (Scanner scanner = new Scanner("NaN\nInfinity\n-1\n7,5\n")) {
                Testes.saida(() -> verificar(new Entrada(scanner).decimal("Nota: ", 0, 10) == 7.5,
                        "Esperado 7,5 após três valores inválidos."));
            }
        });
        testes.executar("console: recuperar horário inválido", () -> {
            try (Scanner scanner = new Scanner("24:00\n08:60\n08:05\n")) {
                Testes.saida(() -> verificar(new Entrada(scanner).horario("Hora: ").equals("08:05"), "Esperado 08:05."));
            }
        });
        testes.executar("console: recuperar CPF inválido", () -> {
            try (Scanner scanner = new Scanner("abc\n73120510000\n")) {
                Testes.saida(() -> verificar(new Entrada(scanner).cpf("CPF: ").equals("731.205.100-00"), "Normalizar CPF."));
            }
        });
        testes.executar("console: fim de entrada encerra sem erro", () -> {
            try (Scanner scanner = new Scanner("")) {
                String saida = Testes.saida(() -> Entrada.executar(() -> new Entrada(scanner).texto("Nome: ")));
                verificar(saida.contains("Entrada encerrada"), "EOF deve encerrar com mensagem.");
            }
        });
        testes.executar("console: erro do algoritmo não é confundido com EOF", () -> {
            try {
                Entrada.executar(() -> { throw new NoSuchElementException("erro real"); });
            } catch (NoSuchElementException esperado) {
                return;
            }
            throw new AssertionError("Erros reais não devem ser escondidos pelo console.");
        });
        testes.executar("relatório de testes distingue TODO de erro real", () -> {
            String saida = Testes.saida(() -> {
                Testes locais = new Testes();
                locais.executar("TODO", () -> { throw new UnsupportedOperationException("TODO: teste"); });
                locais.executar("erro real", () -> { throw new UnsupportedOperationException("falha inesperada"); });
                try {
                    locais.concluir();
                } catch (AssertionError esperado) {
                    return;
                }
                throw new AssertionError("Falha real deve produzir erro na conclusão.");
            });
            verificar(saida.contains("[PENDENTE] TODO") && saida.contains("[FALHOU] erro real")
                    && saida.contains("0 OK, 1 pendentes, 1 falhas"), "Não simular sucesso nem pendência para erro real.");
        });
        testes.concluir();
    }
}
