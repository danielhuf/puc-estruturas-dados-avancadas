/******************************************************************************

LAB 13 Hashtable c/ encadeamento exterior
INF1010 Estrutura de Dados Avançadas
Prof. Augusto Baffa

Implementar uma tabela de dispersão (ou hash) criando o TDA hashtable (interface hashtable.h e arquivo hashtable.c).

Utilizar as seguintes estruturas para representar a tabela:

////
typedef struct {
   int chave;
   int dados;
   int prox;
} ttabpos;

typedef struct smapa {
   int tam;
   int ocupadas;
   ttabpos *tabpos;
} Mapa;

/////

As estruturas podem ficar no arquivo hashtable.c pois não serão acessadas pelo main.c
A strutura smapa armazena o tamanho do vetor, a quantidade de casas ocupadas e o vetor da estrutura ttabpos (chamado tabpos)
Deve-se utilizar o encadeamento interno para tratar conflitos.
A tabela (tabpos) contém a chave, o valor (dados) e o campo prox que aponta para o próximo índice que contém outra chave para a mesma hash.
Ambas as variáveis recebem o valor inicial -1 indicando a ausência de valores.

///////////////////////////////////
//interface arquivo hashtable.h
typedef struct smapa Mapa;

Mapa* cria (void);
void redimensiona (Mapa* m);
Mapa* insere (Mapa* m, int chave, int dados);
int busca (Mapa *m, int chave);
Mapa* retira (Mapa *m, int chave);

void exibir(Mapa* m);
void print_ocupacao(Mapa* m);
void destroi (Mapa *m);
///////////////////////////////////

Utilize o programa já criado na Main para testar sua implementação!

Implemente a função insere, inicialmente sem redimensionamento. O esqueleto de implementação está criando tabelas com 11 posições. A função insere deve seguir o seguinte algoritmo:
. Calcula pos fazendo o hash da chave modulo o tamanho da tabela
. Caso pos esteja livre, realiza inserção e retorna. Caso contrário, procura por poslivre, uma próxima posição livre na tabela.
. Caso a chave em pos tenha o mesmo valor de hash que a chave a inserir, estamos em um conflito primário: insere a nova chave em poslivre e encadeia poslivre na lista atual.
. Caso a chave em pos tenha valor diferente de hash que a chave a inserir, estamos em um conflito secundário: move a chave em pos para poslivre e corrige a lista encadeada referente aos conflitos deste outro valor de hash.

Obs: A função de hash usada inicialmente gera conflitos para todos os números iguais módulo o tamanho da tabela (definido inicialmente como 11). Use isto para gerar conflitos propositalmente.

Implemente o redimensionamento da tabela (função redimensiona, chamado quando a tabela atinge 75% de ocupação - há rascunho nos slides)

Implemente a função de busca. (Não há rascunho essa função)
Implemente a função de retirada. (Não há rascunho essa função)


*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"


int main()
{
    int opcao, chave, dados;

	Hashtable* m = hashtable_cria();
 
	do {
	    printf("\n---------------------\n");
		printf("Hash Table em C \n\n");
		printf("MENU-:\n1.Inserir item na Hash Table" 
                    "\n2.Remover item da Hash Table"
		            "\n3.Verificar tamanho da Hash Table" 
                    "\n4.Exibir dados da Hash Table"
                    "\n0.Sair"
		       "\n\n Selecione uma opcao -:");
 
		scanf("%d", &opcao);
 
		switch(opcao){
 
        	case 1:
        
        	      printf("Inserir elemento na Hash Table\n");
        
        	      printf("Entre com a chave -:\t");
        	      scanf("%d", &chave);
        
        	      printf("Entre com o valor (int) -:\t");
        	      scanf("%d", &dados);		      
        	      m = hashtable_insere (m, chave, dados);
        
        	      break;
        
        	case 2:
        
        	      printf("Remover elemento da Hash Table \n Entrar com a chave para apagar-:");
        	      scanf("%d", &chave);
        	      hashtable_retira(m, chave);
        	      
        	      break;
        
        	case 3:
        
        	      hashtable_print_ocupacao(m);
        	      break;
        
        	case 4:
        
        	      hashtable_exibir(m);
        
        	      break;
        	 case 0:
        	    break;
        
        	default:
        	       printf("Opcao invalida\n");
 
		}

 
	}while(opcao != 0);
 
	
    hashtable_destroi(m);

    return 0;
}






