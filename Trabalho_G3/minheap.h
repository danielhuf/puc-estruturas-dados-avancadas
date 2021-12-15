#include "heap.h"

void minheap_insere(Heap* heap, int prioridade, void *info);

void *minheap_remove(Heap* heap);

void minheap_diminui(Heap *heap, int prioridade, void *info);

void minheap_diminui2(Heap *heap, int prioridade, int info);