package fila;

import java.util.NoSuchElementException;

public class Fila<T> {

    private Object[] elementos = new Object[20];
    private int inicio = 0;
    private int fim = 0;
    private int quantidade = 0;


    public void enqueue(T elemento) {
        if(quantidade == elementos.length){
            throw new IllegalStateException("A fila está cheia.");
        }
        if(elemento == null){
            throw new IllegalArgumentException("O elemento é nulo.");
        }
        elementos[fim] = elemento;
        quantidade++;
        fim = (fim + 1) % elementos.length;
    }

    @SuppressWarnings("unchecked")
    public T dequeue() {
        if(isEmpty()){
            throw new NoSuchElementException("A fila está vazia.");

        }
        T removido = (T) elementos[inicio];
        elementos[inicio] = null;
        inicio = (inicio + 1) % elementos.length;
        quantidade--;

        return removido;
    }

    @SuppressWarnings("unchecked")
    public T front() {
        if(isEmpty()){
            throw new NoSuchElementException("A fila está vazia.");

        }

        return (T) elementos[inicio];

    }

    /** Remove o elemento inserido mais recentemente que ainda aguarda na fila. */
    @SuppressWarnings("unchecked")
    public T removerUltimo() {
        if (isEmpty()) {
            throw new NoSuchElementException("A fila está vazia.");
        }
        fim = (fim - 1 + elementos.length) % elementos.length;
        T removido = (T) elementos[fim];
        elementos[fim] = null;
        quantidade--;
        return removido;
    }

    public boolean isEmpty() {
       return quantidade == 0;
    }

    public int size() {
      return quantidade;
    }

    public void listar() {
        for(int i = 0; i < quantidade; i++){
            int indice = (inicio + i) % elementos.length;
            System.out.println(elementos[indice]);
        }
    }
}
