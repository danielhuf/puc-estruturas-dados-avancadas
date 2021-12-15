typedef struct elemento Elemento;
typedef struct pilha Pilha;

Pilha* pilha_cria (void);
int pilha_push (Pilha* p, int v);
int pilha_peek (Pilha* p);
int pilha_pop (Pilha* p);
void pilha_libera (Pilha* p);
int pilha_vazia (Pilha* p);
void imprime_pilha (Pilha* p, char* nome);
int tamanho_pilha (Pilha* p);
Pilha* seleciona (int num, Pilha* pino1, Pilha* pino2, Pilha* pino3);