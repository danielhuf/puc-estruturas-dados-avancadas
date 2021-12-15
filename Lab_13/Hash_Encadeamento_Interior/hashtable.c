#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define TAMINICIAL 11
#define FATOR_AUMENTO 1.947

typedef struct ttabpos{
   int chave;
   int dados;
   int prox;
} Tabpos;

struct hashtable {
   int tam;
   int ocupadas;
   Tabpos *tabpos;
};

int hash(Hashtable* m, int chave)
{
	return (chave % m->tam);
}

Hashtable* hashtable_cria() {
   int i;
   
   Hashtable* m = (Hashtable*) malloc (sizeof(Hashtable));
   if (m==NULL) {
       printf("Erro na alocação! \n"); 
       exit(1);
   }
   
   m->tabpos = (Tabpos*) malloc (TAMINICIAL * sizeof(Tabpos));
   if (m->tabpos==NULL) {
       printf("Erro na alocação! \n");
       exit(1);
   }
   
   m->tam = TAMINICIAL;
   m->ocupadas = 0;
   
   for (i=0; i < TAMINICIAL; i++) {
      m->tabpos[i].chave = -1;
      m->tabpos[i].prox = -1;
   }
   return m;
}

Hashtable* hashtable_insere (Hashtable* m, int chave, int dados) {
   
   int poslivre, indconf;
   
   if (m->ocupadas > 0.75 * m->tam) hashtable_redimensiona(m);
   int pos = hash(m, chave);

    if (m->tabpos[pos].chave == -1) 
    {
		m->tabpos[pos].chave = chave;
		m->tabpos[pos].dados = dados;
		m->tabpos[pos].prox = -1;
		printf("\n ** Chave (%d) inserida na pos(%d) \n", chave, pos);
	}
	else
    {
		printf("\n *** Colisão ***  \n");
		poslivre = pos;
        do 
            poslivre = (poslivre+1) % (m->tam);
        while ((poslivre != pos) && (m->tabpos[poslivre].chave != -1)); 
        
        if (poslivre == pos) { /* tabela cheia -- não deveria acontecer */
            printf ("pânico, tabela cheia!\n"); exit(1);
        }

        /* achou posicao livre  - verificar quem vai para ela */
        indconf = hash(m, m->tabpos[pos].chave);
        if (indconf == pos) { /* conflito primario: encadeia */
            m->tabpos[poslivre].chave = chave;
            m->tabpos[poslivre].dados = dados;
            m->tabpos[poslivre].prox = m->tabpos[pos].prox;
            m->tabpos[pos].prox = poslivre;
        }
        else { /* conflito secundario: expulsa o item atual de pos */
                /* encontrar a posicao do item na lista */
            while (m->tabpos[indconf].prox != pos) 
                indconf = m->tabpos[indconf].prox;
        
            /* acertar encadeamento */
            m->tabpos[poslivre].chave = m->tabpos[pos].chave;
            m->tabpos[poslivre].dados = m->tabpos[pos].dados;
            m->tabpos[poslivre].prox = m->tabpos[pos].prox;
            m->tabpos[indconf].prox = poslivre;
            m->tabpos[pos].chave = chave;
            m->tabpos[pos].dados = dados;
            m->tabpos[pos].prox = -1;
        }
	}
	
	(m->ocupadas)++;
    return m;
}

Hashtable* hashtable_retira(Hashtable* m, int chave)
{
    int pos, posbusca, anterior;
    if (m==NULL) {
        printf("Erro na alocação! \n"); 
        exit(1);
    }

    anterior = -1;
    pos = hash(m, chave);
    posbusca = pos;
    
    while (m->tabpos[posbusca].chave != -1) {
        if (m->tabpos[posbusca].chave == chave){ // chave igual
	        if(anterior != -1)
	            m->tabpos[anterior].prox = m->tabpos[posbusca].prox;
		        
    		m->tabpos[posbusca].chave = -1;
		    m->tabpos[posbusca].dados = -1;
	        m->tabpos[posbusca].prox = -1;
	        
	        (m->ocupadas)--;
	        
            return m;
        }
        else if (hash(m, m->tabpos[posbusca].chave) != pos){ //chave diferente hash diferente
            printf("\n Chave não existe \n");
            return m;
        }
        else if (m->tabpos[posbusca].prox != -1){ // chave diferente hash igual
            anterior = posbusca;
            posbusca = m->tabpos[posbusca].prox;
        }
        else{ 
            printf("\n Chave não existe \n");
            return m;
        }
    }
    printf("\n Chave não existe \n");
    return m;
} 


int hashtable_busca (Hashtable *m, int chave) {

    int pos, posbusca;
    if (m==NULL) return -1;
    
    pos = hash(m, chave);
    posbusca = pos;
    
    while (m->tabpos[posbusca].chave != -1) {
        if (m->tabpos[posbusca].chave == chave) // chave igual
            return m->tabpos[posbusca].dados;
        
        else if (hash(m, m->tabpos[posbusca].chave) != pos) //chave diferente hash diferente
            return -1;
        
        else if (m->tabpos[posbusca].prox != -1) // chave diferente hash igual
            posbusca = m->tabpos[posbusca].prox;
        
        else return -1;
    }
    return -1;
}


void hashtable_redimensiona (Hashtable* m) {
    int i, pos;
    int tamanterior = m->tam;
    Tabpos* anterior = m->tabpos;
    
    hashtable_print_ocupacao(m);
    printf("\n**** Redimensionar ****\n");
    
    /* aumenta o tamanho */
    m->ocupadas = 0;  
    m->tam = FATOR_AUMENTO * m->tam;
    printf("novo tamanho: %d\n", m->tam);

    m->tabpos = (Tabpos*) malloc (m->tam * sizeof(Tabpos));
    if (m->tabpos==NULL) {
       printf("erro na alocação! \n");
       exit(1);
    }
    
    /* inicialização da nova tabela */
    for (i=0; i < m->tam; i++) {
        m->tabpos[i].chave = -1;
        m->tabpos[i].prox = -1;
    }

   /* e os elementos já inseridos na tabela anterior? */
    for (i=0; i < tamanterior; i++)
        if (anterior[i].chave != -1) 
            hashtable_insere (m, anterior[i].chave, anterior[i].dados);
    
    free (anterior);
}

void hashtable_exibir(Hashtable* m)
{
	int i;
	for (i = 0; i < m->tam; i++)
    {
		if (m->tabpos[i].chave == -1)
        {
			printf("\n Pos[%d] não tem elementos \n", i);
		}
		else 
        {
			printf("\n Pos[%d] tem elementos -: \t chave(%d) valor(%d) prox(%d)", i, m->tabpos[i].chave, m->tabpos[i].dados, m->tabpos[i].prox);
		}
	}
}

int hashtable_tamanho(Hashtable* m)
{
	return m->tam;
}

int hashtable_ocupacao(Hashtable* m)
{
	return m->ocupadas;
}

void hashtable_print_ocupacao(Hashtable* m){
    int n = hashtable_tamanho(m);
    int o = hashtable_ocupacao(m);
    float p = (float)o / (float)n;
    printf("\n** Ocupacao/Tamanho da Hash Table: (%d / %d) = %.2f\n", o, n, p);
}

void hashtable_destroi (Hashtable *m) {
  free (m->tabpos);
  free (m);
}