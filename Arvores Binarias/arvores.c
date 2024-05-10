#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int valor;
    struct No* esquerdo, * direito;
} NODE;

typedef struct {
    NODE* raiz;
} BTREE;

void inserirEsquerda(NODE* No, int n);
void inserirDireita(NODE* No, int n);

void inserirEsquerda(NODE* No, int n) {
    if (No->esquerdo == NULL) {
        NODE* novo = (NODE*)malloc(sizeof(NODE));
        novo->valor = n;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        No->esquerdo = novo;
    }
    else {
        if (n < No->esquerdo->valor)
            inserirEsquerda(No->esquerdo, n);
        if (n > No->esquerdo->valor)
            inserirDireita(No->esquerdo, n);
    }
}

void inserirDireita(NODE* No, int n) {
    if (No->direito == NULL) {
        NODE* novo = (NODE*)malloc(sizeof(NODE));
        novo->valor = n;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        No->direito = novo;
    }
    else {
        if (n > No->direito->valor)
            inserirDireita(No->direito, n);
        if (n < No->direito->valor)
            inserirEsquerda(No->direito, n);
    }
}

NODE* inserir(NODE* raiz, int n) {
    if (raiz == NULL){
        NODE* novo = (NODE*)malloc(sizeof(NODE));
        novo->valor = n;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        return novo;
    }
    else {
        if (n < raiz->valor)
            raiz->esquerdo = inserir(raiz->esquerdo, n);
        if (n > raiz->valor)
            raiz->direito = inserir(raiz->direito, n);
        return raiz;
    }
}

void imprimir(NODE* raiz) {
    if (raiz != NULL) {
        imprimir(raiz->esquerdo);
        printf("%d ", raiz->valor);
        imprimir(raiz->direito);
    }
}

int tamanho(NODE* raiz) {
    if (raiz == NULL)
        return 0;
    else
        return 1 + tamanho(raiz->esquerdo) + tamanho(raiz->direito);
}

int buscar(NODE* raiz, int chave) {
    if (raiz == NULL) {
        return -1;
    }
    else {
        if (raiz->valor == chave) {
            return raiz->valor;
        }
        else {
            if (chave < raiz->valor)
                return buscar(raiz->esquerdo, chave);
            else
                return buscar(raiz->direito, chave);
        }
    }
}

int main() {
    int op, n;
    BTREE arv;
    arv.raiz = NULL;

    do {
        printf("\n0 - sair\n1 - inserir\n2 - imprimir\n3 - Buscar\n");
        scanf("%d", &op);

        switch (op) {
        case 0:
            printf("\nSair..\n");
            break;
        case 1:
            printf("Digite um valor:");
            scanf("%d", &n);
            arv.raiz = inserir(arv.raiz, n);
            break;
        case 2:
            printf("Impressao da arvore: ");
            imprimir(arv.raiz);
            printf("\n");
            printf("Tamanho: %d\n", tamanho(arv.raiz));
            break;
        case 3:
            printf("qual valor procura?");
            scanf("%d", &n);
            printf("Resultado: %d\n", buscar(arv.raiz, n));
            break;
        default:
            printf("Opcao Invalida\n");
        }
    } while (op != 0);

    return 0;
}