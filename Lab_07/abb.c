#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

struct abb {
    int info;
    struct abb* pai;
    struct abb* esq;
    struct abb* dir;
};

Abb* abb_cria (void)
{
    return NULL;
}

Abb* abb_busca (Abb* r, int v)
{
    if (r == NULL)
        return NULL;
    else if (r->info > v)
        return abb_busca(r->esq, v);
    else if (r->info < v)
        return abb_busca(r->dir, v);
    else return r;
}

Abb* abb_min (Abb* r)
{
    if (r == NULL) return NULL;
    while (r->esq != NULL)
        r = r->esq;
    return r;
}

Abb* abb_prox (Abb* r)
{
    if (r==NULL) return NULL;
    else if (r->dir != NULL)
        /* retorna o menor da sad */
        return abb_min(r->dir);
    else {
        Abb* p = r->pai;
        while (p!=NULL && r==p->dir) {
            r = p;
            p = p->pai;
        }
        return p;
    }
}

void abb_imprime (Abb* a)
{
    if (a != NULL) {
        abb_imprime(a->esq);
        printf("%d ", a->info);
        abb_imprime(a->dir);
    }
}

Abb* cria_filho (Abb* pai, int val) 
{
    Abb* no = (Abb*) malloc(sizeof(Abb));
    no->info = val;
    no->pai = pai;
    no->esq = no->dir = NULL;
    return no;
}

Abb* abb_insere (Abb* r, int val) 
{
    if (r==NULL)
    return cria_filho(r, val);
    else if (val < r->info)  {
        if (r->esq == NULL)
            r->esq = cria_filho(r,val);
        else
            r->esq = abb_insere(r->esq, val);
    }
    else if (val > r->info) {
        if (r->dir == NULL)
            r->dir = cria_filho(r, val);
        else
            r->dir = abb_insere(r->dir, val);
    }
    return r;
}

Abb* abb_retira (Abb* r, int val)
{
    if (r == NULL) return NULL;
    else if (val < r->info)
        r->esq = abb_retira(r->esq, val);
    else if (val > r->info)
        r->dir = abb_retira(r->dir, val);
    else {   /* achou o nó a remover */
        if (r->esq == NULL && r->dir == NULL) {  /* nó sem filhos */
            free(r); r = NULL;
        }
        else if (r->esq == NULL) {  /* nó só tem filho à direita */
            Abb* t = r; r = r->dir; r->pai = t->pai; free(t);
        }
        else if (r->dir == NULL) {  /* nó só tem filho à esquerda */
            Abb* t = r; r = r->esq; r->pai = t->pai; free(t);
        }
        else {  /* nó tem os dois filhos: busca o sucessor */
            Abb* sucessor = r->dir;
            while (sucessor->esq != NULL) sucessor = sucessor->esq;
            r->info = sucessor->info;  /* troca os valores */
            sucessor->info = val;
            /* liga o filho do sucessor e o avo */
            if (sucessor->pai->esq == sucessor)
                sucessor->pai->esq = sucessor->dir;  /* se sucessor for filho à esquerda */
            else
                sucessor->pai->dir = sucessor->dir;  /* se sucessor for filho à direita */
            if (sucessor->dir != NULL) sucessor->dir->pai = sucessor->pai;
            free(sucessor);
        }
    }
    return r;
}

void arv_imprime_aninhado (Abb* a)
{
    if (a != NULL) {
        printf("%d (", a->info);   /* mostra raiz */
        arv_imprime_aninhado(a->esq);      /* mostra sae */
        arv_imprime_aninhado(a->dir);      /* mostra sad */
        printf(")");
    }
}

int max (int a, int b)
{
    return (a >= b) ? a : b;
}

int altura (Abb* a)
{
    if (a == NULL)
        return 0;
    return 1 + max(altura(a->esq), altura(a->dir));
}

int esta_Balanceada (Abb* a)
{
    int h_esq;
    int h_dir;
    
    if (a == NULL)
        return 1;
        
    h_esq = altura(a->esq);
    h_dir = altura(a->dir);
    
    return (abs(h_esq - h_dir)<=1 && esta_Balanceada(a->esq) && esta_Balanceada(a->dir));
}





