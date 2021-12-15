#include<stdio.h>
#include<stdlib.h>
#include "minheap.h"

struct _heap {
	int max; /* tamanho maximo do heap */
	int pos; /* proxima posicao disponivel no vetor */
	int* prioridade; /* vetor das prioridades */
	void** info; /* vetor das informações */
};

static void troca(int a, int b, int* v) {
	int f = v[a];
	v[a] = v[b];
	v[b] = f;
}

static void troca2(int a, int b, void** v) {
	void *f = v[a];
	v[a] = v[b];
	v[b] = f;
}

static void corrige_acima(Heap* heap, int pos) {
	int pai;
	while (pos > 0) {
		pai = (pos - 1) / 2;
		if (heap->prioridade[pai] > heap->prioridade[pos]) {
			troca(pos, pai, heap->prioridade);
			troca2(pos, pai, heap->info);
		}
		else
			break;
		pos = pai;
	}
}

void minheap_insere(Heap* heap, int prioridade, void *info)
{
	if (heap->pos < heap->max)
	{
		heap->prioridade[heap->pos] = prioridade;
		heap->info[heap->pos] = info;
		corrige_acima(heap, heap->pos);
		heap->pos++;
	}
	else {
		printf("Heap CHEIO!\n");
		exit(1);
	}
}

// heapify iterativo
static void corrige_abaixo(Heap* heap) {
	int pai = 0;
	int filho_esq, filho_dir, filho;

	while (2 * pai + 1 < heap->pos) {
		filho_esq = 2 * pai + 1;
		filho_dir = 2 * pai + 2;

		if (filho_dir >= heap->pos) filho_dir = filho_esq;

		if (heap->prioridade[filho_esq] < heap->prioridade[filho_dir])
			filho = filho_esq;
		else
			filho = filho_dir;

		if (heap->prioridade[pai] > heap->prioridade[filho]) {
			troca(pai, filho, heap->prioridade);
			troca2(pai, filho, heap->info);
		}
		else
			break;

		pai = filho;
	}
}

void *minheap_remove(Heap* heap)
{
	if (heap->pos > 0) {
		void *topo = heap->info[0];
		heap->prioridade[0] = heap->prioridade[heap->pos - 1];
		heap->info[0] = heap->info[heap->pos - 1];
		heap->pos--;
		corrige_abaixo(heap);
		return topo;
	}
	else {
		printf("Heap VAZIO!");
		exit(1);
	}
}

void minheap_diminui(Heap *heap, int prioridade, void *info) {
	int i, pai;

	for (i = 0; i < heap->pos && heap->info[i] != info; i++);
	if (i == heap->pos) {  /* Info não está na heap */
		exit(1);
	}
	heap->prioridade[i] = prioridade;
	pai = (i - 1) / 2;

	while (i>0 && heap->prioridade[i] < heap->prioridade[pai]) {
		troca(i, pai, heap->prioridade);
		troca2(i, pai, heap->info);
		i = pai;
		pai= (i - 1) / 2;
	}
}

void minheap_diminui2(Heap *heap, int prioridade, int info) {
	int i, pai;

	for (i = 0; i < heap->pos && *((int*)heap->info[i]) != info; i++);
	if (i == heap->pos) {
		printf("Info %d nao esta na heap\n", info);
		exit(1);
	}
	heap->prioridade[i] = prioridade;
	pai = (i - 1) / 2;

	while (i > 0 && heap->prioridade[i] < heap->prioridade[pai]) {
		troca(i, pai, heap->prioridade);
		troca2(i, pai, heap->info);
		i = pai;
		pai = (i - 1) / 2;
	}
}

void minheap_aumenta(Heap *heap, int prioridade, void *info) {
	int i, filho_esq, filho_dir;

	for (i = 0; i < heap->pos && heap->info[i] != info; i++);
	if (i == heap->pos) {
		exit(1);
	}
	filho_esq = 2 * i + 1;
	filho_dir = 2 * i + 2;

	while ((filho_esq < heap->pos &&
		heap->prioridade[i] > heap->prioridade[filho_esq]) ||
		(filho_dir < heap->pos &&
		heap->prioridade[i] > heap->prioridade[filho_dir])) {
		if (filho_dir < heap->pos &&
			heap->prioridade[filho_esq] < heap->prioridade[filho_dir]) {
			troca(i, filho_esq, heap->prioridade);
			troca2(i, filho_esq, heap->info);
			i = filho_esq;
		}
		else {
			troca(i, filho_dir, heap->prioridade);
			troca2(i, filho_dir, heap->info);
			i = filho_dir;
		}
		filho_esq = 2 * i + 1;
		filho_dir = 2 * i + 2;
	}
}