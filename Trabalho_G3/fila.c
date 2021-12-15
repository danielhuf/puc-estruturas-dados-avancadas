#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

Fila* fila_cria(void) {
	Fila* f = (Fila*)malloc(sizeof(Fila));
	f->ini = NULL;
	f->fim = NULL;
	return f;
}

void fila_insere(Fila* f, int info) {

	Lista* n = lista_insere(NULL, info);

	/* verifica se lista não estava vazia */
	if (f->fim != NULL)
		f->fim->prox = n;
	else /* fila estava vazia */
		f->ini = n;
	f->fim = n; /* fila aponta para novo elemento */
}


int fila_retira(Fila* f) {

	int info;

	if (fila_vazia(f)) {
		printf("Fila vazia.\n");
		exit(1);
	} /* aborta programa */

	info = f->ini->info;

	f->ini = lista_retira_primeiro(f->ini);

	if (f->ini == NULL) /* verifica se fila ficou vazia */
		f->fim = NULL;

	return info;
}

int fila_vazia(Fila* f) {
	return lista_vazia(f->ini) && lista_vazia(f->fim);
}

void fila_libera(Fila* f) {
	lista_libera(f->ini);
	free(f);
}