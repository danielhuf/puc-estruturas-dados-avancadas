#ifndef HEAP_STRUCT
#define HEAP_STRUCT
typedef struct _heap Heap;
#endif

Heap* heap_cria(int max);

int heap_vazia(Heap *heap);

void heap_libera(Heap *heap);