#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvBin.h"

struct noArv {
    char info;
    struct noArv* esq;
    struct noArv* dir;
};

NoArv* arv_criavazia (void)
{
    return NULL;
}

NoArv* arv_cria (char c, NoArv* sae, NoArv* sad)
{
    NoArv* p = (NoArv*)malloc(sizeof(NoArv));
    if (p==NULL) exit(1);
    p->info = c;
    p->esq = sae;
    p->dir = sad;
    return p;
}

NoArv* arv_libera (NoArv* a)
{
    if (!arv_vazia(a)) {
        arv_libera(a->esq);   /* libera sae */
        arv_libera(a->dir);   /* libera sad */
        free(a);              /* libera raiz */
    }
    return NULL;
}

int arv_vazia (NoArv* a)
{
    return (a==NULL);
}

int arv_pertence (NoArv* a, char c)
{
    if (arv_vazia(a))
        return 0;     /* árvore vazia: nâo encontrou */
    else
        return a->info==c || arv_pertence(a->esq, c) || arv_pertence(a->dir, c);
}

void arv_imprime_aninhado (NoArv* a)
{
    if (!arv_vazia(a)) {
        printf("%c (", a->info);   /* mostra raiz */
        arv_imprime_aninhado(a->esq);      /* mostra sae */
        arv_imprime_aninhado(a->dir);      /* mostra sad */
        printf(")");
    }
}

void imprime_pre_ordem (NoArv* a)
{
    if (!arv_vazia(a)) {
        printf("%c ", a->info);
        if (arv_vazia(a->esq) && !arv_vazia(a->dir))
            printf("* ");
        imprime_pre_ordem(a->esq);
        if (!arv_vazia(a->esq) && arv_vazia(a->dir))
            printf("* ");
        imprime_pre_ordem(a->dir);
    }
}

void imprime_ordem_simetrica (NoArv* a)
{
    if (!arv_vazia(a)) {
        if (arv_vazia(a->esq) && !arv_vazia(a->dir))
            printf("* ");
        imprime_ordem_simetrica(a->esq);
        printf("%c ", a->info);
        if (!arv_vazia(a->esq) && arv_vazia(a->dir))
            printf("* ");
        imprime_ordem_simetrica(a->dir);
    }
}

void imprime_pos_ordem (NoArv* a)
{
    if (!arv_vazia(a)) {
        if (arv_vazia(a->esq) && !arv_vazia(a->dir))
            printf("* ");
        imprime_pos_ordem(a->esq);
        if (!arv_vazia(a->esq) && arv_vazia(a->dir))
            printf("* ");
        imprime_pos_ordem(a->dir);
        printf("%c ", a->info);
    }
}





