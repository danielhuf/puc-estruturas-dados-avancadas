#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#include "arvExp.h"
#define MAX 50

/*------------------------- PARTE 1: Shunting Yard para converter infix para postfix ----------------*/

int eh_alg (char c) {
	if (c >= '0' && c <= '9') return 1;
	return 0;
}

Pilha *string2infix (char *s) {
	Pilha *p = pilha_cria();
	char *i, *op;
	int *valor;
	
	// Percorre a string
	for (i = s; *i != '\0'; i++) {
	    
	    // Adiciona numero na pilha
		if (eh_alg(*i)) { 
			valor = (int*)malloc(sizeof(int));
			*valor = (int)(*i - '0');
			
			while (eh_alg(*(i + 1))) {
				i++;
				*valor = *valor * 10 + ((int)(*i - '0'));
			}
			
			pilha_push(p, 0, valor);
		}
		
		// Adiciona operador na pilha
		else if (*i != ' ') {  
			op = (char*)malloc(sizeof(char));
			
			if (*i == 'x')
				*op = '*';
			else
				*op = *i;
				
			pilha_push(p, 1, op);
		}
	}
	return p;
}

Pilha *infix2postfix (Pilha *p) {
	p = roda_vagao(p);
	Pilha *saida = pilha_cria(), *temp = pilha_cria();
	char tipo, tipot;
	void *inf, *inft;
	char x, y;
	
	while (!pilha_vazia(p)) {
		inf = pilha_pop(p, &tipo);
		
		if (tipo == 0) {  //Numeros vão direto para a pilha de saída
			pilha_push(saida, tipo, inf);
		}
		
		else {
			x = *((char*)inf);
			
			if (x == '(') {  //Abertura de parênteses vai para a pilha temporária
				pilha_push(temp, tipo, inf);
			}
			
			else if (x == ')') {  //Fechamento de parênteses
				free(inf);
				
				// Percorre a pilha temporária até encontrar a abertura de parênteses
				while (x != '(') {  
					inf = pilha_pop(temp, &tipo);
					x = *((char*)inf);
					
					if (x != '(') { //Passa operadores de temp para a saída
						pilha_push(saida, tipo, inf);
					}
					
					else {
							free(inf);
					}
				}
			}
			
			else { // x é operador
			    
				if (!pilha_vazia(temp)) {
					inft = pilha_le_topo(temp, &tipot);
					
					 // y é char no topo da pilha temp
					y = *((char*)inft);
						
					while (tipot == 1 && y != '(' && y != ')' &&	// Enquanto y é operador e
						!((x == '*' || x == '/') && (y == '+' || y == '-'))) {	// Precedência de x é menor ou igual a de y
						inft = pilha_pop(temp, &tipot);  // Pop y de temp
						pilha_push(saida, tipot, inft);  // Push y na saída
						
						if (!pilha_vazia(temp)) {
							inft = pilha_le_topo(temp, &tipot);
							y = *((char*)inft);
						}
						
						else
							tipot = 0; // Sair do loop se temp estiver vazia
					}
				}
				pilha_push(temp, tipo, inf);  // Push x na saída
			}
		}
	}
	
	// Enquanto houver operadores em temp, mover para a saída
	while (!pilha_vazia(temp)) { 
		inf = pilha_pop(temp, &tipo);
		pilha_push(saida, tipo, inf);
	}
	
	pilha_libera(temp);
	pilha_libera(p);
	return saida;
}

/*----------------------- PARTE 2: Criação da árvore de expressão através de postfix ----------------*/

ArvExp* postfix2ArvExp (Pilha *postfix) {
	ArvExp* raiz = arv_criavazia(), *novo_no, *atual;
	void* info;
	char tipo;
	
	//1. Pegando o ultimo simbolo a direita da notação postfix, criando um nó para ele, colocando na raiz
	info = pilha_pop(postfix, &tipo);
	raiz = arv_cria(info, tipo);
	
	//2. Definindo a raiz como no atual
	atual = raiz;
	
	while (!pilha_vazia(postfix)) {
		info = pilha_pop(postfix, &tipo);   //3. Para cada elemento da direita para a esquerda
		novo_no = arv_cria(info, tipo);     //3.1 Criando um nó
		atual = arv_anexa(novo_no, atual);  //3.2 e 3.3 Anexando o novo nó ao nó atual
		atual = novo_no;                    //3.4 Definindo o novo nó como nó atual
	}
	
	return raiz;
}


/*---------------------------------------------------------------------------------------------------*/

void executa (char* oper) {
    
    Pilha *p;
	ArvExp *a;
	int i;
	
    p = string2infix(oper);
	printf("\nNotacao infix: ");
	pilha_imprime_h(p);

	p = infix2postfix(p);
	printf("\nNotacao postfix: ");
	pilha_imprime_h(p);

	a = postfix2ArvExp(p);
	printf("\nArvore de expressao aninhada:\n");
	arv_imprime_aninhado(a);

	i = arv_valorEA(a);
	printf("\n\nResultado da expressao: %d\n", i);

	pilha_libera(p);
	arv_libera(a);
}

int main (void) {
    int i;
	char s[MAX], c, *expressoes[10] = {"3 + 2 x 3", "10 x 2 - 2 x 5", "7 + 3 / 2", "2 x 6 + 3 / 8",
	                                  "2 + (3 x (8 - 4))", "18 / 2 x 5 + 6 - 4",
	                                  "3 + (16 - 4 x 3) - 6 / 2", "(2 - 3 + 1) / (2 - 2)",
	                                  "((18 + 3 x 2) / 8 + 5 x 3) / 6", "16 / 4 x (4)"};
	
	printf("Deseja printar as expressões previamente avaliadas? (s/n)\n");
	scanf("%c", &c);
	if (c=='s') {
	    for (i=0; i<10; i++) {
	        printf("\n%d) %s\n", i+1, expressoes[i]);
	        executa(expressoes[i]);
	        printf("---------------------------------------------------------------\n");
	    }
	}
	
	printf("\nDeseja calcular alguma outra expressao? (s/n)\n");
	scanf(" %c", &c);
	
	while (c=='s') {
	    i = 0;
	    printf("\nDigite a expressao:\n");
	    c = getc(stdin);
    	c = getc(stdin);
    	while (c != '\n') {
    		s[i++] = c;
    		c = getc(stdin);
    	}
    	s[i] = '\0';
    	executa(s);
    	printf("\nDeseja calcular alguma outra expressao? (s/n)\n");
    	scanf(" %c", &c);
	}
	
	return 0;
}
