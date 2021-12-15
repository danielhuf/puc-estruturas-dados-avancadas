#include "lista.h"

typedef struct pilha {
	Lista* topo;
} Pilha;

Pilha* pilha_cria(void);

void pilha_push(Pilha* p, int v);

int pilha_pop(Pilha* p);

int pilha_vazia(Pilha* p);

void pilha_libera(Pilha* p);

int pilha_topo(Pilha * p);