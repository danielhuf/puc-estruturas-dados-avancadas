#include <stdlib.h>
#include "UnionFind.h"

UniaoBusca* ub_cria(int tam) {
	UniaoBusca *u = (UniaoBusca*)malloc(sizeof(UniaoBusca));
	u->n = tam;
	u->v = (int*)malloc(sizeof(int)*tam);
	for (int i = 0; i < tam; i++)
		u->v[i] = -1;
	return u;
}

int ub_busca(UniaoBusca* ub, int u) {
	int x = u;
	int aux;
	if ((u < 0) || (u > ub->n)) return -1;
	while (ub->v[u] >= 0) u = ub->v[u];
	while (ub->v[x] >= 0) {
		aux = x; x = ub->v[x]; ub->v[aux] = u;
	}
	return u;
}

int ub_uniao(UniaoBusca* ub, int u, int v) {
	u = ub_busca(ub, u);
	v = ub_busca(ub, v);

	if (u == v)
		return u;

	if (ub->v[u] > ub->v[v]) { /* negativos: v[u] menor em modulo! */
		ub->v[v] += ub->v[u]; /* atualiza o numero de nos de v */
		ub->v[u] = v;
		return v;
	}
	else { /* arvore em v tem menos nos */
		ub->v[u] += ub->v[v]; /* atualiza o numero de nos de u */
		ub->v[v] = u;
		return u;
	}
}

void ub_libera(UniaoBusca *ub) {
	free(ub->v);
	free(ub);
}