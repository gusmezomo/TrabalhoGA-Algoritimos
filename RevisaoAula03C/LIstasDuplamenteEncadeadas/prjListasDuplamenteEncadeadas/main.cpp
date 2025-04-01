#include <iostream>
#include <cstdlib>
using namespace std;

class ListaDuplamenteEncadeada {
private:
    // Estrutura de cada nó da lista
    struct Elemento {
        int valor;
        Elemento* proximo;
        Elemento* anterior;
    };

    // Ponteiros para o início e fim da lista
    Elemento* inicio;
    Elemento* fim;
    int tamanho;

    // Função auxiliar para alocar um novo elemento na memória
    Elemento* alocarMemoria(int valor) {
        Elemento* novo = new Elemento;
        novo->valor = valor;
        novo->proximo = nullptr;
        novo->anterior = nullptr;
        return novo;
    }

public:
    // Construtor - inicializa a lista vazia
    ListaDuplamenteEncadeada() {
        inicio = nullptr;
        fim = nullptr;
        tamanho = 0;
    }

    // Destrutor - libera toda a memória alocada pela lista
    ~ListaDuplamenteEncadeada() {
        while (inicio != nullptr) {
            Elemento* atual = inicio;
            inicio = inicio->proximo;
            delete atual;
        }
    }

    // Remove o primeiro elemento da lista
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

    // Remove o último elemento da lista
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

    // Insere um novo elemento no início da lista
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

    // Insere um novo elemento no final da lista
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

    // Insere um novo elemento em uma posição específica da lista
    void inserirPosicao(int valor, int posicao) {
        posicao = posicao - 1; // ajusta para índice base 0
        Elemento* novo = alocarMemoria(valor);

        if (inicio == nullptr) {
            inicio = fim = novo;
        } else {
            Elemento* atual;
            int i;

            // Escolhe o melhor lado para começar a busca (início ou fim)
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
                // Conecta o novo elemento na posição correta
                novo->anterior = atual->anterior;
                novo->proximo = atual;

                if (atual->anterior != nullptr)
                    atual->anterior->proximo = novo;
                else
                    inicio = novo;

                atual->anterior = novo;
                tamanho++;

                // Mostra os vizinhos do novo nó inserido
                cout << "Valor antecessor ao que desejo inserir: " << (novo->anterior ? novo->anterior->valor : -1) << endl;
                cout << "Valor proximo ao que desejo inserir: " << (novo->proximo ? novo->proximo->valor : -1) << endl;
            }
        }
    }

    // Imprime os valores da lista do início ao fim
    void imprimirLista() {
        Elemento* atual = inicio;
        while (atual) {
            printf("%d\n", atual->valor);
        atual = atual->proximo;
        }
    }

    // Imprime os valores da lista do fim ao início
    void imprimirListaInversa() {
        Elemento* atual = fim;
        while (atual) {
            printf("%d\n", atual->valor);
        atual = atual->anterior;
        }
    }
};

int main() {
    // Cria uma lista duplamente encadeada
    ListaDuplamenteEncadeada lista;

    // Insere 10 valores aleatórios no início da lista
    for (int i = 0; i < 10; i++)
        lista.inserirInicio(rand());

    // Insere o valor 1000 na posição 2
    lista.inserirPosicao(1000, 2);

    // Imprime os valores da lista
    printf("Imprimir lista atual ...\n");
    lista.imprimirLista();

    // Imprime a lista ao contrário (opcional)
    // cout << "Imprimir lista inversa ..." << endl;
    // lista.imprimirListaInversa();

    return 0;
}
