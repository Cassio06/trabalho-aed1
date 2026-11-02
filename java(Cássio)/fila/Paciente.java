package fila;

import apoio.Validacao;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.time.format.DateTimeParseException;
import java.time.format.ResolverStyle;

public class Paciente {

    private final String nome;
    private final String horarioChegada;
    private final String tipoAtendimento;

    public Paciente(String nome, String horarioChegada, String tipoAtendimento) {
        this.nome = Validacao.texto(nome, "Nome");
        this.horarioChegada = validarHorario(horarioChegada);
        this.tipoAtendimento = Validacao.texto(tipoAtendimento, "Tipo de atendimento");
    }

    public String getNome() {
        return nome;
    }

    public String getHorarioChegada() {
        return horarioChegada;
    }

    public String getTipoAtendimento() {
        return tipoAtendimento;
    }

    @Override
    public String toString() {
        return nome + " - chegada: " + horarioChegada + " - atendimento: " + tipoAtendimento;
    }

    private static String validarHorario(String valor) {
        String horario = Validacao.texto(valor, "Horário de chegada");
        try {
            LocalTime.parse(horario, DateTimeFormatter
                    .ofPattern("HH:mm").withResolverStyle(ResolverStyle.STRICT));
        } catch (DateTimeParseException excecao) {
            throw new IllegalArgumentException("Horário de chegada deve ser válido no formato HH:mm.");
        }
        return horario;
    }
}
