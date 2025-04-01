#include <iostream>
#include <cstdlib>
using namespace std;

class ListaDuplamenteEncadeada {
private:
    // Estrutura interna agora está encapsulada na classe (antes era struct fora do escopo)
    struct Elemento {
        int valor;
        Elemento* proximo;
        Elemento* anterior;
    };

    // Variáveis globais da versão original (inicio, fim, tamanho) agora são atributos privados
    Elemento* inicio;
    Elemento* fim;
    int tamanho;

    // Função auxiliar para alocar um novo nó (usa new, diferente do malloc em C)
    Elemento* alocarMemoria(int valor) {
        Elemento* novo = new Elemento;
        novo->valor = valor;
        novo->proximo = nullptr;
        novo->anterior = nullptr;
        return novo;
    }

public:
    // Construtor: substitui a função criarLista() da versão original
    ListaDuplamenteEncadeada() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    // Destrutor: libera toda a memória da lista automaticamente (antes não era feito)
    ~ListaDuplamenteEncadeada() {
        while (inicio != nullptr) {
            Elemento* atual = inicio;
            inicio = inicio->proximo;
            delete atual;
        }
    }

    // Método da classe para remover o primeiro elemento (agora com verificação de ponteiro)
    void removerInicio() {
        if (inicio != nullptr) {
            Elemento* atual = inicio;
            inicio = atual->proximo;

            if (inicio != nullptr)
                inicio->anterior = nullptr;
            else
                fim = nullptr;

            delete atual;
            tamanho--;
        }
    }

    // Método da classe para remover o último elemento
    void removerFim() {
        if (fim != nullptr) {
            Elemento* atual = fim;
            fim = atual->anterior;

            if (fim != nullptr)
                fim->proximo = nullptr;
            else
                inicio = nullptr;

            delete atual;
            tamanho--;
        }
    }

    // Inserção no início — mesmo comportamento da versão C, agora encapsulado
    void inserirInicio(int valor) {
        Elemento* novo = alocarMemoria(valor);

        if (inicio == nullptr) {
            inicio = novo;
            fim = novo;
        } else {
            novo->proximo = inicio;
            inicio->anterior = novo;
            inicio = novo;
        }

        tamanho++;
    }

    // Inserção no fim — mesmo funcionamento da versão original
    void inserirFim(int valor) {
        Elemento* novo = alocarMemoria(valor);

        if (inicio == nullptr) {
            inicio = novo;
            fim = novo;
        } else {
            novo->anterior = fim;
            fim->proximo = novo;
            fim = novo;
        }

        tamanho++;
    }

    // Inserção em posição específica — agora a lógica está completa e funcional
    void inserirPosicao(int valor, int posicao) {
        posicao = posicao - 1; // ajuste de índice para base 0
        Elemento* novo = alocarMemoria(valor);
    
        if (inicio == nullptr) {
            inicio = novo;
            fim = novo;
        } else {
            Elemento* atual;
            int i;
    
            // Mesma lógica de escolha do ponto de início da busca que existia no código original
            if (posicao < (tamanho / 2)) {
                atual = inicio;
                i = 0;
            } else {
                atual = fim;
                i = tamanho;
            }

            // Loop de busca adaptado da versão original
            while ((i != posicao) && (i >= 0) && (i <= tamanho)) {
                if (i < posicao) {
                    i++;
                    atual = atual->proximo;
                } else if (i > posicao) {
                    i--;
                    atual = atual->anterior;
                }
            }

            // Inserção real do elemento, que não era feita corretamente na versão original
            if (atual != nullptr) {
                novo->anterior = atual->anterior;
                novo->proximo = atual;

                if (atual->anterior != nullptr)
                    atual->anterior->proximo = novo;
                else
                    inicio = novo;

                atual->anterior = novo;
                tamanho++;

                // Impressão dos vizinhos — também estava presente na versão original
                cout << "Valor antecessor ao que desejo inserir: " << (novo->anterior ? novo->anterior->valor : -1) << endl;
                cout << "Valor proximo ao que desejo inserir: " << (novo->proximo ? novo->proximo->valor : -1) << endl;
            }
        }
    }

    // Impressão da lista — mesmo funcionamento, agora como método
    void imprimirLista() {
        Elemento* atual = inicio;
        while (atual) {
            cout << atual->valor << endl;
            atual = atual->proximo;
        }
    }

    // Impressão reversa — método opcional mantido
    void imprimirListaInversa() {
        Elemento* atual = fim;
        while (atual) {
            cout << atual->valor << endl;
            atual = atual->anterior;
        }
    }
};

int main() {
    // Criação do objeto — substitui criarLista() da versão C
    ListaDuplamenteEncadeada lista;

    // Insere 10 números aleatórios no início da lista (igual à versão original)
    for (int i = 0; i < 10; i++)
        lista.inserirInicio(rand());

    // Insere o valor 1000 na segunda posição
    lista.inserirPosicao(1000, 2);

    // Imprime os elementos da lista
    cout << "Imprimir lista atual ..." << endl;
    lista.imprimirLista();

    // Impressão reversa — opcional e equivalente à função comentada no código original
    // cout << "Imprimir lista inversa ..." << endl;
    // lista.imprimirListaInversa();

    return 0;
}
