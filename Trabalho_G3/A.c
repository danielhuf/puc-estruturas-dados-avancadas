#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "grafo.h"
#include "A.h"
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


/*Função heurística Manhattan*/
static int distManhattan (Grafo *g, int origem, int destino, int col) {
	int xo, yo, xd, yd;
	xo = origem % col;
	yo = origem / col;
	xd = destino % col;
	yd = destino / col;
	
	return abs(xo - xd) + abs(yo - yd);
}

/*Mostra pontos visitados no mapa*/
static void mostra_visits (Grafo *g, int* cmc, int col) {
	char *infoCpy;
	int i;

	infoCpy = (char*)malloc(sizeof(char) * g->nv);
	assert(infoCpy);
	for (i = 0; i < g->nv; i++) {
		if (cmc[i])
			infoCpy[i] = g->info[i];
		else
			infoCpy[i] = ' ';
	}
		
	for (i = 0; i < g->nv; i++) {
		printf("%c", infoCpy[i]);
		if ((i + 1) % col == 0)
			printf("\n");
	}
	printf("\n\n");
	free(infoCpy);
	return;
}


/*Algorítimo A* */
int *A (Grafo *g, int origem, int destino, int col, int *cont) {
	int i, u, v, alt, altm, *dist, *prev, *visits, *inftemp;
	Viz *p;
	Heap *h;

	dist = (int*)malloc(sizeof(int) * g->nv);
	assert(dist);

	prev = (int*)malloc(sizeof(int) * g->nv);
	assert(prev);

	visits = (int*)malloc(sizeof(int) * g->nv);
	assert(visits);

	h = heap_cria(g->nv);

	dist[origem] = 0;
	prev[origem] = origem;

	for (i = 0; i < g->nv; i++) {
		if (i != origem) {
			dist[i] = INT_MAX;
			prev[i] = NIL;
			visits[i] = 0; //todos os pontos não visitados
		}
		inftemp = (int*)malloc(sizeof(int));
		assert(inftemp);
		*inftemp = i;

		minheap_insere(h, dist[i], inftemp);
	}

	(*cont) = 0; //contador de verticies

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
				altm = dist[u] + p->peso + distManhattan(g,v,destino,col); //f(x)=g(x)+h(x)
				if (alt < dist[v]) {
					dist[v] = alt;
					prev[v] = u;
					minheap_diminui2(h, altm, v);
				}
			}
			else if (v == destino) {
				heap_libera(h);
				free(dist);
        mostra_visits(g,visits,col);
        free(visits);
				return prev;
			}
		}
	}
	heap_libera(h);
	free(dist);
    free(visits);

	return prev;
}