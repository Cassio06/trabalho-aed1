package avl;

import apoio.Dados;
import apoio.Entrada;
import apoio.Pendencia;
import java.util.Locale;
import java.util.Scanner;

public class IndiceCpf {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        Funcionario[] funcionarios = criarFuncionariosDemonstracao();
        AVL<String, Funcionario> indice = new AVL<>();
        System.out.println("Base inicial: " + funcionarios.length + " funcionários; CPFs fictícios, validação de formato.");
        for (Funcionario funcionario : funcionarios) System.out.println(funcionario);
        try {
            for (Funcionario funcionario : funcionarios) indice.inserir(funcionario.getCpf(), funcionario);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
            return;
        }
        while (true) {
            int opcao = entrada.inteiro("\n1 - Cadastrar/atualizar; 2 - Buscar; 3 - Remover; "
                    + "4 - Verificar altura e balanceamento; 0 - Sair: ", 0, 4);
            if (opcao == 0) return;
            try {
                if (opcao == 4) {
                    System.out.println("Altura: " + indice.altura());
                    System.out.println("Fator da raiz: " + indice.fatorBalanceamento());
                    System.out.println("Todos os nós balanceados: " + indice.estaBalanceada());
                } else {
                    String cpf = entrada.cpf("CPF: ");
                    if (opcao == 1) {
                        Funcionario funcionario = new Funcionario(cpf, entrada.texto("Nome: "), entrada.texto("Cargo: "));
                        indice.inserir(cpf, funcionario);
                        System.out.println("Funcionário salvo: " + funcionario);
                    } else {
                        Funcionario funcionario = opcao == 2 ? indice.buscar(cpf) : indice.remover(cpf);
                        System.out.println(funcionario == null ? "CPF não encontrado."
                                : (opcao == 2 ? "Encontrado: " : "Removido: ") + funcionario);
                    }
                }
            } catch (UnsupportedOperationException excecao) {
                Pendencia.mostrar(excecao);
            }
        }
    }

    static Funcionario[] criarFuncionariosDemonstracao() {
        Funcionario[] funcionarios = new Funcionario[25];
        String[] cargos = {"Analista", "Assistente", "Coordenador", "Técnico", "Gerente"};

        for (int i = 0; i < funcionarios.length; i++) {
            String cpf = String.format(Locale.ROOT, "731.205.%03d-%02d", i + 100, (i * 7) % 100);
            funcionarios[i] = new Funcionario(cpf, Dados.nome(i), cargos[i % cargos.length]);
        }

        return funcionarios;
    }
}
