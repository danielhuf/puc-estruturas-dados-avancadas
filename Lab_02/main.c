#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"

int main()
{
	Aluno *tab[8];
	int pos;
	inicializa(8, tab);
	
	preenche(8, tab, 0, 444,"Luiz","rua A", "984376854");
	preenche(8, tab, 1, 111,"Rita","rua B", "989452763");
	
	//Com o exemplo abaixo, pode-se perceber que a função atualiza já está "embutida" na função preenche
	preenche(8, tab, 0, 999,"Rute","avenida C", "939845735");
	
	imprime_tudo(8, tab);
	
	pos = busca_lin(8, tab, "Rita");
	if (pos!=-1)
	    printf("Nome encontrado na posição %d da tabela!", pos);
	else
	    printf("Nome não foi encontrado na tabela");
	
	retira(8, tab, 0);
	retira(8, tab, 1);

    return 0;
}
