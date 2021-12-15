#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

int main()
{
    Avl* a;
    a = avl_cria();
    a = avl_insere(a, 15);
    a = avl_insere(a, 10);
    a = avl_insere(a, 5);
    a = avl_insere(a, 20);
    a = avl_insere(a, 18);
    a = avl_insere(a, 16);
    a = avl_insere(a, 19);
    a = avl_insere(a, 25);
    a = avl_insere(a, 22);
    a = avl_insere(a, 21);
    a = avl_insere(a, 30);
    
    printf("\nExibição aninhada -> ");
    arv_imprime_aninhado(a);
    
    a = avl_insere(a, 9);
    a = avl_insere(a, 13);
    a = avl_insere(a, 23);
    
    printf("\nExibição aninhada -> ");
    arv_imprime_aninhado(a);
    
    a = avl_remove(a, 10);
    a = avl_remove(a, 18);
    a = avl_remove(a, 22);
    
    printf("\nExibição aninhada -> ");
    arv_imprime_aninhado(a);
    
    avl_destroi(a);

    return 0;
}
