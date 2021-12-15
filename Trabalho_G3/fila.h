#include "lista.h"

typedef struct fila {
	Lista* ini;
	Lista* fim;
} Fila;

Fila* fila_cria(void);

void fila_insere(Fila* f, int info);

int fila_retira(Fila* f);

int fila_vazia(Fila* f);

void fila_libera(Fila* f);