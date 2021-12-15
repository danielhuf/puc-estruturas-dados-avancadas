#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "grafo.h"
#include "prim.h"
#define NIL -1
#define NUM_COL 8

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

int cont = 0;

Aresta menor_aresta(Grafo *g, int *U) {
	int i, custo, u, v, d;
	Viz *p;
	Aresta a;

	custo = INT_MAX;
	for (i = 0; i < g->nv; i++) {
		if (U[i]) {
			for (p = g->viz[i]; p != NULL; p = p->prox) {
				if (!U[p->noj]) {

					d = grafo_distancia(g, i, p->noj);
					if (d < custo) {
						custo = d;
						u = i;
						v = p->noj;
					}

					d = grafo_distancia(g, p->noj, i);
					if (d < custo) {
						custo = d;
						u = p->noj;
						v = i;
					}

				}
			}
		}
	}
	a.u = u;
	a.v = v;
	return a;
}

Aresta *prim(Grafo *g) {
	int i, pos, *U;
	Aresta *T, a;

	T = (Aresta*)malloc(sizeof(Aresta)*(g->nv) - 1);
	assert(T);

	U = (int*)malloc(sizeof(int)*(g->nv));
	assert(U);

	for (i = 0; i < g->nv; i++) {
		U[i] = 0;
	}
	
	pos = 0;
	U[0] = 1;
	while (pos < g->nv - 1) {
		a = menor_aresta(g, U);

		T[pos] = a;
		U[a.v] = 1;
		U[a.u] = 1;
		pos++;
	}
	free(U);

	return T;
}

int imprime_arv(Aresta *arv, Grafo *g, int col) {
	char *infoCpy;
	int i, custo, posu, posv, rcol = col * 2 - 1;
	Aresta a;

	infoCpy = (char*)malloc(sizeof(char) * (g->nv * 4));
	assert(infoCpy);

	for (i = 0; i < (g->nv * 4); i++) {
		infoCpy[i] = ' ';
	}

	for (i = 0; i < g->nv; i++) {
		infoCpy[(i / col) * 2 * rcol + (i % col) * 2] = g->info[i];
	}

	custo = 0;
	for (i = 0; i < g->nv - 1; i++) {
		a = arv[i];
		if (a.u < 0 || a.v < 0) {
			printf("Indice negativo:\n i: %d\n", i);
			printf("%d->%d ", arv[i].u, arv[i].v);
			exit(1);
		}
		posu = (a.u / col) * 2 * rcol + (a.u % col) * 2;
		posv = (a.v / col) * 2 * rcol + (a.v % col) * 2;
		if (posu > posv) {
			if (posu - posv == 2)
				infoCpy[posv + 1] = '_';
			else
				infoCpy[posv + rcol] = '|';

		}
		else {
			if (posv - posu == 2)
				infoCpy[posu + 1] = '_';
			else
				infoCpy[posu + rcol] = '|';
		}
		custo += grafo_distancia(g, a.u, a.v);

	}
	for (i = 0; i < (g->nv * 4); i++) {
		printf("%c", infoCpy[i]);
		if ((i + 1) % rcol == 0)
			printf("\n");
	}

	free(infoCpy);
	return custo;
}