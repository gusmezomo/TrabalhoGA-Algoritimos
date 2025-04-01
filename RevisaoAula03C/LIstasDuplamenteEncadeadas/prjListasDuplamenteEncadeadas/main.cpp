// LISTA DUPLAMENTE ENCADEADA
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

typedef struct elemento Elemento;
struct elemento
{
    int valor;
    Elemento *proximo;
    Elemento *anterior;
};

// Criar 2 vari�veis globais.
Elemento *inicio;
Elemento *fim;
int tamanho;

// Criar 2 elemmentos nulos na lista.
void criarLista()
{
    inicio = NULL;
    fim = NULL;
    tamanho = 0;
}

// Alocar um dado, e como funciona o esquema do lista duplamente encadeada:
Elemento *alocarMemoria(int valor)
{
    //Aloca��o de mem�ria p/ pr�ximo elemento
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));

    novo -> valor = valor;
    novo -> anterior = NULL;
    novo -> proximo = NULL;

    return novo;
}

void removerInicio()
{
    Elemento *atual = inicio;

    inicio = atual->proximo;
    inicio->anterior = NULL;
    tamanho--;
}

void removerFim()
{
    Elemento *atual = fim;

    fim = atual->anterior;
    fim->proximo = NULL;
    tamanho--;
}

// Inserir no inicio da lista:
void inserirInicio(int valor)
{
    Elemento *novo = alocarMemoria(valor); // criar novo elemento alocando mem�ria

    // verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo tamb�m, pois se os dois s�o nulos o inico e fim recebe o novo.
    if (inicio == NULL)
    {
        inicio = novo;
        fim = novo;
    }
    else
    {
        Elemento *atual; // criar novo elemento caso tenha dado no inicio da lista.

        atual = inicio;
        novo->proximo = atual;
        atual->anterior = novo;
        inicio = novo;
    }

    tamanho++;
}

// Inserir no fim da lista:
void inserirFim(int valor)
{
    Elemento *novo = alocarMemoria(valor); // criar novo elemento alocando mem�ria

    // verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo tamb�m, pois se os dois s�o nulos o inico e fim recebe o novo.
    if (inicio == NULL)
    {
        inicio = novo;
        fim = novo;
    }
    else
    {
        Elemento *atual;

        atual = fim;
        novo->anterior = atual;
        atual->proximo = novo;
        fim = novo;
    }

    tamanho++;
}

// Inserir no inicio da lista:
void inserirPosicao(int valor, int posicao)
{
    posicao = posicao - 1;
    Elemento *novo = alocarMemoria(valor); // criar novo elemento alocando mem�ria

    // verificar se o inicio for nulo, se sim, inicio recebe novo e o fim vai ser novo tamb�m, pois se os dois s�o nulos o inico e fim recebe o novo.
    if (inicio == NULL)
    {
        inicio = novo;
        fim = novo;

    }
    else
    {
        Elemento *atual; // criar novo elemento caso tenha dado no inicio da lista.
        Elemento *tmp;
        int i;

        // Decidindo o ponto de incio
        if (posicao < (tamanho / 2))
        {
            atual = inicio;
            i = 0;
        }
        else
        {
            atual = fim;
            i = tamanho;
        }

        // Percorrer para encontrar a posi��o
        while ((i != posicao) && (i >= 0) && (i <= tamanho))
        {
            if (i < posicao)
            {
                i++;
                atual = atual->proximo;
            }
            else if (i > posicao)
            {
                i--;
                atual = atual->anterior;
            }

            if (posicao == i)
            {
                printf("Valor antecessor ao que desejo inserir %d\n", atual->anterior->valor);
                printf("Valor proximo ao que desejo inserir %d\n", atual->proximo->valor);
            }
        }
    }

}

// Fun��o para imprimir a lista:
void imprimirLista()
{
    Elemento *atual;
    atual = inicio;

    while (atual)
    {
        printf("%d\n", atual->valor);
        atual = atual->proximo;
    }
}

// Fun��o para imprimir a lista:
void imprimirListaInversa()
{
    Elemento *atual;
    atual = fim;

    while (atual)
    {
        printf("%d\n", atual->valor);
        atual = atual->anterior;
    }
}

int main()
{
    //Criar a lista em mem�ria
    criarLista();

    for (int i = 0; i < 10; i++)
        inserirInicio(rand());

    //Inserir na posi��o espec�fica
    inserirPosicao(1000, 2);

    printf("Imprimir lista atual ...\n");
    imprimirLista();

    //printf("Imprimir lista inversa ...\n");
    //imprimirListaInversa();
}