#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

#define TAMINICIAL 2
#define FATOR_AUMENTO 1.947

typedef struct hashtable_item {
   int chave;
   int dados;
   struct hashtable_item *prox;
} Hashtable_item;

typedef struct ttabpos {
   Hashtable_item *ini;
   Hashtable_item *fim;
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
      m->tabpos[i].ini = NULL;
      m->tabpos[i].fim = NULL;
   }
   return m;
}


/* lista */
Hashtable_item* lista_busca (Hashtable_item* lista, int chave)
{
    Hashtable_item* p;
    for (p = lista; p != NULL; p = p-> prox)
    {
        if (p->chave == chave)
            return p; /* achou o Lista */
    }
    return NULL; /* não achou o Lista */
}

/*****************/

Hashtable* hashtable_insere (Hashtable* m, int chave, int dados) {
   
    int poslivre, indconf;
   
    if (m->ocupadas > 0.75 * m->tam) hashtable_redimensiona(m);
   
    int pos = hash(m, chave);

    Hashtable_item *lista = m->tabpos[pos].ini;
    
	/* Creating an item to insert in the Hash Table */
	Hashtable_item *item = (Hashtable_item*) malloc(sizeof(Hashtable_item));
	item->chave = chave;
	item->dados = dados;
	item->prox = NULL;
    
    if (lista == NULL) 
    {
		printf("\n ** Chave (%d) inserida na pos(%d) \n", chave, pos);
        m->tabpos[pos].ini = item;
        m->tabpos[pos].fim = item;

		(m->ocupadas)++;
	}
	else
    {
		printf("\n *** Colisão ***  \n");
		
		Hashtable_item *colid_item = lista_busca (lista, chave);
		
		if(colid_item == NULL){
    		printf("\n ** Chave (%d) inserida na pos(%d) após colisão\n", chave, pos);
            m->tabpos[pos].fim->prox = item;
            m->tabpos[pos].fim = item;

		    (m->ocupadas)++;
		}
		else{
		    /* elemento existe - atualizar valor */
		    colid_item->dados = dados;
		}
	}

    return m;
}

Hashtable* hashtable_retira(Hashtable* m, int chave)
{
    if (m==NULL) {
        printf("Erro na alocação! \n"); 
        exit(1);
    }

    int pos = hash(m, chave);


    
    if(m->tabpos[pos].ini == NULL){
        printf("\n Chave não existe \n");
    }
    else{
        
        Hashtable_item* a = NULL; /* ponteiro para Lista anterior */
        Hashtable_item* p = m->tabpos[pos].ini; /* ponteiro para percorrer a lista */
        
        /* procura Lista na lista, guardando anterior */
        while (p != NULL && p->chave != chave) {
            a = p;
            p = p->prox;
        }
        /* verifica se achou Lista */
        if (p == NULL){
            printf("\n Chave não existe \n");
            return m;
        }
        
        /* retira Lista */
        if (a == NULL){
            m->tabpos[pos].ini = p->prox; /* retira Lista do inicio */
        }
        else
            a->prox = p->prox;/* retira Lista do meio da lista */
        
        if (m->tabpos[pos].ini == NULL) /* verifica se fila ficou vazia */
            m->tabpos[pos].fim = NULL;
            
        free(p);
        
        (m->ocupadas)--;
    }
    
    return m;
} 


int hashtable_busca (Hashtable *m, int chave) {


    if (m==NULL) return -1;

    int pos = hash(m, chave);

    Hashtable_item *lista = m->tabpos[pos].ini;

    if(lista != NULL){
        Hashtable_item *item = lista_busca (lista, chave);
        if(item != NULL)
            return item->dados;
        else
            return -1;
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
        m->tabpos[i].ini = NULL;
        m->tabpos[i].fim = NULL;
    }

   /* e os elementos já inseridos na tabela anterior? */
    for (i=0; i < tamanterior; i++){
        if (anterior[i].ini != NULL){
            Hashtable_item* p = anterior[i].ini;
            Hashtable_item* t;
            while (p != NULL)
            {
                t = p->prox; /* guarda referência p/ próx. Lista */
                hashtable_insere (m, p->chave, p->dados);
                free(p); /* libera a memória apontada por p */
                p = t; /* faz p apontar para o próximo */
            }
        }
        anterior[i].ini = NULL;
        anterior[i].fim = NULL;
    }
    
    free (anterior);
}

void hashtable_exibir(Hashtable* m)
{
	int i;
	for (i = 0; i < m->tam; i++)
    {
		if (m->tabpos[i].ini == NULL)
        {
			printf("\n Pos[%d] não tem elementos \n", i);
		}
		else 
        {
			printf("\n Pos[%d] tem elementos -: \t",i);
			
			Hashtable_item *p;
            for (p = m->tabpos[i].ini; p != NULL; p = p-> prox)
            {
    			printf("chave(%d) valor(%d); ", p->chave, p->dados);
            }

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
    int i;
    
    for (i=0; i < m->tam; i++){
        if (m->tabpos[i].ini != NULL){
            Hashtable_item* p = m->tabpos[i].ini;
            Hashtable_item* t;
            while (p != NULL)
            {
                t = p->prox; /* guarda referência p/ próx. Lista */
                free(p); /* libera a memória apontada por p */
                p = t; /* faz p apontar para o próximo */
            }
        }
        m->tabpos[i].ini = NULL;
        m->tabpos[i].fim = NULL;
    }
  free (m->tabpos);
  free (m);
}