package fila;

import apoio.Testes;
import java.util.NoSuchElementException;

public class TesteFila {

    private static final Testes TESTES = new Testes();

    public static void main(String[] args) {
        executar("fila vazia", TesteFila::testarFilaVazia);

        executar("um elemento", TesteFila::testarUmElemento);

        executar("vários elementos", TesteFila::testarVariosElementos);

        executar("elementos repetidos", TesteFila::testarElementosRepetidos);

        executar("remoção em fila vazia", TesteFila::testarRemocaoEmFilaVazia);

        executar("front em fila vazia", () -> {
            Fila<Integer> fila = new Fila<>();

            try {
                fila.front();
            } catch (NoSuchElementException esperado) {
                return;
            }

            throw new AssertionError(
                    "front vazio deve lançar NoSuchElementException."
            );
        });

        executar("intercalar inserções e remoções e reutilizar fila", () -> {
            Fila<Integer> fila = new Fila<>();

            fila.enqueue(1);
            fila.enqueue(2);

            verificar(
                    fila.dequeue() == 1,
                    "Primeira saída deve ser 1."
            );

            fila.enqueue(3);

            verificar(
                    fila.size() == 2,
                    "Esperados dois elementos após intercalar operações."
            );

            verificar(
                    fila.dequeue() == 2 && fila.dequeue() == 3,
                    "Saídas devem ser 2 e 3."
            );

            verificar(
                    fila.size() == 0 && fila.isEmpty(),
                    "Fila deve terminar vazia."
            );

            fila.enqueue(4);

            verificar(
                    fila.front() == 4 && fila.dequeue() == 4,
                    "Fila esvaziada deve ser reutilizável."
            );
        });

        executar("capacidade máxima e tentativa de exceder", () -> {
            Fila<Integer> fila = new Fila<>();

            for (int i = 1; i <= 20; i++) {
                fila.enqueue(i);
            }

            verificar(
                    fila.size() == 20,
                    "A fila deve aceitar exatamente 20 elementos."
            );

            try {
                fila.enqueue(21);
            } catch (IllegalStateException esperado) {
                verificar(
                        "A fila está cheia.".equals(esperado.getMessage()),
                        "A mensagem de fila cheia está incorreta."
                );

                verificar(
                        fila.size() == 20,
                        "A tentativa de exceder a capacidade não deve alterar a fila."
                );

                return;
            }

            throw new AssertionError(
                    "A inserção do 21º elemento deveria lançar IllegalStateException."
            );
        });

        executar("fila circular após remoções e novas inserções", () -> {
            Fila<Integer> fila = new Fila<>();

            for (int i = 1; i <= 20; i++) {
                fila.enqueue(i);
            }

            for (int i = 1; i <= 10; i++) {
                verificar(
                        fila.dequeue() == i,
                        "A ordem FIFO deve ser mantida nas primeiras remoções."
                );
            }

            for (int i = 21; i <= 30; i++) {
                fila.enqueue(i);
            }

            verificar(
                    fila.size() == 20,
                    "A fila deve conter 20 elementos após reutilizar as posições."
            );

            for (int i = 11; i <= 30; i++) {
                verificar(
                        fila.dequeue() == i,
                        "A fila circular deve manter a ordem FIFO."
                );
            }

            verificar(
                    fila.isEmpty(),
                    "A fila deve terminar vazia."
            );
        });

        executar("rejeitar elemento nulo", () -> {
            Fila<Integer> fila = new Fila<>();

            try {
                fila.enqueue(null);
            } catch (IllegalArgumentException esperado) {
                return;
            }

            throw new AssertionError(
                    "A inserção de null deve lançar IllegalArgumentException."
            );
        });

        executar("listagem FIFO não altera a fila", () -> {
            Fila<String> fila = new Fila<>();

            fila.enqueue("Ana");
            fila.enqueue("Bruno");

            Testes.saidaEsperada("Ana\nBruno", fila::listar);

            verificar(
                    fila.size() == 2 && "Ana".equals(fila.dequeue()),
                    "Listar não pode remover ou reordenar."
            );
        });

        executar("listagem vazia", () ->
                Testes.saidaEsperada("", new Fila<String>()::listar)
        );

        executar("dados da clínica: 15 chegadas válidas em ordem", () -> {
            Paciente[] pacientes = Clinica.criarPacientesDemonstracao();

            verificar(
                    pacientes.length == 15,
                    "Esperados 15 pacientes."
            );

            for (int i = 1; i < pacientes.length; i++) {
                verificar(
                        pacientes[i - 1].getHorarioChegada()
                                .compareTo(pacientes[i].getHorarioChegada()) <= 0,
                        "Chegadas precisam respeitar a ordem de registro."
                );
            }
        });

        executar("dados da impressão: 12 trabalhos e 75 páginas", () -> {
            TrabalhoImpressao[] trabalhos =
                    FilaImpressao.criarTrabalhosDemonstracao();

            int paginas = 0;

            for (TrabalhoImpressao trabalho : trabalhos) {
                paginas += trabalho.getNumeroPaginas();
            }

            verificar(
                    trabalhos.length == 12 && paginas == 75,
                    "Esperados 12 trabalhos e 75 páginas."
            );
        });

        executar("cancelar último inserido e preservar FIFO", () -> {
            Fila<Integer> fila = new Fila<>();
            fila.enqueue(1);
            fila.enqueue(2);
            fila.enqueue(3);
            verificar(fila.removerUltimo() == 3, "Deve cancelar o elemento inserido mais recentemente.");
            verificar(fila.size() == 2, "O tamanho deve diminuir após o cancelamento.");
            verificar(fila.dequeue() == 1 && fila.dequeue() == 2 && fila.isEmpty(),
                    "O cancelamento não pode alterar a ordem FIFO dos demais elementos.");
            try {
                fila.removerUltimo();
            } catch (NoSuchElementException esperado) {
                return;
            }
            throw new AssertionError("Cancelar em uma fila vazia deve lançar NoSuchElementException.");
        });
        TESTES.concluir();
    }

    private static void testarFilaVazia() {
        Fila<Integer> fila = new Fila<>();

        verificar(
                fila.isEmpty(),
                "Uma fila nova deve estar vazia."
        );

        verificar(
                fila.size() == 0,
                "Uma fila nova deve ter tamanho zero."
        );
    }

    private static void testarUmElemento() {
        Fila<String> fila = new Fila<>();

        fila.enqueue("A");

        verificar(
                "A".equals(fila.front()),
                "front deve consultar o primeiro elemento."
        );

        verificar(
                fila.size() == 1 && !fila.isEmpty(),
                "front não deve remover o elemento."
        );

        verificar(
                "A".equals(fila.dequeue()),
                "dequeue deve remover o primeiro elemento."
        );

        verificar(
                fila.isEmpty(),
                "A fila deve ficar vazia após a remoção."
        );
    }

    private static void testarVariosElementos() {
        Fila<Integer> fila = new Fila<>();

        fila.enqueue(10);
        fila.enqueue(20);
        fila.enqueue(30);

        verificar(
                fila.size() == 3,
                "O tamanho deve ser três."
        );

        verificar(
                fila.dequeue() == 10,
                "A fila deve respeitar a ordem de chegada."
        );

        verificar(
                fila.dequeue() == 20,
                "O segundo elemento deve ser removido depois."
        );

        verificar(
                fila.dequeue() == 30,
                "O último elemento deve sair por último."
        );
    }

    private static void testarElementosRepetidos() {
        Fila<Integer> fila = new Fila<>();

        fila.enqueue(7);
        fila.enqueue(7);

        verificar(
                fila.dequeue() == 7,
                "O primeiro valor repetido deve ser removido."
        );

        verificar(
                fila.dequeue() == 7,
                "O segundo valor repetido deve ser removido."
        );
    }

    private static void testarRemocaoEmFilaVazia() {
        Fila<Integer> fila = new Fila<>();

        try {
            fila.dequeue();
        } catch (NoSuchElementException esperado) {
            return;
        }

        throw new AssertionError(
                "dequeue vazio deve lançar NoSuchElementException."
        );
    }

    private static void executar(String nome, Runnable casoDeTeste) {
        TESTES.executar(nome, casoDeTeste);
    }

    private static void verificar(boolean condicao, String mensagem) {
        if (!condicao) {
            throw new AssertionError(mensagem);
        }
    }
}