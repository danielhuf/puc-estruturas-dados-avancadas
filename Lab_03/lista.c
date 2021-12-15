#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

struct aluno
{
    int mat;
    char nome[81];
    char end[121];
    char tel[21];
};

struct elemento 
{
    Aluno* info;
    struct elemento *prox;
};

/* Entendo atualiação como atualização de nome */

/* CRIAÇÃO */
Elemento* lista_cria ()
{
    return NULL;
}

/* INSERÇÃO */
Elemento* lista_insere_ordenado (Elemento* lista, int m, char* no, char* e, char* t)
{
    Elemento* novo;
    Elemento* a = NULL;    /* ponteiro para elemento anterior */
    Elemento* p = lista;   /* ponteiro para percorrer a lista */
    
    while (p != NULL && strcmp(p->info->nome, no) < 0) {
        a = p;             /* procura posição de inserção */
        p = p->prox; 
    }
    /* cria novo elemento */
    novo = (Elemento*)malloc(sizeof(Elemento));
    novo->info = (Aluno*)malloc(sizeof(Aluno));
    novo->info->mat = m;
    strcpy(novo->info->nome, no);
    strcpy(novo->info->end, e);
    strcpy(novo->info->tel, t);
    if (a == NULL) {
        novo->prox = lista;   /* insere elemento no início */
        lista = novo;
    }
    else {
        novo->prox = a->prox; /* insere elemento no meio da lista */
        a->prox = novo;
    }
    return lista;
}

/* ATUALIZAÇÃO */
/* A atualização pode ser entendida como um remove "nome antigo" e insere ordenado "nome_novo", mantendo as informações restantes */
Elemento* lista_atualiza (Elemento* lista, char* nomeAntigo, char* nomeNovo)
{
    int matAntigo;
    char endAntigo[121], telAntigo[21];
    
    Elemento* el_buscado = busca_nome(lista, nomeAntigo);
    matAntigo = el_buscado->info->mat;
    strcpy(endAntigo, el_buscado->info->end);
    strcpy(telAntigo, el_buscado->info->tel);
    
    Elemento* lista_removido = lista_retira(lista, nomeAntigo);
    Elemento* lista_adicionado = lista_insere_ordenado(lista_removido, matAntigo, nomeNovo, endAntigo, telAntigo);
    return lista_adicionado;
}

/* REMOÇÃO */
Elemento* lista_retira (Elemento* lista, char* no)
{
    Elemento* a = NULL;   /* ponteiro para elemento anterior */
    Elemento* p = lista;  /* ponteiro para percorrer a lista */
    
    /* procura elemento na lista, guardando anterior */
    while (p != NULL && strcmp(p->info->nome, no) != 0) {
        a = p;
        p = p->prox;
    }
    
    /* verifica se achou elemento */
    if (p == NULL)
        return lista;   /* não achou: retorna lista original */
        
    /* retira elemento */
    if (a == NULL)
        lista = p->prox;   /* retira elemento do início */
    else
        a->prox = p->prox; /* retira elemento do meio da lista */
        
    free(p);
    return lista;
}

/* IMPRESSÃO */
void lista_imprime (Elemento* lista)
{
    Elemento *p;
    int cont = 1;
    for (p = lista; p != NULL; p = p->prox, cont++) {
        printf("Aluno %d:\n", cont);
        printf("Matricula: %d\n", p->info->mat);
        printf("Nome: %s\n", p->info->nome);
        printf("Endereço: %s\n", p->info->end);
        printf("Telefone: %s\n\n", p->info->tel);        
    }
}

/* BUSCA POR NOME */
Elemento* busca_nome (Elemento* lista, char* n)
{
    Elemento* p;
    for (p=lista; p!=NULL; p=p->prox) {
        if (strcmp(p->info->nome, n)==0)
            return p;   /* achou o elemento */
    }
    return NULL;        /* não achou o elemento */
}

/* IGUALDADE */
int lista_igual (Elemento* lista1, Elemento* lista2)
{
    Elemento* p1;   /* ponteiro para percorrer lista 1 */
    Elemento* p2;   /* ponteiro para percorrer lista 2 */
    for (p1=lista1, p2=lista2; p1!=NULL && p2!=NULL; p1=p1->prox, p2=p2->prox) {
        if (p1->info->mat != p2->info->mat || strcmp(p1->info->nome, p2->info->nome) != 0 || strcmp(p1->info->end, p2->info->end) != 0 || strcmp(p1->info->tel, p2->info->tel) != 0)
            return 0;
    }
    if (p1 == p2)  /* se ambos forem NULL as listas são iguais */
        return 1;
    else
        return 0;
}

/* TESTE DE VAZIA */
int lista_vazia (Elemento* lista)
{
    return (lista == NULL);
}

/* LIBERAÇÃO */
void lista_libera (Elemento* lista)
{
    Elemento* p = lista;
    Elemento* t;
    while (p != NULL) {
        t = p->prox;     /* guarda referência para próximo elemento */
        free(p->info);
        free(p);         /* libera a memória apontada por p */
        p = t;           /* faz apontar para o próximo */
    }
}






