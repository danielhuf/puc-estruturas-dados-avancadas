#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

Lista* lista_cria(void)
{
	return NULL;
}

Lista* lista_insere(Lista* lista, int info)
{
	Lista* novo = (Lista*)malloc(sizeof(Lista));
	novo->info = info;
	novo->prox = lista;
	return novo;
}

Lista* lista_retira_primeiro(Lista* lista)
{
	Lista* p = lista; /* ponteiro para percorrer a lista */

	/* retira Lista */
	lista = p->prox; /* retira Lista do inicio */
	free(p);
	return lista;
}



int lista_vazia(Lista* lista)
{
	if (lista == NULL)
		return 1;
	else
		return 0;
}

void lista_libera(Lista* lista)
{
	Lista* p = lista;
	Lista* t;
	while (p != NULL)
	{
		t = p->prox; /* guarda referência p/ próx. Lista */
		free(p); /* libera a memória apontada por p */
		p = t; /* faz p apontar para o próximo */
	}
}

int lista_tamanho(Lista* lista)
{
	Lista* p = lista;
	int count = 0;
	while (p != NULL)
	{
		p = p->prox;
		count++;
	}
	return count;
}