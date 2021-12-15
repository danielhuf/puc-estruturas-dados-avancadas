#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "grafo.h"
#include "dijkstra.h"
#include "minheap.h"
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

/* Algorítimo do Dijkstra */
int *Dijkstra (Grafo *g, int origem, int *cont) {
	int i, u, v, alt, *dist, *prev, *visits, *inftemp;
	Viz *p;
	Heap *h;
	
	dist = (int*)malloc(sizeof(int) * g->nv);
	assert(dist);

	prev = (int*)malloc(sizeof(int) * g->nv);
	assert(prev);

	visits = (int*)malloc(sizeof(int) * g->nv);
	assert(visits);

	h = heap_cria(g->nv);

	*cont = 0;

	dist[origem] = 0;
	prev[origem] = origem;

	for (i = 0; i < g->nv; i++) {
		if (i != origem) {
			dist[i] = INT_MAX;
			prev[i] = NIL;
			visits[i] = 0;
		}
		inftemp = (int*)malloc(sizeof(int));
		assert(inftemp);
		*inftemp = i;

		minheap_insere(h, dist[i],inftemp);
	}
	
	while (!heap_vazia(h)) {
		inftemp = (int*)minheap_remove(h);
		u = *inftemp;
		free(inftemp);
		visits[u] = 1;
		(*cont)++;
		for (p = g->viz[u]; p != NULL; p = p->prox) {
			v = p->noj;
			if (!visits[v]) {
				alt = dist[u] + p->peso;
				if (alt < dist[v]) {
					dist[v] = alt;
					prev[v] = u;
					minheap_diminui2(h, alt, v);
				}
			}
		}
	}
	heap_libera(h);
  free(visits);
	free(dist);
	
	return prev;
}