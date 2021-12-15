#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include <stdio.h>
#include "fila.h"
#include "largura.h"
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

int* buscaLargura(Grafo *g, int origem, int destino, int *cont) {
	Fila *f;
	char *visits;
	int i, atual, *prev;
	Viz *v;

	prev = (int*)malloc(sizeof(int) * g->nv);
	assert(prev);

	//Cria vetor de visitados iniciados com 0
	visits = (char*)malloc(sizeof(char) * g->nv);
	assert(visits);
	for (i = 0; i < g->nv; i++) {
		prev[i] = NIL;
		visits[i] = 0;
	}

	f = fila_cria();
	fila_insere(f, origem);
	visits[origem] = 1;
	prev[origem] = origem;

	*cont = 0;

	while (!fila_vazia(f) && !visits[destino]) {
		atual = fila_retira(f);

		for (v = g->viz[atual]; v != NULL; v = v->prox) {
			if (!visits[v->noj]) {
				fila_insere(f, v->noj);
				prev[v->noj] = atual;
				visits[v->noj] = 1;
				(*cont)++;
			}
		}
	}
	fila_libera(f);
	free(visits);
	return prev;
}