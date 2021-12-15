/******************************************************************************
 
LAB 14 Heaps
INF1010 Estrutura de Dados Avançadas
Prof. Augusto Baffa

 Implemente um TDA para uma Heap:
– O programa principal deve criar a heap e carregar as prioridades.
– Insira as prioridades 29, 7, 3, 6, 15, 11, 25, 30
– Faça os ajustes para criar uma min heap e uma max heap
• Verifique como ficaria a ordenação em ambos os casos
– Após implementar sua heap:
• Inicialize o vetor com os valores e aplique os conceitos de heap para executar o heapsort.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "maxheap.h"
#include "minheap.h"
#include "heapsort.h"
/////////////////////////

int main(void) {
    int i, vmin, vmax;
    int tam = 10;
    int n = 8;
    int iniciais[] = {29, 7, 3, 6, 15, 11, 25, 30};

    Heap *maxh  =  heap_cria(tam); 
    Heap *minh  =  heap_cria(tam); 
    
    for (i = 0; i < n; i++) {
        maxheap_insere(maxh, iniciais[i]);
        minheap_insere(minh, iniciais[i]);
    }

    printf(" == Max Heap\n");
    heap_print(maxh);
    heap_print_indent(maxh);
    printf(" * Heapsort\n");
    maxheap_heapsort(maxh);
    heap_print(maxh);
    heap_print_indent(maxh);
    
    printf("-----------------------\n\n");
    
    printf(" == Min Heap\n");
    heap_print(minh);
    heap_print_indent(minh);
    printf(" * Heapsort\n");
    minheap_heapsort(minh);
    heap_print(minh);
    heap_print_indent(minh);

    printf("-----------------------\n\n");
    
    for (i = 0; i < n; i++) {
        vmin = minheap_remove(minh);
        vmax = maxheap_remove(maxh);
        
        printf("Remoção Min Heap: %d, Max Heap: %d\n", vmin, vmax);
    }
    printf("\n");

    heap_libera(maxh);
    heap_libera(minh);
  
    return 0;
}
