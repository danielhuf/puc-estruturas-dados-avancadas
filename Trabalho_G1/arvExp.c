#include <stdio.h>
#include <stdlib.h>
#include "arvExp.h"
#include "pilha.h"

// Estrutura da arvore de expressão
struct arvExp {
	int tipo;
	int valor;
	char oper;
	struct arvExp* esq;
	struct arvExp* dir;
	struct arvExp* pai;
};

ArvExp* arv_criavazia (void) {
	return NULL;
}

int arv_vazia (ArvExp* a) {
	return (a == NULL);
}

int arv_valorEA(ArvExp* arv) {
	int i;
	
	if (arv_vazia(arv) || (arv->tipo != 0 && arv->tipo != 1))
		return 0;
		
	if (arv->tipo == 0)   // Operando
		return arv->valor;
		
	switch (arv->oper) {  // Operador
	    case '+':
		    return arv_valorEA(arv->esq) + arv_valorEA(arv->dir);
		    
	    case '-':
		    return arv_valorEA(arv->esq) - arv_valorEA(arv->dir);
		    
	    case '*':
		    return arv_valorEA(arv->esq) * arv_valorEA(arv->dir);
		    
	    case '/':
		    i = arv_valorEA(arv->dir);
		    if (i == 0) { printf("\n\nErro: Divisao por zero"); return 0;}
		    return arv_valorEA(arv->esq) / i;
		    
	    default:
		    printf("Operador invalido\n");
		    exit(2);
	}
}

ArvExp* arv_cria (void* info, char tipo) {
	ArvExp* p = (ArvExp*)malloc(sizeof(ArvExp));
	if (p == NULL) exit(1);
	p->esq = NULL;
	p->dir = NULL;
	p->pai = NULL;
	p->tipo = tipo;
	
	if (tipo == 0)                //info é valor int
		p->valor = *((int*)info);
	else                          //info é valor char
		p->oper = *((char*)info);
		
	return p;
}

ArvExp* arv_anexa (ArvExp* filho, ArvExp* atual) {
    
    // Procurando o pimeiro pai/avô operador que pode ter mais filhos e definindo-o como o nó atual
	while (atual->tipo == 0 || (atual->esq != NULL && atual->dir != NULL)) {
		atual = atual->pai;
	}
	
	if (atual->dir == NULL) {
		filho->pai = atual;
		atual->dir = filho;
	}
	
	else {
		filho->pai = atual;
		atual->esq = filho;
	}
	
	return atual;
}

void arv_imprime_aninhado (ArvExp* a) {
    
    // A impressão aninhada está sendo feita na ordem simétrica
	if (!arv_vazia(a)) {
		printf("(");
		arv_imprime_aninhado(a->esq);      /* mostra sae */
		if (a->tipo == 0)
			printf(" %d ", a->valor);
		else
			printf(" %c ", a->oper);
		arv_imprime_aninhado(a->dir);      /* mostra sad */
		printf(")");
	}
}

void arv_libera(ArvExp* a)
{
	if (!arv_vazia(a)) {
		arv_libera(a->esq);   /* libera sae */
		arv_libera(a->dir);   /* libera sad */
		free(a);              /* libera raiz */
	}
}