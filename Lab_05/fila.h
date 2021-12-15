typedef struct lista Lista;
typedef struct fila Fila;

Fila* fila_cria (void);
void fila_insere (Fila* f, int pedido, char* prato);
void fila_passa (Fila* origem, Fila* destino);
void fila_libera (Fila* f);
int fila_vazia (Fila* f);
void imprime_fila (Fila* f);