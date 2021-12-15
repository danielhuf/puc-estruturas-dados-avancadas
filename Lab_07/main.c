#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "abb.h"

int main()
{
    Abb *a;
    a = abb_cria ();
    a = abb_insere(a, 15);
    a = abb_insere(a, 10);
    a = abb_insere(a, 5);
    a = abb_insere(a, 20);
    a = abb_insere(a, 18);
    a = abb_insere(a, 16);
    a = abb_insere(a, 19);
    a = abb_insere(a, 25);
    a = abb_insere(a, 22);
    a = abb_insere(a, 21);
    a = abb_insere(a, 30);
    
    printf("Exibição da arvore ordenada-> ");
    abb_imprime(a);
    
    printf("\nExibição aninhada -> ");
    arv_imprime_aninhado(a);
    
    if (esta_Balanceada(a))
        printf("\nA arvore esta balanceada");
    else
        printf("\nA arvore nao esta balanceada");
    
    a = abb_insere(a, 3);
    a = abb_insere(a, 7);
    a = abb_insere(a, 13);
    a = abb_insere(a, 17);
    a = abb_insere(a, 29);
    
    printf("\n\nExibição da arvore ordenada-> ");
    abb_imprime(a);
    
    printf("\nExibição aninhada -> ");
    arv_imprime_aninhado(a);
    
    if (esta_Balanceada(a))
        printf("\nA arvore esta balanceada");
    else
        printf("\nA arvore nao esta balanceada");
    
    a = abb_retira(a, 5);
    a = abb_retira(a, 15);
    a = abb_retira(a, 16);
    a = abb_retira(a, 18);
    a = abb_retira(a, 22);
    
    printf("\n\nExibição da arvore ordenada-> ");
    abb_imprime(a);
    
    printf("\nExibição aninhada -> ");
    arv_imprime_aninhado(a);
    
    if (esta_Balanceada(a))
        printf("\nA arvore esta balanceada");
    else
        printf("\nA arvore nao esta balanceada");
    
    return 0;
}
