typedef struct aluno Aluno;
typedef struct elemento Elemento;

Elemento* lista_cria ();
Elemento* lista_insere_ordenado (Elemento* lista, int m, char* no, char* e, char *t);
Elemento* lista_atualiza (Elemento* lista, char* nomeAntigo, char* nomeNovo);
Elemento* lista_retira (Elemento* lista, char* no);
void lista_imprime (Elemento* lista);
Elemento* busca_nome (Elemento* lista, char* n);
int lista_igual (Elemento* lista1, Elemento* lista2);
int lista_vazia (Elemento* lista);
void lista_libera (Elemento* lista);
