#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "grafo.h"
#include "largura.h"
#include "profundidade.h"
#include "dijkstra.h"
#include "A.h"
#include "prim.h"
#include "kruskal.h"

#define NUM_V 3280	/* quantidade de vértices: 82*40=3280 */
#define NUM_COL 82

int main(void) {
	int i, custo, v_inicio, v_final, custoDikstra, custoA, custoPrim, custoKruskal, custoLargura, custoProfundidade;

	Grafo *g = grafo_cria(NUM_V);

	FILE *arqMap = fopen("maze_lab_grafos_T03.txt", "rt");

	char c = fgetc(arqMap);
	i = 0;
	while (!feof(arqMap)) { /* lê arquivo e cria o grafo */
		if (c != '\n') {
			grafo_insere_info_vertice(g, i, c);
			if (c == 'M')
				custo = 100;
			else if (c == 'R')
				custo = 5;
			else if (c == '.')
				custo = 1;
			else {
				if (c == 'I')
					v_inicio = i;
				else if (c == 'F')
					v_final = i;
				else {
					printf("Caractere inválido\n");
					exit(1);
				}
				custo = 0;
			}

			if (i - NUM_COL >= 0)	    	/* i não está na borda superior do mapa*/
				grafo_insere_aresta(g, i - NUM_COL, i, custo);

			if (i + NUM_COL < NUM_V)	    /* i não está na borda inferior do mapa*/
				grafo_insere_aresta(g, i + NUM_COL, i, custo);

			if (i % NUM_COL != 0)	     	/* i não está na lateral esquerda do mapa */
				grafo_insere_aresta(g, i - 1, i, custo);

			if ((i + 1) % NUM_COL != 0)	    /* i não está na lateral direita do mapa */
				grafo_insere_aresta(g, i + 1, i, custo);

			i++;
		}
		c = fgetc(arqMap);
	}
	fclose(arqMap);

	grafo_imprime(g, NUM_COL);

	printf("\n\n------------------------------- BUSCA EM LARGURA ---------------------------------\n");
	int *larg, contLarg;

	clock_t t1 = clock();       // momento inicial
	larg = buscaLargura(g, v_inicio, v_final, &contLarg);
	t1 = clock() - t1;          // momento final

	printf("Caminho encontrado:\n");
	custoLargura = mostra_prev(g, larg, v_final, NUM_COL);
	free(larg);

	printf("\n\n----------------------------- BUSCA EM PROFUNDIDADE ------------------------------\n");
	int *prof, contProf;

	clock_t t2 = clock();
	prof = buscaProfundidade(g, v_inicio, v_final, &contProf);
	t2 = clock() - t2;

	printf("Caminho encontrado:\n");
	custoProfundidade = mostra_prev(g, prof, v_final, NUM_COL);
	free(prof);

	printf("\n\n----------------------------------- DIJKSTRA -------------------------------------\n");
	int *dij, contDij;

	clock_t t3 = clock();
	dij = Dijkstra(g, v_inicio, &contDij);
	t3 = clock() - t3;

	printf("Caminho de menor custo encontrado:\n");
	custoDikstra = mostra_prev(g, dij, v_final, NUM_COL);

    printf("\n\nOutra visualização do menor caminho:\n");
    mostra_prev2(g, dij, v_final, NUM_COL);

    free(dij);

	printf("\n\n-------------------------------------- A* ----------------------------------------\n");
	int *Aestrela, contA;

    printf("Vértices acessados no algoritmo");
	clock_t t4 = clock();
	Aestrela = A(g, v_inicio, v_final, NUM_COL, &contA);
	t4 = clock() - t4;

    printf("Caminho de menor custo encontrado:\n");
	custoA = mostra_prev(g, Aestrela, v_final, NUM_COL);
	free(Aestrela);

	printf("\n\n----------------------------------- KRUSKAL --------------------------------------\n");
	Aresta *krus;

	clock_t t5 = clock();
	krus = kruskal(g);
	t5 = clock() - t5;

    printf("Árvore geradora mínima encontrada:\n");
	custoKruskal = imprime_arv(krus, g, NUM_COL);
	free(krus);

	printf("\n------------------------------------ PRIM ----------------------------------------\n");
	Aresta *arvprim;

	clock_t t6 = clock();
	arvprim = prim(g);
	t6 = clock() - t6;

    printf("Árvore geradora mínima encontrada:\n");
	custoPrim = imprime_arv(arvprim, g, NUM_COL);
	free(arvprim);


	printf("\n----------------------------------- RESULTADOS -----------------------------------\n\n");

	printf("Busca em largura\n");
    printf("Qtd de vertices visitados: %d\n", contLarg);
	printf("Custo total: %d\n", custoLargura);
	printf("Tempo de execucao: %f segundos\n\n", ((double)t1) / CLOCKS_PER_SEC);

	printf("Busca em profundidade\n");
    printf("Qtd de vertices visitados: %d\n", contProf);
	printf("Custo total: %d\n", custoProfundidade);
	printf("Tempo de execucao: %f segundos\n\n", ((double)t2) / CLOCKS_PER_SEC);

	printf("Dijkstra\n");
	printf("Custo total: %d\n", custoDikstra);
	printf("Qtd de vertices visitados: %d\n", contDij);
	printf("Tempo de execucao: %f segundos\n\n", ((double)t3) / CLOCKS_PER_SEC);

	printf("A*\n");
	printf("Custo total: %d\n", custoA);
	printf("Qtd de vertices visitados: %d\n", contA);
	printf("Tempo de execucao: %f segundos\n\n", ((double)t4) / CLOCKS_PER_SEC);

	printf("Prim\n");
	printf("Custo total: %d\n", custoPrim);
	printf("Tempo de execucao: %f segundos\n\n", ((double)t5) / CLOCKS_PER_SEC);

	printf("Kruskal\n");
	printf("Custo total: %d\n", custoKruskal);
	printf("Tempo de execucao: %f segundos\n\n", ((double)t6) / CLOCKS_PER_SEC);

	grafo_destroi(g);
	return 0;
}