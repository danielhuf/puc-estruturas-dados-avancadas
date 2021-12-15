typedef struct hashtable Hashtable;

Hashtable* hashtable_cria(void);
void hashtable_redimensiona (Hashtable* m);
Hashtable* hashtable_insere (Hashtable* m, int chave, int dados);
int hashtable_busca (Hashtable *m, int chave);
Hashtable* hashtable_retira (Hashtable *m, int chave);

void hashtable_exibir(Hashtable* m);
void hashtable_destroi (Hashtable *m);

int hashtable_ocupacao(Hashtable* m);
int hashtable_tamanho(Hashtable* m);
void hashtable_print_ocupacao(Hashtable* m);