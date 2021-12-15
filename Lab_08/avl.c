#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

struct avl {
    int info;
    int fb;   /* fator de balanceamento */
    struct avl *pai;
    struct avl *esq;
    struct avl *dir;
};

Avl* avl_cria (void)
{
    return NULL;
}

Avl* avl_insere2 (Avl* r, int info, int* flag)
{
    if (r==NULL) {
        r = (Avl*)malloc(sizeof(Avl));
        r->esq = r->dir = NULL;
        r->info = info;
        r->fb = 0;
        *flag = 1;
    }
    else if (r->info > info) {
        r->esq = avl_insere2 (r->esq, info, flag);
        if (*flag) {          /* r cresceu à esquerda (ou seja, he aumentou) */
            switch(r->fb) {   /* analise do fator de balanceamento de r */
                case 1:       /* antes: hd>he xxx depois: hd=he pois he aumentou */
                    r->fb = 0; *flag = 0; break;
                case 0:       /* antes: hd=he xxx depois: hd<he pois he aumentou */
                    r->fb = -1; break;
                case -1:      /* antes: hd<he xxx depois hd-he=-2 pois he aumentou */
                    if (r->esq->fb == -1) r = rotacao_direita(r);
                    else r = rotacao_esquerda_direita(r);
                    *flag = 0; break;
            }
        }
    }
    else if (r->info < info) {
        r->dir = avl_insere2 (r->dir, info, flag);
        if (*flag) {          /* r cresceu à direita (ou seja, hd aumentou) */
            switch(r->fb) {   /* analise do fator de balanceamento de r */
                case 1:       /* antes: hd<he xxx depois hd=he pois hd aumntou */
                    r->fb = 0; *flag = 0; break;
                case 0:       /* antes: hd=he xxx depois: hd>he pois hd aumentou */
                    r->fb = -1; break;
                case -1:      /* antes: hd>he xxx depois hd-he=2 pois hd aumentou */
                    if (r->dir->fb == -1) r = rotacao_esquerda(r);
                    else r = rotacao_direita_esquerda(r);
                    *flag = 0; break;
            }
        }
    }
    return r;
}

Avl* avl_insere (Avl* r, int info)
{
    int flag = 0;
    return avl_insere2(r, info, &flag);
}

Avl* rotacao_direita (Avl *r)
{
    Avl *t=r->esq, *m=t->dir;
    t->dir = r;
    r->esq = m;
    if (t->fb == -1) {
        t->fb = 0;
        r->fb = 0;
    }
    else {
        t->fb = 1;
        r->fb = -1;
    }
    return t;
}

Avl* rotacao_esquerda (Avl *r)
{
    Avl *t=r->dir, *m=t->esq;
    t->esq = r;
    r->dir = m;
    if (t->fb==1) {
        t->fb = 0;
        r->fb = 0;
    }
    else {
        t->fb = -1;
        r->fb = 1;
    }
    return t;
}

Avl* rotacao_direita_esquerda (Avl *r) 
{
    Avl *t = r->dir, *s = t->esq;
    Avl *T2 = s->esq, *T3 = s->dir;
    s->esq = r; s->dir = t;
    r->dir = T2; t->esq = T3;
    switch (s->fb) {
        case -1:
            r->fb = s->fb = 0;
            t->fb = 1; break;
        case 0:
            r->fb = s->fb = t->fb = 0; break;
        case 1:
            r->fb = -1;
            s->fb = t->fb = 0; break;
    }
    return s;
}

Avl* rotacao_esquerda_direita (Avl *r)
{
    Avl *p = r->esq, *q = p->dir;
    Avl *T2 = q->esq, *T3 = q->dir;
    q->esq = p; q->dir = r;
    p->dir = T2; r->esq = T3;
    switch (q->fb) {
        case -1:
            r->fb = 1;
            q->fb = p->fb = 0; break;
        case 0:
            r->fb = q->fb = p->fb = 0; break;
        case 1:
            r->fb = q->fb = 0;
            p->fb = -1; break;
    }
    return q;
}

Avl* avl_remove2 (Avl *r, int info, int *delta_h) 
{
    if (!r) return NULL;
    else if (info < r->info) {
        r->esq = avl_remove2(r->esq, info, delta_h);
        r->fb -= *delta_h;
        if (r->fb == 2) {
            if (r->dir->fb == 1) {r = rotacao_esquerda(r); *delta_h = -1; }
            else if (r->dir->fb == 0) {r = rotacao_esquerda(r); *delta_h = 0; }
            else if (r->dir->fb == -1) {r = rotacao_direita_esquerda(r); *delta_h = -1; }
        }
        else *delta_h = ((r->fb==1) ? 0 : -1); /* a sad mantém a altura do nó */
    }
    else if (info > r->info) {
        r->dir = avl_remove2(r->dir, info, delta_h);
        r->fb -= *delta_h;
        if (r->fb == 2) {
            if (r->esq->fb == 1) {r = rotacao_direita(r); *delta_h = -1; }
            else if (r->esq->fb == 0) {r = rotacao_direita(r); *delta_h = 0; }
            else if (r->esq->fb == -1) {r = rotacao_esquerda_direita(r); *delta_h = -1; }
        }
        else *delta_h = ((r->fb==1) ? 0 : -1); /* a sae mantém a altura do nó */
    }
    else {  /* achou o nó para remover - remoção semelhante à abb */
        if (r->esq == NULL && r->dir == NULL) {  /* nó sem filhos */
            free(r); r = NULL; *delta_h = -1;
        }
        else if (r->esq == NULL) {  /* nó só tem filho à direita */
            Avl* t = r; r = r->dir; r->pai = t->pai; free(t); *delta_h = -1;
        }
        else if (r->dir == NULL) {  /* nó só tem filho à esquerda */
            Avl* t = r; r = r->esq; r->pai = t->pai; free(t); *delta_h = -1;
        }
        else {  /* nó tem os dois filhos: busca o sucessor */
            Avl* sucessor = r->dir;
            while (sucessor->esq != NULL) sucessor = sucessor->esq;
            r->info = sucessor->info;  /* troca os valores */
            sucessor->info = info;
            /* liga o filho do sucessor e o avo */
            if (sucessor->pai->esq == sucessor)
                sucessor->pai->esq = sucessor->dir;  /* se sucessor for filho à esquerda */
            else
                sucessor->pai->dir = sucessor->dir;  /* se sucessor for filho à direita */
            if (sucessor->dir != NULL) sucessor->dir->pai = sucessor->pai;
            free(sucessor); *delta_h = -1;
        }
    }
    return r;
}

Avl* avl_remove (Avl *r, int info)
{
    int delta_h = 0;
    return avl_remove2(r, info, &delta_h);
}

int arv_vazia (Avl* a)
{
    return (a==NULL);
}

void avl_destroi (Avl* a)
{
    if (!arv_vazia(a)) {
        avl_destroi(a->esq);   /* libera sae */
        avl_destroi(a->dir);   /* libera sad */
        free(a);               /* libera raiz */
    }
}

void arv_imprime_aninhado (Avl* a)
{
    if (a != NULL) {
        printf("%d (", a->info);   /* mostra raiz */
        arv_imprime_aninhado(a->esq);      /* mostra sae */
        arv_imprime_aninhado(a->dir);      /* mostra sad */
        printf(")");
    }
}



