typedef struct lista {
	int info;
	struct lista *prox;
} Lista;

Lista* lista_cria(void);

Lista* lista_insere(Lista* lista, int info);

Lista* lista_retira_primeiro(Lista* lista);

int lista_vazia(Lista* lista);

void lista_libera(Lista* lista);