typedef struct pilha Pilha;

Pilha* pilha_cria (void);

void pilha_push (Pilha* p, char tipo, void *v);

void* pilha_pop (Pilha* p, char *tipo);

int pilha_vazia (Pilha* p);

void pilha_libera (Pilha* p);

void pilha_imprime_h (Pilha *p);

void* pilha_le_topo (Pilha* p, char *tipo);

Pilha* roda_vagao (Pilha *p); //inverte uma pilha