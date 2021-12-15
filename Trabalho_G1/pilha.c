#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

// nó da pilha para armazenar inteiros ou caracteres
struct elemento {
	char tipo;
	void *info;
	struct elemento *prox;
};
typedef struct elemento Elemento;
//tipo 0: info é valor int
//tipo 1: info é valor char

// Estrutura da pilha
struct pilha {
	Elemento* topo;
};

Pilha* pilha_cria (void) {
	Pilha *p = (Pilha*)malloc(sizeof(Pilha));
	if (p == NULL)
		exit(1);
	p->topo = NULL;
	return p;
}

void pilha_push (Pilha* p, char tipo, void *v) {
	Elemento *n = (Elemento*)malloc(sizeof(Elemento));
	if (n == NULL) { printf("Sem memória para alocar elemento.\n"); exit(1);}
	
	n->tipo = tipo;
	n->info = v;
	n->prox = p->topo;
	p->topo = n;
}

void* pilha_pop (Pilha* p, char *tipo) {
	Elemento *t;
	void *info;
	if (pilha_vazia(p)) { 
	    printf("Pilha vazia.\n"); 
	    exit(1);
	}
	
	t = p->topo;
	*tipo = t->tipo;
	info = t->info;
	p->topo = t->prox;
	
	free(t);
	return info;
}

void* pilha_le_topo (Pilha* p, char *tipo) {
	Elemento *t;
	void *info;
	if (pilha_vazia(p)) { 
	    printf("Pilha vazia.\n"); 
	    exit(1);
	}
	
	// Pega informações do topo da pilha
	t = p->topo;
	*tipo = t->tipo;
	info = t->info;
	return info;
}

void pilha_libera(Pilha* p) {
	Elemento *t, *q = p->topo;
	while (q != NULL)
	{
		t = q->prox;
		free(q->info);
		free(q);
		q = t;
	}
	free(p);
}

int pilha_vazia(Pilha* p) {
	return (p->topo == NULL); 
}

void imprime_elementos_h(Elemento *t) {
	if (t != NULL) {
		imprime_elementos_h(t->prox);
		if (t->tipo == 0) {
			int i = *((int*)t->info);
			printf("%d", i);
		}
		else {
			char op = *((char*)t->info);
			printf("%c", op);
		}
	}
}

void pilha_imprime_h(Pilha *p) {
	if (pilha_vazia(p)) {
		printf("Pilha vazia.\n");
		return;
	}
	Elemento *t = p->topo;
	imprime_elementos_h(t);
	printf("\n");
}

// Inverte a ordem de elementos da Pilha
Pilha* roda_vagao(Pilha *p) {
	Pilha *p2 = pilha_cria();
	char c;
	void *v;
	while (!pilha_vazia(p)) {
		v = pilha_pop(p, &c);
		pilha_push(p2, c, v);
	}
	pilha_libera(p);
	return p2;
}