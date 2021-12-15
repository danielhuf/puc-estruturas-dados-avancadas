#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

struct aluno
{
    int mat;
    char nome[81];
    char end[121];
    char tel[21];
};

void inicializa (int n, Aluno** tab) 
{
    int i;
    for (i=0; i<n; i++)
        tab[i] = NULL;
    return;
}

void preenche (int n, Aluno** tab, int i, int m, char* no, char* e, char *t)
{
    if (i<0 || i>=n) {
        printf("Indice fora do limite do vetor\n");
        exit(1);
    }
    if (tab[i]==NULL)
        tab[i] = (Aluno*)malloc(sizeof(Aluno));
    tab[i]->mat = m;
    strcpy(tab[i]->nome, no);
    strcpy(tab[i]->end, e);
    strcpy(tab[i]->tel, t);
    return;
}

void retira (int n, Aluno** tab, int i)
{
    if (i<0 || i>=n) {
        printf("Indice fora do limite do vetor\n");
        exit(1);
    }
    if (tab[i]!=NULL) {
        free(tab[i]);
        tab[i] = NULL;
    }
    return;
}

void imprime (int n, Aluno** tab, int i)
{
    if (i<0 || i>=n) {
        printf("Indice fora do limite do vetor\n");
        exit(1);
    }
    if (tab[i]!=NULL) {
        printf("Matricula: %d\n", tab[i]->mat);
        printf("Nome: %s\n", tab[i]->nome);
        printf("Endereço: %s\n", tab[i]->end);
        printf("Telefone: %s\n\n", tab[i]->tel);
    }
    return;
}

void imprime_tudo (int n, Aluno** tab)
{
    int i;
    for (i=0; i<n; i++)
        imprime(n, tab, i);
    return;
}

//Irei utilizar a busca linear, visto que a busca binária necessita que os nomes estejam ordenados
int busca_lin (int n, Aluno** tab, char* nome)
{
    int i;
    for (i=0; i<n; i++) {
        if (tab[i] != NULL)
            if (strcmp(tab[i]->nome, nome) == 0)
                return i;
    }
    return -1;
}

