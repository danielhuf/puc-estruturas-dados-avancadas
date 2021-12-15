#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "grafo.h"
#include "kruskal.h"
#include "UnionFind.h"
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

struct aresta {
	int u;
	int v;
};

/* Algorítimo gerador de árvore geradora mínima com Kruskal*/
Aresta *kruskal(Grafo *g) {
	int i, pos;
	Aresta *A, a, *atemp;
	UniaoBusca *UB;
	Heap *h;
	Viz *p;

	A = (Aresta*)malloc(sizeof(Aresta)*(g->nv)-1);
	assert(A);

	UB = ub_cria(g->nv);

	h = heap_cria(g->na);
	for (i = 0; i < g->nv; i++) {
		for (p = g->viz[i]; p != NULL; p = p->prox) {
			atemp = (Aresta*)malloc(sizeof(Aresta));
			assert(atemp);
			atemp->u = i;
			atemp->v = p->noj;
			minheap_insere(h, p->peso, atemp);
		}
	}

	pos = 0;
	int cont = 0;
	
	while (!heap_vazia(h)) {
		
		atemp = minheap_remove(h);
		a = *atemp;
		free(atemp);

		if (ub_busca(UB, a.u) != ub_busca(UB, a.v)) {
			A[pos++] = a;
			ub_uniao(UB, a.u, a.v);
		}
	}
	heap_libera(h);
	ub_libera(UB);

	return A;
}