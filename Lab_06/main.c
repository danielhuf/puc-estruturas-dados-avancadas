#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arvBin.h"

int main()
{
    NoArv* a = arv_cria('a', 
                        arv_cria('b', 
                                arv_cria('e', 
                                        arv_cria('k', 
                                                arv_criavazia(), 
                                                arv_cria('l', 
                                                        arv_criavazia(), 
                                                        arv_criavazia())), 
                                        arv_cria('f', 
                                                arv_criavazia(), 
                                                arv_criavazia())), 
                                arv_cria('c', 
                                        arv_cria('g', 
                                                arv_criavazia(), 
                                                arv_criavazia()), 
                                        arv_cria('d', 
                                                arv_cria('h', 
                                                        arv_cria('m', 
                                                                arv_criavazia(), 
                                                                arv_criavazia()), 
                                                        arv_cria('i', 
                                                                arv_criavazia(), 
                                                                arv_cria('j', 
                                                                        arv_criavazia(), 
                                                                        arv_criavazia()))), 
                                                arv_criavazia()))), 
                        arv_criavazia());
    
    printf("Exibição aninhada -> ");
    arv_imprime_aninhado(a);
    printf("\nExibição pré-ordem -> ");
    imprime_pre_ordem(a);
    printf("\nExibição ordem simétrica -> ");
    imprime_ordem_simetrica(a);
    printf("\nExibição pós-ordem -> ");
    imprime_pos_ordem(a);

    a = arv_libera(a);
    return 0;
}
