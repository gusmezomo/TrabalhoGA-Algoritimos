#include <iostream>
#include <cstdlib>
using namespace std;

class ListaDuplamenteEncadeada {
private:
    struct Elemento {
        int valor;
        Elemento* proximo;
        Elemento* anterior;
    };

    Elemento* inicio;
    Elemento* fim;
    int tamanho;

    Elemento* alocarMemoria(int valor) {
        Elemento* novo = new Elemento;
        novo->valor = valor;
        novo->proximo = nullptr;
        novo->anterior = nullptr;
        return novo;
    }

public:
    ListaDuplamenteEncadeada() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    ~ListaDuplamenteEncadeada() {
        while (inicio != nullptr) {
            Elemento* atual = inicio;
            inicio = inicio->proximo;
            delete atual;
        }
    }

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

    void inserirInicio(int valor) {
        Elemento* novo = alocarMemoria(valor);

        if (inicio == nullptr) {
            inicio = fim = novo;
        } else {
            novo->proximo = inicio;
            inicio->anterior = novo;
            inicio = novo;
        }

        tamanho++;
    }

    void inserirFim(int valor) {
        Elemento* novo = alocarMemoria(valor);

        if (inicio == nullptr) {
            inicio = fim = novo;
        } else {
            novo->anterior = fim;
            fim->proximo = novo;
            fim = novo;
        }

        tamanho++;
    }

    void inserirPosicao(int valor, int posicao) {
        posicao = posicao - 1;
        Elemento* novo = alocarMemoria(valor);

        if (inicio == nullptr) {
            inicio = fim = novo;
        } else {
            Elemento* atual;
            int i;

            if (posicao < (tamanho / 2)) {
                atual = inicio;
                i = 0;
                while (i < posicao && atual != nullptr) {
                    atual = atual->proximo;
                    i++;
                }
            } else {
                atual = fim;
                i = tamanho - 1;
                while (i > posicao && atual != nullptr) {
                    atual = atual->anterior;
                    i--;
                }
            }

            if (atual != nullptr) {
                novo->anterior = atual->anterior;
                novo->proximo = atual;
                if (atual->anterior != nullptr)
                    atual->anterior->proximo = novo;
                else
                    inicio = novo;

                atual->anterior = novo;
                tamanho++;

                cout << "Valor antecessor ao que desejo inserir: " << (novo->anterior ? novo->anterior->valor : -1) << endl;
                cout << "Valor proximo ao que desejo inserir: " << (novo->proximo ? novo->proximo->valor : -1) << endl;
            }
        }
    }

    void imprimirLista() {
        Elemento* atual = inicio;
        while (atual) {
            cout << atual->valor << endl;
            atual = atual->proximo;
        }
    }

    void imprimirListaInversa() {
        Elemento* atual = fim;
        while (atual) {
            cout << atual->valor << endl;
            atual = atual->anterior;
        }
    }
};

int main() {
    ListaDuplamenteEncadeada lista;

    for (int i = 0; i < 10; i++)
        lista.inserirInicio(rand());

    lista.inserirPosicao(1000, 2);

    cout << "Imprimir lista atual ..." << endl;
    lista.imprimirLista();

    // cout << "Imprimir lista inversa ..." << endl;
    // lista.imprimirListaInversa();

    return 0;
}
