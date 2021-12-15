#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "grafo.h"

#define NIL -1

/* quantidade de vértices: 82*40=3280 -> ao quadrado = 10758400 */
/* quantidade de arcos: (81*40 + 39*82)*2 = 12876 */
/* E << V^2 -> representação por lista de adjacências! */

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

static Viz* criaViz(Viz* head, int noj, int peso) { /* insere vizinho no inicio da lista */
	Viz* no = (Viz*)malloc(sizeof(Viz));
	assert(no);
	no->noj = noj;
	no->peso = peso;
	no->prox = head;
	return no;
}

Grafo* grafo_cria(int nv) {
	int i;
	Grafo* g = (Grafo *)malloc(sizeof(Grafo));
	assert(g);
	g->nv = nv;
	g->na = 0;
	g->viz = (Viz **)malloc(sizeof(Viz *) * nv);
	assert(g->viz);
	for (i = 0; i < nv; i++)
		g->viz[i] = NULL;
	g->info = (char*)malloc(sizeof(char) * nv);
	assert(g->info);
	return g;
}

void grafo_insere_info_vertice(Grafo* g, int v, char info) {
	(g->info[v]) = info;
}

void grafo_insere_aresta(Grafo* g, int vo, int vd, int peso) { /* cria caminho de v1 para v2 */
	Viz *p;
	p = criaViz(g->viz[vo], vd, peso);
	g->viz[vo] = p;
	g->na++;
}

void grafo_imprime(Grafo* g, int col) {
	int i;
	printf("Grafo construido:\n");
	for (i = 0; i < g->nv; i++) {
		printf("%c", g->info[i]);
		if ((i + 1) % col == 0)
			printf("\n");
	}
}

void grafo_destroi(Grafo* g) {
	int i, nv;
	Viz *p, *q;
	nv = g->nv;
	for (i = 0; i < nv; i++) {
		p = g->viz[i];
		while (p != NULL) {
			q = p->prox;
			free(p);
			p = q;
		}
	}
	free(g->viz);
	free(g->info);
	free(g);
}

/* Retorna o custo do vértice no para o vértice nd no grafo */
int grafo_distancia(Grafo *g, int no, int nd) {
	Viz *p;
	for (p = g->viz[no]; p != NULL; p = p->prox) {
		if (p->noj == nd)
			return p->peso;
	}
	printf("Distancia nao encontrada\n");
	return INT_MAX;
}

/* Imprime o caminho no mapa e retorna o custo do mesmo*/
int mostra_prev(Grafo *g, int *prev, int vd, int col) {
	char *infoCpy;
	int i, c, vfin = vd;
	int atual;

	infoCpy = (char*)malloc(sizeof(char) * g->nv);
	assert(infoCpy);
	for (i = 0; i < g->nv; i++)
		infoCpy[i] = '#';
	
	atual = vd;
	c = 0;
	while (prev[atual] != atual) {
		infoCpy[atual] = ' ';
		c += grafo_distancia(g, prev[atual], atual);
		atual = prev[atual];
		if (atual<0 || atual>g->nv) {
			printf("Prev invalido\n");
			exit(1);
		}
	}
	infoCpy[atual] = g->info[atual];
	infoCpy[vfin] = g->info[vfin];

	for (i = 0; i < g->nv; i++) {
		printf("%c", infoCpy[i]);
		if ((i + 1) % col == 0)
			printf("\n");
	}

	free(infoCpy);
	return c;
}

/* forma alternativa de imprimir caminho no mapa*/
void mostra_prev2(Grafo *g, int* cmc, int nd, int col) {
	char *infoCpy;
	int i, vfin = nd;

	infoCpy = (char*)malloc(sizeof(char) * g->nv);
	assert(infoCpy);
	for (i = 0; i < g->nv; i++)
		infoCpy[i] = ' ';

	while (cmc[nd] != nd) {
		infoCpy[nd] = g->info[nd];
		nd = cmc[nd];
	}
	infoCpy[nd] = g->info[nd];
	infoCpy[vfin] = g->info[vfin];

	for (i = 0; i < g->nv; i++) {
		printf("%c", infoCpy[i]);
		if ((i + 1) % col == 0)
			printf("\n");
	}

	free(infoCpy);
	return;
}