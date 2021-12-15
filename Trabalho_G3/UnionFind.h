struct uniaoBusca {
	int n; /* tamanho do vetor */
	int *v; /* vetor de elementos */
};

typedef struct uniaoBusca UniaoBusca;

/* cria particao de conjunto com tam elementos */
UniaoBusca* ub_cria(int tam);

/* retorna o representante da parte em que está u */
int ub_busca(UniaoBusca* ub, int u);

/* retorna o representante do resultado */
int ub_uniao(UniaoBusca* ub, int u, int v);

void ub_libera(UniaoBusca *ub);