typedef struct abb Abb;

Abb* abb_cria (void);
Abb* abb_busca (Abb* r, int v);
Abb* abb_min (Abb* r);
Abb* abb_prox (Abb* r);
void abb_imprime (Abb* a);
Abb* cria_filho (Abb* pai, int val);
Abb* abb_insere (Abb* r, int val);
Abb* abb_retira (Abb* r, int val);
void arv_imprime_aninhado (Abb* a);
int max (int a, int b);
int altura (Abb* a);
int esta_Balanceada (Abb* a);
