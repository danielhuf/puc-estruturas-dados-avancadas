#include<stdio.h>
#include<stdlib.h>
#include "maxheap.h"

struct _heap {
    int max; /* tamanho maximo do heap */
    int pos; /* proxima posicao disponivel no vetor */
    int* prioridade; /* vetor das prioridades */
};

static void troca(int a, int b, int* v) {
    int f = v[a];
    v[a] = v[b];
    v[b] = f;
}

static void corrige_acima(Heap* heap, int pos) {
    int pai;
    while (pos > 0){
        pai = (pos-1) / 2;
        if (heap->prioridade[pai] < heap->prioridade[pos])
            troca(pos, pai, heap->prioridade);
        else
            break;
        pos = pai;
    }
}


void maxheap_insere(Heap* heap, int prioridade)
{
    if ( heap->pos < heap->max )
    {
        heap->prioridade[heap->pos] = prioridade;
        corrige_acima(heap,heap->pos);
        heap->pos++;
    }
    else{
        printf("Heap CHEIO!\n");
        exit(1);
    }
}

// heapify iterativo
static void corrige_abaixo(Heap* heap){
    int pai=0;
    int filho_esq, filho_dir, filho;
    
    while (2 * pai+1 < heap->pos){
        filho_esq = 2 * pai+1;
        filho_dir = 2 * pai+2;

        if (filho_dir >= heap->pos) filho_dir = filho_esq;
        
        if (heap->prioridade[filho_esq] > heap->prioridade[filho_dir])
            filho = filho_esq;
        else
            filho = filho_dir;
        
        if (heap->prioridade[pai] < heap->prioridade[filho])
            troca(pai, filho, heap->prioridade);
        else
            break;
            
        pai=filho;
    }
}

int maxheap_remove(Heap* heap)
{
    if (heap->pos > 0) {
        int topo = heap->prioridade[0];
        heap->prioridade[0] = heap->prioridade[heap->pos-1];
        heap->pos--;
        corrige_abaixo(heap);
        return topo;
    }
    else {
        printf("Heap VAZIO!");
        return -1;
    }
}
