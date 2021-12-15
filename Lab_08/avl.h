typedef struct avl Avl;

Avl* avl_cria (void);
Avl* avl_insere (Avl* r, int info);
Avl* avl_remove (Avl *r, int info);
Avl* rotacao_esquerda (Avl *r);
Avl* rotacao_direita (Avl *r);
Avl* rotacao_esquerda_direita (Avl *r);
Avl* rotacao_direita_esquerda (Avl *r);
void avl_destroi (Avl* a);
void arv_imprime_aninhado (Avl* a);