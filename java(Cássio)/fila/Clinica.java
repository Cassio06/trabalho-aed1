package fila;

import apoio.Dados;
import apoio.Entrada;
import apoio.Pendencia;
import java.time.Duration;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.Scanner;

public class Clinica {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            Entrada.executar(() -> executar(new Entrada(scanner)));
        }
    }

    private static void executar(Entrada entrada) {
        System.out.println("Clínica: atendimento FIFO, estimativa de 10 minutos por paciente.");
        int modo = entrada.inteiro("1 - Simular 15 pacientes; 2 - Cadastrar 15 pacientes; 0 - Sair: ", 0, 2);
        if (modo == 0) return;
        Paciente[] pacientes = modo == 1 ? criarPacientesDemonstracao() : cadastrar(entrada);
        System.out.println("Chegadas (mesmo dia, em ordem de registro):");
        for (Paciente paciente : pacientes) System.out.println(paciente);
        Fila<Paciente> fila = new Fila<>();
        LocalTime ultimoHorario = LocalTime.parse(pacientes[pacientes.length - 1].getHorarioChegada());
        // Somente histórico de atendimentos; a fila real é sempre a Fila<T>.
        Paciente[] atendidos = new Paciente[200];
        int quantidade = 0;
        long esperaTotal = 0;
        LocalDateTime inicio = LocalDateTime.of(2026, 8, 3, 8, 0);
        try {
            for (Paciente paciente : pacientes) fila.enqueue(paciente);
        } catch (UnsupportedOperationException excecao) {
            Pendencia.mostrar(excecao);
            return;
        }
        while (true) {
            int opcao = entrada.inteiro("\n1 - Chegada; 2 - Chamar próximo; 3 - Consultar próximo; "
                    + "4 - Tamanho; 5 - Atender todos; 6 - Relatório; 0 - Sair: ", 0, 6);
            if (opcao == 0) {
                relatorio(atendidos, quantidade, esperaTotal);
                return;
            }
            try {
                switch (opcao) {
                    case 1 -> {
                        if (quantidade + fila.size() >= atendidos.length) {
                            System.out.println("Limite de 200 registros para este dia.");
                            break;
                        }
                        Paciente paciente = lerPaciente(entrada, ultimoHorario);
                        fila.enqueue(paciente);
                        ultimoHorario = LocalTime.parse(paciente.getHorarioChegada());
                        System.out.println("Chegada registrada: " + paciente);
                    }
                    case 2, 5 -> {
                        if (fila.isEmpty()) {
                            System.out.println("Não há pacientes aguardando.");
                            break;
                        }
                        do {
                            Paciente paciente = fila.dequeue();
                            LocalDateTime chegada = LocalDate.of(2026, 8, 3)
                                    .atTime(LocalTime.parse(paciente.getHorarioChegada()));
                            if (inicio.isBefore(chegada)) inicio = chegada;
                            long espera = Duration.between(chegada, inicio).toMinutes();
                            atendidos[quantidade++] = paciente;
                            esperaTotal += espera;
                            System.out.println("Chamado às " + inicio.toLocalTime() + ": " + paciente
                                    + " | espera estimada: " + espera + " min");
                            inicio = inicio.plusMinutes(10);
                        } while (opcao == 5 && !fila.isEmpty());
                    }
                    case 3 -> System.out.println(fila.isEmpty() ? "Fila vazia." : "Próximo: " + fila.front());
                    case 4 -> System.out.println("Aguardando: " + fila.size());
                    case 6 -> relatorio(atendidos, quantidade, esperaTotal);
                    default -> throw new IllegalStateException("Opção inesperada.");
                }
            } catch (UnsupportedOperationException excecao) {
                Pendencia.mostrar(excecao);
            }
        }
    }

    private static void relatorio(Paciente[] atendidos, int quantidade, long esperaTotal) {
        System.out.println("\nOrdem efetiva de atendimento: " + quantidade + " paciente(s)");
        for (int i = 0; i < quantidade; i++) System.out.println((i + 1) + " - " + atendidos[i]);
        if (quantidade == 0) System.out.println("Sem atendimentos; média ainda não calculada.");
        else System.out.printf("Espera média estimada: %.2f min%n", (double) esperaTotal / quantidade);
    }

    static Paciente[] criarPacientesDemonstracao() {
        Paciente[] pacientes = new Paciente[15];
        String[] tipos = {"Consulta", "Exame", "Retorno"};
        for (int i = 0; i < pacientes.length; i++) {
            pacientes[i] = new Paciente(Dados.nome(i), LocalTime.of(8, 5).plusMinutes(i * 7L).toString(),
                    tipos[i % tipos.length]);
        }
        return pacientes;
    }

    private static Paciente[] cadastrar(Entrada entrada) {
        Paciente[] pacientes = new Paciente[15];
        LocalTime anterior = LocalTime.MIDNIGHT;
        for (int i = 0; i < pacientes.length; i++) {
            System.out.println("Paciente " + (i + 1) + " de " + pacientes.length);
            pacientes[i] = lerPaciente(entrada, anterior);
            anterior = LocalTime.parse(pacientes[i].getHorarioChegada());
        }
        return pacientes;
    }

    private static Paciente lerPaciente(Entrada entrada, LocalTime anterior) {
        String nome = entrada.texto("Nome: ");
        String horario;
        do {
            horario = entrada.horario("Horário de chegada (HH:mm): ");
            if (!LocalTime.parse(horario).isBefore(anterior)) break;
            System.out.println("Informe chegada a partir de " + anterior + ", no mesmo dia.");
        } while (true);
        return new Paciente(nome, horario, entrada.texto("Tipo de atendimento: "));
    }
}
