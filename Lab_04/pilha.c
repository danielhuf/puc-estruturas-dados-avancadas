#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"

/* nó da lista para armazenar valores reais */
struct elemento {
    int info;
    struct elemento *prox;
};

/* estrutura da pilha */
struct pilha {
    Elemento* topo; /* aponta para o topo da pilha */
};

Pilha* pilha_cria (void)
{
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if (p==NULL) exit(1);
    
    p->topo = NULL;
    return p;
}

int pilha_push (Pilha* p, int v)
{
    Elemento* n = (Elemento*)malloc(sizeof(Elemento));
    if (n==NULL) {    /* memória esgotada */
        printf("Sem memória para alocar elemento. \n");
        return 0;   /* aborta programa */
    }
    /* insere elemento na próxima posição livre */
    n->info = v;
    n->prox = p->topo;    /* n->prox será o próximo elemento abaixo na pilha */
    p->topo = n;
    return 1;
}

int pilha_peek (Pilha* p)
{
    if (pilha_vazia(p))
    {
        printf("Pilha vazia.\n");
        return 0; 
    }
    /* pega elemento do topo */
    return p->topo->info;
}

int pilha_pop (Pilha* p)
{
    Elemento* t;
    int v;
    if (pilha_vazia(p))
    {
        printf("Pilha vazia.\n");
        return 0; 
    }
    /* retira elemento do topo */
    t = p->topo;
    v = t->info;
    p->topo = t->prox;
    free(t);
    
    return v;
}

void pilha_libera (Pilha* p)
{
    Elemento *t, *q = p->topo;
    while (q!=NULL)
    {
        t = q->prox;
        free(q);
        q = t;
    }
    free (p);
}

int pilha_vazia (Pilha* p)
{
    return (p->topo == NULL);
}

void imprime_pilha (Pilha* p, char* nome)
{
    Elemento *q = p->topo;
    printf("\n\n");
    while (q != NULL) {
        printf("%d\n", q->info);
        q = q->prox;
    }
    printf("----\n%s\n\n", nome);
}

int tamanho_pilha (Pilha* p)
{
    Elemento *q = p->topo;
    int tam = 0;
    while (q != NULL) {
        tam++;
        q = q->prox;
    }
    return tam;
}

Pilha* seleciona (int num, Pilha* pino1, Pilha* pino2, Pilha* pino3)
{
    switch (num) {
        case 1:
        return pino1;
        
        case 2:
        return pino2;
        
        case 3:
        return pino3;
        
        default:
        printf("Valor inválido!\n");
    }
    return NULL;
}




