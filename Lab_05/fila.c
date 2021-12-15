#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

/* nó da lista para armazenar valores reais */
struct lista {
    int numPedido;
    char* nomePrato;
    struct lista* prox;
};

/* estrutura da fila */
struct fila {
    Lista* ini;
    Lista* fim;
};

Fila* fila_cria (void)
{
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if (f==NULL) exit(1);
    
    f->ini = NULL;
    f->fim = NULL;
    return f;
}

void fila_insere (Fila* f, int pedido, char* prato)
{
    Lista* n = (Lista*)malloc(sizeof(Lista));
    if (n==NULL) exit(1);
    
    n->numPedido = pedido;  /* armazena informação */
    n->nomePrato = (char*)malloc((strlen(prato)+1)*sizeof(char));
    if (n->nomePrato==NULL) exit(1);
    strcpy(n->nomePrato, prato);
    n->prox = NULL;        /* novo nó passa a ser o último */
    
    /* verifica se lista não estava vazia */
    if (f->fim != NULL)
        f->fim->prox = n;
    else  /* fila estava vazia */
        f->ini = n;
    f->fim = n;  /* fila aponta para novo elemento */
}

void fila_passa (Fila* origem, Fila* destino)
{
    Lista* t;
    //int num;
    //char* nome;
    if (fila_vazia(origem)) {
        printf("Fila vazia.\n");
        exit(1); /* aborta programa */
    }
    t = origem->ini;
    //num = t->numPedido;
    //strcpy(nome, t->nomePrato);
    fila_insere(destino, t->numPedido, t->nomePrato);
    
    origem->ini = t->prox;
    if (origem->ini == NULL)  /* verifica se fila ficou vazia */
        origem->fim = NULL;
    free(t->nomePrato);
    free(t);
}

void fila_libera (Fila* f)
{
    Lista* q = f->ini;
    while (q!=NULL) {
        Lista* t = q->prox;
        free(q->nomePrato);
        free(q);
        q = t;
    }
    free(f);
}

int fila_vazia (Fila* f)
{
    return (f->ini == NULL);
}

void imprime_fila (Fila* f)
{
    Lista* q = f->ini;
    int cont = 1;
    while (q!=NULL) {
        printf("Posição %d: pedido %d - %s\n", cont++, q->numPedido, q->nomePrato);
        q = q->prox;
    }
    printf("\n");
}

