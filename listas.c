#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int dado;
    struct No* proximo;
    struct No* anterior;
} No;

No* criarNo(int dado) 
{
    No* novoNo = (No*)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(1);
    }
    novoNo->dado = dado;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;
    return novoNo;
}

void inserirNoInicio(No** cabeca, int dado) 
{

    No* novoNo = criarNo(dado);
    novoNo->proximo = *cabeca;
    if (*cabeca != NULL) {
        (*cabeca)->anterior = novoNo;
    }
    *cabeca = novoNo;
}

void inserirNoFim(No** cabeca, int dado) 
{

    No* novoNo = criarNo(dado);
    if (*cabeca == NULL) {
        *cabeca = novoNo;
        return;
    }
    No* temp = *cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }
    temp->proximo = novoNo;
    novoNo->anterior = temp;
}

void inserirNaPosicao(No** cabeca, int dado, int posicao)
{

    if (posicao < 1) {
        printf("Erro: Posição inválida\n");
        return;
    }
    if (posicao == 1) {
        inserirNoInicio(cabeca, dado);
        return;
    }

    No* novoNo = criarNo(dado);
    No* temp = *cabeca;
    for (int i = 1; i < posicao - 1 && temp != NULL; i++) {
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Erro: Posição inválida\n");
        return;
    }

    novoNo->proximo = temp->proximo;
    novoNo->anterior = temp;
    if (temp->proximo != NULL) {
        temp->proximo->anterior = novoNo;
    }
    temp->proximo = novoNo;
}

void excluirNoInicio(No** cabeca) 
{
    if (*cabeca == NULL) {
        printf("Erro: Lista vazia\n");
        return;
    }

    No* temp = *cabeca;
    *cabeca = temp->proximo;
    if (*cabeca != NULL) {
        (*cabeca)->anterior = NULL;
    }
    free(temp);
}

void excluirNoFim(No** cabeca) 
{
    if (*cabeca == NULL) {
        printf("Erro: Lista vazia\n");
        return;
    }

    No* temp = *cabeca;
    while (temp->proximo != NULL) {
        temp = temp->proximo;
    }

    if (temp->anterior != NULL) {
        temp->anterior->proximo = NULL;
    } else {
        *cabeca = NULL;
    }

    free(temp);
}

void excluirNaPosicao(No** cabeca, int posicao) 
{

    if (*cabeca == NULL || posicao < 1) {
        printf("Erro: Lista vazia ou posição inválida\n");
        return;
    }

    No* temp = *cabeca;
    for (int i = 1; i < posicao && temp != NULL; i++) {
        temp = temp->proximo;
    }

    if (temp == NULL) {
        printf("Erro: Posição inválida\n");
        return;
    }

    if (temp->anterior != NULL) {
        temp->anterior->proximo = temp->proximo;
    } else {
        *cabeca = temp->proximo;
    }

    if (temp->proximo != NULL) {
        temp->proximo->anterior = temp->anterior;
    }

    free(temp);
}

No* buscarNo(No* cabeca, int chave) 
{
    No* temp = cabeca;
    while (temp != NULL && temp->dado != chave) {
        temp = temp->proximo;
    }
    return temp;
}

void exibirLista(No* cabeca) 
{
    No* temp = cabeca;
    while (temp != NULL) {
        printf("%d ", temp->dado);
        temp = temp->proximo;
    }
    printf("\n");
}

void liberarLista(No** cabeca) 
{
    No* atual = *cabeca;
    No* proximo;
    while (atual != NULL) {
        proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    *cabeca = NULL;
}

int main() 
{

    No* cabeca = NULL;

    inserirNoInicio(&cabeca, 10);
    inserirNoFim(&cabeca, 20);
    inserirNaPosicao(&cabeca, 15, 2);

    printf("Lista após inclusão: ");
    exibirLista(cabeca);

    excluirNoInicio(&cabeca);
    excluirNoFim(&cabeca);
    excluirNaPosicao(&cabeca, 1);

    printf("Lista após exclusão: ");
    exibirLista(cabeca);

    No* resultadoBusca = buscarNo(cabeca, 20);
    if (resultadoBusca != NULL) {
        printf("Nó encontrado: %d\n", resultadoBusca->dado);
    } else {
        printf("Nó não encontrado\n");
    }

    liberarLista(&cabeca);

    return 0;
}
