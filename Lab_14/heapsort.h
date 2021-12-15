#include "heap.h"

void maxheap_heapify_rec(Heap* heap, int pai);
void maxheap_heapify_int(Heap* heap, int pai);
void maxheap_constroi_heap(Heap* heap);
void maxheap_heapsort(Heap* heap);

void minheap_heapify_rec(Heap* heap, int pai);
void minheap_heapify_int(Heap* heap, int pai);
void minheap_constroi_heap(Heap* heap);
void minheap_heapsort (Heap* heap);

int* minheap_sort (int nums[], int tam);
int* maxheap_sort (int nums[], int tam);