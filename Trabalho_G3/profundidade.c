#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include "pilha.h"
#include "profundidade.h"
#define NIL -1

struct _viz {
	int noj;
	int peso;
	struct _viz* prox;
};
typedef struct _viz Viz;

struct _grafo {
	int nv;      /* numero de nos ou vertices */
	int na;      /* numero de arestas */
	Viz** viz;   /* viz[i] aponta para a lista de arestas incidindo em i */
	char *info;  /* letra referente a cada ponto no mapa */
};

int* buscaProfundidade(Grafo *g, int origem, int destino, int *cont) {
	Pilha *p;
	char *visits;
	int i, atual, *prev;
	Viz *v;

	prev = (int*)malloc(sizeof(int) * g->nv);
	assert(prev);

	//Cria vetor de visitados iniciados com 0
	visits = (char*)malloc(sizeof(char) * g->nv);
	assert(visits);
	for (i = 0; i < g->nv; i++) {
		prev[i] = -1;
		visits[i] = 0;
	}

	p = pilha_cria();
	pilha_push(p, origem);
	visits[origem] = 1;
	prev[origem] = origem;

    *cont = 0;

	while (!pilha_vazia(p) && !visits[destino]) {
		atual = pilha_pop(p);

		for (v = g->viz[atual]; v != NULL; v = v->prox) {
			if (!visits[v->noj]) {
				pilha_push(p, v->noj);
				prev[v->noj] = atual;
				visits[v->noj] = 1;
                (*cont)++;
			}
		}
	}

    pilha_libera(p);
	free(visits);
	return prev;
}