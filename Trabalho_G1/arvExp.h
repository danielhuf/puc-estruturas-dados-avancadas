typedef struct arvExp ArvExp;

int arv_valorEA (ArvExp* arv);

ArvExp* arv_criavazia (void);

int arv_vazia (ArvExp* a);

ArvExp* arv_cria (void* info, char tipo);

ArvExp* arv_anexa (ArvExp* filho, ArvExp* atual);

void arv_imprime_aninhado (ArvExp* a);

void arv_libera (ArvExp* a);