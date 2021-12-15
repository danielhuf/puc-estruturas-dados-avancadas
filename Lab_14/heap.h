#ifndef HEAP_STRUCT
#define HEAP_STRUCT
typedef struct _heap Heap;
#endif

Heap* heap_cria(int max);

void heap_print(Heap *heap);

void heap_print_indent(Heap *heap);

void heap_libera(Heap *heap);
