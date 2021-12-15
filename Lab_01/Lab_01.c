#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno
{
    int mat;
    char *nome;
    char *end;
    char *tel;
} Aluno;

Aluno* criaAluno (int m, char* n, char* e, char* t)
{
    Aluno* al;
    al = (Aluno*)malloc(sizeof(Aluno));
    if (al==NULL)
        return NULL;
    al->mat = m;
    al->nome = (char*)malloc(81*sizeof(char));
    al->end = (char*)malloc(121*sizeof(char));
    al->tel = (char*)malloc(21*sizeof(char));
    strcpy(al->nome,n);
    strcpy(al->end,e);
    strcpy(al->tel,t);
    return al;
}

void printRecursivo(char *str) {
    if(*str=='\0')
        return;
    printf("%c", *str);
    printRecursivo(str+1);
}

int lenStringRecursivo(char *str) {
    if(*str=='\0')
        return 0;
    return 1 + lenStringRecursivo(str+1);
}

void exibeTodosAlunos (Aluno** vAl, int n)
{
    int i;
    printf("Dados dos alunos\n");
    for (i=0; i<n; i++) {
        printf("Matricula: %d", vAl[i]->mat);
        printf(" - Nome: "); printRecursivo(vAl[i]->nome);
        printf(" - Endereço: "); printRecursivo(vAl[i]->end);
        printf(" - Telefone: "); printRecursivo(vAl[i]->tel);
        printf("\n");
    }
}

int main()
{
	Aluno *vAl[8];
	int i;
	vAl[0]= criaAluno(444,"Luiz","rua A", "984376854");
	vAl[1]= criaAluno(111,"Rita","rua B", "989452763");
	vAl[2]= criaAluno(999,"Rute","avenida C", "939845735");
	vAl[3]= criaAluno(555,"Dina","rua D", "982537424");
	vAl[4]= criaAluno(777,"Lana","bairro E", "948579558");
	vAl[5]= criaAluno(666,"Tais","bairro F", "983429843");
	vAl[6]= criaAluno(222,"Cris","avenida G", "98468533");
	vAl[7]= criaAluno(333,"Vera","rua H", "959834759");

	exibeTodosAlunos(vAl, 8);
	printf("\n%d", lenStringRecursivo(vAl[2]->end));
	
	for (i=0; i<8; i++) {
	    free(vAl[i]->nome);
	    free(vAl[i]->end);
	    free(vAl[i]->tel);
	    free(vAl[i]);
	}
    return 0;
}

