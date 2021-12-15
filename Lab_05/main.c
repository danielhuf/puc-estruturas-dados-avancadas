#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fila.h"

int main()
{
    Fila* filaPreparo = fila_cria();
    Fila* filaPronto = fila_cria();
    
    fila_insere(filaPreparo, 12332, "Lasanha");
    fila_insere(filaPreparo, 2321, "Bolo de chocolate");
    fila_insere(filaPreparo, 3762, "Macarrao com ovo");
    imprime_fila(filaPreparo);
    
    fila_passa(filaPreparo, filaPronto);
    fila_passa(filaPreparo, filaPronto);
    
    imprime_fila(filaPreparo);
    imprime_fila(filaPronto);

    fila_libera(filaPreparo);
    fila_libera(filaPronto);
    return 0;
}
