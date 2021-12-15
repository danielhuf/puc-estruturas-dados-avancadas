#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#define DISCOS 3

int inicializar (Pilha* pino1, int discos)
{
    int i, resp;
    for (i=discos; i>0; i--) {
        resp = pilha_push(pino1, i);
        if (resp==0)
            return 0;
    }
    return 1;
}

void terminar (Pilha* pino1, Pilha* pino2, Pilha* pino3)
{
    printf("Liberando os pinos...\n");
    pilha_libera(pino1);
    pilha_libera(pino2);
    pilha_libera(pino3);
}

int mover (Pilha* origem, Pilha* destino)
{
    int disco = pilha_peek(origem);
    if (disco != 0 && (pilha_vazia(destino) || disco < pilha_peek(destino))) {
        disco = pilha_pop(origem);
        int resp = pilha_push(destino, disco);
        return 1;
    }
    printf("Movimento inválido!\n");
    return 0;
}

void mostrarPinos (Pilha* pino1, Pilha* pino2, Pilha* pino3)
{
    imprime_pilha(pino1, "pino1");
    imprime_pilha(pino2, "pino2");
    imprime_pilha(pino3, "pino3");
}

int main()
{
    printf("Inicializando os pinos...\n");
    Pilha* pino1 = pilha_cria();
    Pilha* pino2 = pilha_cria();
    Pilha* pino3 = pilha_cria();
    
    int ini = inicializar(pino1, DISCOS);
    int tam = tamanho_pilha(pino3);
    int origem, destino, mov;
    Pilha* pino_Origem;
    Pilha* pino_Destino;
    while (tam != DISCOS) {
        printf("Escolha o numero do pino de origem:");
        scanf("%d", &origem);
        pino_Origem = seleciona(origem, pino1, pino2, pino3);
        printf("Escolha o numero do pino de destino:");
        scanf("%d", &destino);
        pino_Destino = seleciona(destino, pino1, pino2, pino3);
        mov = mover(pino_Origem, pino_Destino);
        mostrarPinos(pino1, pino2, pino3);
        tam = tamanho_pilha(pino3);
    }
    
    printf("PARABÉNS! Você venceu o desafio da Torre de Hanói!\n");
    terminar(pino1, pino2, pino3);
    return 0;
}
