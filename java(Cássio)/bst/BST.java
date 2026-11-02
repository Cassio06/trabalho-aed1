package bst;

/** Busca/remoção ausentes retornam null; inserir chave repetida atualiza seu valor.
 * Listagens imprimem um valor por linha; árvore vazia não imprime valores. */
public class BST<K extends Comparable<K>, V> {
    private class No {
        K chave;
        V valor;
        No esquerda;
        No direita;

        No(K chave, V valor) {
            this.chave = chave;
            this.valor = valor;
        }
    }

    private No raiz;

    private No menorNo(No atual) {
        while (atual.esquerda != null) {
            atual = atual.esquerda;
        }

        return atual;
    }

    public void inserir(K chave, V valor) {
        raiz = inserir(raiz, chave, valor);
    }

    private No inserir(No atual, K chave, V valor) {
        if (atual == null) {
            return new No(chave,valor);
        }
        int comparacao = chave.compareTo(atual.chave);
        if (comparacao < 0) {
            atual.esquerda = inserir(atual.esquerda, chave, valor);
        } else if (comparacao > 0) {
            atual.direita = inserir(atual.direita, chave, valor);
        } else {
            atual.valor = valor;
        }
        return atual;
    }

    public V buscar(K chave) {
        No atual = raiz;

        while(atual != null){
            int comparacao = chave.compareTo(atual.chave);

            if(comparacao == 0){
                return atual.valor;
            } else if(comparacao < 0){
                atual = atual.esquerda;
            } else{
                atual = atual.direita;
            }
        }
        return null;
    }

    public V remover(K chave) {
        V valorRemovido = buscar(chave);
        raiz = remover(raiz,chave);
        return valorRemovido;
    }

    private No remover(No atual, K chave){
        if(atual == null){
            return null;
        }
        int comparacao = chave.compareTo(atual.chave);

        if(comparacao < 0){
            atual.esquerda = remover(atual.esquerda, chave);
        } else if(comparacao > 0){
            atual.direita = remover(atual.direita, chave);

        }else{
            if(atual.esquerda == null && atual.direita == null){
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
        return atual;
    }

    public void listarEmOrdem() {
        listarEmOrdem(raiz);
    }
    
    private void listarEmOrdem(No atual) {
        if(atual == null){
            return;
        }
        listarEmOrdem(atual.esquerda);
        System.out.println(atual.valor);
        listarEmOrdem(atual.direita);
    }

    /** Usado com chaves String normalizadas; prefixo vazio lista todos. */
    public void listarPorPrefixo(String prefixo) {
        listarPorPrefixo(raiz, prefixo);
    }
    private void listarPorPrefixo(No atual, String prefixo) {
        if (atual == null) {
            return;
        }
        String chaveAtual = atual.chave.toString();

        int comparacao = chaveAtual.compareTo(prefixo);

        if(comparacao > 0){
            listarPorPrefixo(atual.esquerda, prefixo);

        }
        if(chaveAtual.startsWith(prefixo)){
            System.out.println(atual.valor);

        }
        if(comparacao<0 || chaveAtual.startsWith(prefixo)){
            listarPorPrefixo(atual.direita, prefixo);
        }
    }
}


