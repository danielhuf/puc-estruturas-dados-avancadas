#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

int main()
{
    Elemento* lista = lista_cria();
    Elemento* lista_aux = lista_cria();
    
    if (lista_vazia(lista))
        printf("A lista está inicialmente vazia\n\n");
    
    lista = lista_insere_ordenado(lista, 444, "Luiz", "rua A", "984376854");
    lista = lista_insere_ordenado(lista, 111, "Rute", "rua B", "989452763");
    lista = lista_insere_ordenado(lista, 999, "Rita", "avenida C", "939845735");
    lista_imprime(lista);
    
    lista = lista_atualiza(lista, "Rita", "Marcia");
    lista = lista_retira(lista, "Luiz");
    lista_imprime(lista);
    
    lista_aux = lista_insere_ordenado(lista_aux, 8888, "Miguel", "rua K", "934633820");
    printf("%d", lista_igual(lista, lista_aux));
    
    lista_libera(lista);
     lista_libera(lista_aux);
    return 0;
}
