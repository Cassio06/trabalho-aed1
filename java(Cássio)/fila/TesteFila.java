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
            throw new AssertionError("front vazio deve lançar NoSuchElementException.");
        });
        executar("intercalar inserções e remoções e reutilizar fila", () -> {
            Fila<Integer> fila = new Fila<>();
            fila.enqueue(1);
            fila.enqueue(2);
            verificar(fila.dequeue() == 1, "Primeira saída deve ser 1.");
            fila.enqueue(3);
            verificar(fila.size() == 2, "Esperados dois elementos após intercalar operações.");
            verificar(fila.dequeue() == 2 && fila.dequeue() == 3, "Saídas devem ser 2 e 3.");
            verificar(fila.size() == 0 && fila.isEmpty(), "Fila deve terminar vazia.");
            fila.enqueue(4);
            verificar(fila.front() == 4 && fila.dequeue() == 4, "Fila esvaziada deve ser reutilizável.");
        });
        executar("listagem FIFO não altera a fila", () -> {
            Fila<String> fila = new Fila<>();
            fila.enqueue("Ana");
            fila.enqueue("Bruno");
            Testes.saidaEsperada("Ana\nBruno", fila::listar);
            verificar(fila.size() == 2 && "Ana".equals(fila.dequeue()), "Listar não pode remover ou reordenar.");
        });
        executar("listagem vazia", () -> Testes.saidaEsperada("", new Fila<String>()::listar));
        executar("dados da clínica: 15 chegadas válidas em ordem", () -> {
            Paciente[] pacientes = Clinica.criarPacientesDemonstracao();
            verificar(pacientes.length == 15, "Esperados 15 pacientes.");
            for (int i = 1; i < pacientes.length; i++) {
                verificar(pacientes[i - 1].getHorarioChegada().compareTo(pacientes[i].getHorarioChegada()) <= 0,
                        "Chegadas precisam respeitar a ordem de registro.");
            }
        });
        executar("dados da impressão: 12 trabalhos e 75 páginas", () -> {
            TrabalhoImpressao[] trabalhos = FilaImpressao.criarTrabalhosDemonstracao();
            int paginas = 0;
            for (TrabalhoImpressao trabalho : trabalhos) paginas += trabalho.getNumeroPaginas();
            verificar(trabalhos.length == 12 && paginas == 75, "Esperados 12 trabalhos e 75 páginas.");
        });
        TESTES.concluir();
    }

    private static void testarFilaVazia() {
        Fila<Integer> fila = new Fila<>();
        verificar(fila.isEmpty(), "uma fila nova deve estar vazia");
        verificar(fila.size() == 0, "uma fila nova deve ter tamanho zero");
    }

    private static void testarUmElemento() {
        Fila<String> fila = new Fila<>();
        fila.enqueue("A");
        verificar("A".equals(fila.front()), "front deve consultar o primeiro elemento");
        verificar(fila.size() == 1 && !fila.isEmpty(), "front não deve remover o elemento");
        verificar("A".equals(fila.dequeue()), "dequeue deve remover o primeiro elemento");
        verificar(fila.isEmpty(), "a fila deve ficar vazia após a remoção");
    }

    private static void testarVariosElementos() {
        Fila<Integer> fila = new Fila<>();
        fila.enqueue(10);
        fila.enqueue(20);
        fila.enqueue(30);

        verificar(fila.size() == 3, "o tamanho deve ser três");
        verificar(fila.dequeue() == 10, "a fila deve respeitar a ordem de chegada");
        verificar(fila.dequeue() == 20, "o segundo elemento deve ser removido depois");
        verificar(fila.dequeue() == 30, "o último elemento deve sair por último");
    }

    private static void testarElementosRepetidos() {
        Fila<Integer> fila = new Fila<>();
        fila.enqueue(7);
        fila.enqueue(7);

        verificar(fila.dequeue() == 7, "o primeiro valor repetido deve ser removido");
        verificar(fila.dequeue() == 7, "o segundo valor repetido deve ser removido");
    }

    private static void testarRemocaoEmFilaVazia() {
        Fila<Integer> fila = new Fila<>();
        try {
            fila.dequeue();
        } catch (NoSuchElementException esperado) {
            return;
        }
        throw new AssertionError("dequeue vazio deve lançar NoSuchElementException.");
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
