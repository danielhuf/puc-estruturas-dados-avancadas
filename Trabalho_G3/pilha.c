#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

Pilha* pilha_cria()
{
	Pilha* p = (Pilha*)malloc(sizeof(Pilha));
	if (p == NULL) exit(1);
	p->topo = NULL;
	return p;
}

void pilha_push(Pilha* p, int valor)
{
	p->topo = lista_insere(p->topo, valor);
}

int cmp(int a, int b) {
	if (a < b)
		return -1;
	else if (a > b)
		return 1;

	return 0;
}

int pilha_pop(Pilha* p)
{
	int v;
	if (pilha_vazia(p))
	{
		printf("Pilha vazia.\n");
		exit(1); /* aborta programa */
	}
	v = p->topo->info;
	p->topo = lista_retira_primeiro(p->topo);

	return v;
}

int pilha_vazia(Pilha* p)
{
	return lista_vazia(p->topo);
}

void pilha_libera(Pilha* p)
{
	lista_libera(p->topo);
	free(p);
}

int pilha_topo(Pilha *p) {
	if (pilha_vazia(p))
	{
		return -1;
	}
	return *(int*)(p->topo->info);
}

void print(int *a) {
	printf("%d ", *a);
}