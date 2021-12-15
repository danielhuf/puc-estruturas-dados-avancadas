#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "heap.h"

struct _heap {
	int max; /* tamanho maximo do heap */
	int pos; /* proxima posicao disponivel no vetor */
	int* prioridade; /* vetor das prioridades */
	void** info; /* vetor das informações */
};

Heap* heap_cria(int max) {
	Heap* heap = (Heap*)malloc(sizeof(Heap));
	assert(heap);
	heap->max = max;
	heap->pos = 0;
	
	heap->prioridade = (int*)malloc(max * sizeof(int));
	assert(heap->prioridade);
	
	heap->info = (void**)malloc(max * sizeof(void*));
	assert(heap->info);
	return heap;
}

int heap_vazia(Heap *heap) {
	if (heap->pos == 0)
		return 1;
	return 0;
}

void heap_libera(Heap * h) {
	int i;
	free(h->prioridade);
	for(i = 0; i < h->pos; i++)
		free(h->info[i]);
	free(h->info);
	free(h);
}