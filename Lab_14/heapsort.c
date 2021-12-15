#include<stdio.h>
#include<stdlib.h>
#include "heapsort.h"
#include "minheap.h"
#include "maxheap.h"

struct _heap {
    int max; /* tamanho maximo do heap */
    int pos; /* proxima posicao disponivel no vetor */
    int* prioridade; /* vetor das prioridades */
};

//////////////////////////
static void troca(int a, int b, int* v) {
    int f = v[a];
    v[a] = v[b];
    v[b] = f;
}

/////////////////////////
void maxheap_heapify_rec(Heap* heap, int pai){ 
   int maior = pai; // Inicializa maior sendo a raiz
   int filho_esq = 2 * pai + 1;
   int filho_dir = 2 * pai + 2;

   if (filho_esq < heap->pos && heap->prioridade[filho_esq] > heap->prioridade[maior]) 
      maior = filho_esq; 
  
   if (filho_dir < heap->pos && heap->prioridade[filho_dir] > heap->prioridade[maior]) 
      maior = filho_dir; 

   if (maior != pai) { // maior não é o pai
      troca(pai, maior, heap->prioridade);
      maxheap_heapify_rec(heap, filho_dir); 
   } 
}

void maxheap_heapify_int(Heap* heap, int pai){
    
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

void maxheap_constroi_heap(Heap* heap) 
{ 
   // índice do último nó intermediário (não-folha)
   int n = heap->pos;
   int startIdx = (n / 2) - 1; 
   int i;
  
   for (i = startIdx; i >= 0; i--) { 
      maxheap_heapify_int(heap, i); 
   } 
} 

/////////////////////////

void minheap_heapify_rec(Heap* heap, int pai) 
{ 
   int menor = pai; // Inicializa menor sendo a raiz
   int filho_esq = 2 * pai + 1;
   int filho_dir = 2 * pai + 2;

   if (filho_esq < heap->pos && heap->prioridade[filho_esq] < heap->prioridade[menor]) 
      menor = filho_esq; 
  
   if (filho_dir < heap->pos && heap->prioridade[filho_dir] < heap->prioridade[menor]) 
      menor = filho_dir; 

   if (menor != pai) { // menor não é o pai
      troca(pai, menor, heap->prioridade);
      minheap_heapify_rec(heap, filho_esq); 
   } 
}

void minheap_heapify_int(Heap* heap, int pai){

    int filho_esq, filho_dir, filho;
    
    while (2 * pai+1 < heap->pos){
        filho_esq = 2 * pai+1;
        filho_dir = 2 * pai+2;

        if (filho_dir >= heap->pos) filho_dir = filho_esq;
        
        if (heap->prioridade[filho_esq] < heap->prioridade[filho_dir])
            filho = filho_esq;
        else
            filho = filho_dir;
        
        if (heap->prioridade[pai] > heap->prioridade[filho])
            troca(pai, filho, heap->prioridade);
        else
            break;
            
        pai=filho;
    }
}

void minheap_constroi_heap(Heap* heap){ 
   // índice do último nó intermediário (não-folha)
   int n = heap->pos;
   int startIdx = (n / 2) - 1; 
   int i;
  
   for (i = startIdx; i >= 0; i--) { 
      minheap_heapify_int(heap, i); 
   } 
} 

/////////////////////////

void maxheap_heapsort (Heap* heap){
    int i;
    int n = heap->pos;
    minheap_constroi_heap(heap);
    for (i = heap->pos - 1; i >= 1; i--) {
        troca(0, i, heap->prioridade);
        heap->pos--;
        minheap_heapify_int(heap, 0);
    }
    heap->pos = n;
}


void minheap_heapsort (Heap* heap){
    int i;
    int n = heap->pos;
    maxheap_constroi_heap(heap);
    for (i = heap->pos - 1; i >= 1; i--) {
        troca(0, i, heap->prioridade);
        heap->pos--;
        maxheap_heapify_int(heap, 0);
    }
    heap->pos = n;
}

/////////////////////////

int *maxheap_cria_listaordenada (Heap *heap, int tam){
  int i = 0;
  int *ordenado = (int *)malloc(tam * sizeof(int));
  //for(i=0; i < tam; i++)
  //  ordenado[i] = maxheap_remove(heap);
  while (tam--)
    ordenado[i++] = maxheap_remove(heap);
    
  return ordenado;
}

int *minheap_cria_listaordenada (Heap *heap, int tam){
  int i = 0;
  int *ordenado = (int *)malloc(tam * sizeof(int));
  //for(i=0; i < tam; i++)
  //  ordenado[i] = minheap_remove(heap);
  while (tam--)
    ordenado[i++] = minheap_remove(heap);
  return ordenado;
}


int* minheap_sort (int nums[], int tam) {
    int i;
    Heap *heap = heap_cria (tam);
    
    for(i = 0; i < tam; i++)
        minheap_insere(heap, nums[i]);

    int *novosnums = minheap_cria_listaordenada (heap, tam);
    
    heap_libera(heap);
    return novosnums;
}  


int* maxheap_sort (int nums[], int tam) {
    int i;
    Heap *heap = heap_cria (tam);
    
    for(i = 0; i < tam; i++)
        maxheap_insere(heap, nums[i]);
    
    int *novosnums = maxheap_cria_listaordenada (heap, tam);
    
    heap_libera(heap);
    return novosnums;
}  
