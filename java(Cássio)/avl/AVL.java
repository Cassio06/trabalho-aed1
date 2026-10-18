package avl;


/** Busca/remoção ausentes retornam null; chave repetida atualiza valor.
 * Altura em nós: vazia = 0, folha = 1. Fator = altura esquerda - altura direita. */
public class AVL<K extends Comparable<K>, V> {

    private class No{
        K chave;
        V valor;
        No esquerda;
        No direita;
        int altura;

        No(K chave, V valor) {
            this.chave = chave;
            this.valor = valor;
            this.altura = 1;
        }
    }

    private No raiz;


    private No rotacionarDireita(No atual) {
        No filhoEsquerdo = atual.esquerda;
        No subarvoreMovida = filhoEsquerdo.direita;
        filhoEsquerdo.direita = atual;
        atual.esquerda = subarvoreMovida;
        atualizarAltura(atual);
        atualizarAltura(filhoEsquerdo);
        return filhoEsquerdo;
    }

    private No rotacionarEsquerda(No atual) {
        No filhoDireito = atual.direita;
        No subarvoreMovida = filhoDireito.esquerda;
        filhoDireito.esquerda = atual;
        atual.direita = subarvoreMovida;
        atualizarAltura(atual);
        atualizarAltura(filhoDireito);
        return filhoDireito;
    }

    private No rebalancear(No atual) {
        atualizarAltura(atual);

        int fator = fatorBalanceamento(atual);

        if (fator > 1) {
          if(fatorBalanceamento(atual.esquerda) < 0){
              atual.esquerda = rotacionarEsquerda(atual.esquerda);
          }
            return rotacionarDireita(atual);
        }

        if (fator < -1) {
            if(fatorBalanceamento(atual.direita) > 0 ){
                atual.direita = rotacionarDireita(atual.direita);
            }
            return rotacionarEsquerda(atual);
        }

        return atual;
    }

    private No menorNo(No atual) {
        while (atual.esquerda != null) {
            atual = atual.esquerda;
        }

        return atual;
    }


    public void inserir(K chave, V valor) {
        raiz = inserir(raiz, chave, valor);
    }

    private No inserir(No atual, K chave, V valor){
        if(atual == null){
            return new No(chave,valor);

        }
        int comparacao = chave.compareTo(atual.chave);

        if(comparacao < 0){
            atual.esquerda = inserir(atual.esquerda, chave, valor);
        } else if(comparacao > 0 ){
            atual.direita = inserir(atual.direita, chave, valor);
        }else{
            atual.valor = valor;
        }

        return rebalancear(atual);

    }

    public V buscar(K chave) {
        No atual = raiz;

        while (atual != null) {
            int comparacao = chave.compareTo(atual.chave);

            if(comparacao == 0){
                return atual.valor;
            } else if(comparacao < 0){
                atual = atual.esquerda;
            }else{
                atual = atual.direita;
            }

        }

        return null;
    }

    public V remover(K chave) {
        V valorRemovido = buscar(chave);
        raiz = remover(raiz, chave);
        return valorRemovido;
    }

    private No remover(No atual, K chave) {
        if (atual == null) {
            return null;
        }

        int comparacao = chave.compareTo(atual.chave);

        if (comparacao < 0) {
            atual.esquerda = remover(atual.esquerda, chave);
        } else if (comparacao > 0) {
            atual.direita = remover(atual.direita, chave);
        } else {
            if (atual.esquerda == null && atual.direita == null) {
                return null;
            }

            if (atual.esquerda == null) {
                return atual.direita;
            }

            if (atual.direita == null) {
                return atual.esquerda;
            }

            No sucessor = menorNo(atual.direita);

            atual.chave = sucessor.chave;
            atual.valor = sucessor.valor;

            atual.direita = remover(atual.direita, sucessor.chave);
        }

        return rebalancear(atual);
    }

    public int altura() {
        return altura(raiz);
    }

    private int altura(No atual) {
        if (atual == null) {
            return 0;
        }

        return atual.altura;
    }

    private void atualizarAltura(No atual) {
        atual.altura = 1 + Math.max(
                altura(atual.esquerda),
                altura(atual.direita)
        );
    }

    public int fatorBalanceamento() {
        return fatorBalanceamento(raiz);
    }

    private int fatorBalanceamento(No atual) {
        if (atual == null) {
            return 0;
        }

        return altura(atual.esquerda) - altura(atual.direita);
    }


    public boolean estaBalanceada() {
        return alturaVerificada(raiz) >= 0;
    }

    private int alturaVerificada(No atual) {
        if (atual == null) {
            return 0;
        }

        int alturaEsquerda = alturaVerificada(atual.esquerda);

        if (alturaEsquerda == -1) {
            return -1;
        }

        int alturaDireita = alturaVerificada(atual.direita);

        if (alturaDireita == -1) {
            return -1;
        }

        int alturaReal = 1 + Math.max(alturaEsquerda, alturaDireita);

        if (Math.abs(alturaEsquerda - alturaDireita) > 1
                || atual.altura != alturaReal) {
            return -1;
        }

        return alturaReal;
    }

    public void listarMaiores(int quantidade) {
        if (quantidade <= 0) {
            return;
        }

        listarMaiores(raiz, quantidade);
    }
    private int listarMaiores(No atual, int restantes){
        if (atual == null || restantes == 0) {
            return restantes;
        }

        restantes = listarMaiores(atual.direita, restantes);

        if(restantes == 0){
            return 0;
        }

        System.out.println(atual.valor);
        restantes--;

        return listarMaiores(atual.esquerda,restantes);


    }
}
