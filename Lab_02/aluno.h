typedef struct aluno Aluno;

void inicializa (int n, Aluno** tab);
void preenche (int n, Aluno** tab, int i, int m, char* no, char* e, char *t);
void retira (int n, Aluno** tab, int i);
void imprime (int n, Aluno** tab, int i);
void imprime_tudo (int n, Aluno** tab);
int busca_lin (int n, Aluno** tab, char* nome);
