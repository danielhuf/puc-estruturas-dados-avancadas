typedef struct _grafo Grafo;

Grafo* grafo_cria(int nv);

void grafo_insere_info_vertice(Grafo* g, int v, char info);

void grafo_insere_aresta(Grafo* g, int v1, int v2, int peso);

void grafo_imprime(Grafo* g, int col);

void grafo_destroi(Grafo* g);

int grafo_distancia(Grafo *g, int no, int nd);

int mostra_prev(Grafo *g, int *prev, int vd, int col);

void mostra_prev2(Grafo *g, int* cmc, int nd, int col);