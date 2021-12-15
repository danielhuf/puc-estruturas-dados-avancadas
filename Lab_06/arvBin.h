typedef struct noArv NoArv;

NoArv* arv_criavazia (void);
NoArv* arv_cria (char c, NoArv* sae, NoArv* sad);
NoArv* arv_libera (NoArv* a);
int arv_vazia (NoArv* a);
int arv_pertence (NoArv* a, char c);
void arv_imprime_aninhado (NoArv* a);
void imprime_pre_ordem (NoArv* a);
void imprime_ordem_simetrica (NoArv* a);
void imprime_pos_ordem (NoArv* a);
