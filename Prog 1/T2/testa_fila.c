#include <stdio.h>
#include <stdlib.h>
#include "libfila.h"

void imprime_fila(fila_t *fila) 
{
    nodo_f_t *no = fila->ini;

    while (no != NULL) 
    {
        printf("%d ", no->chave);
        no = no->prox;
    }

    printf("\n");
}

int main() 
{
    fila_t *filaB, *filaC, *filaD, *filaE; 
    int i;

    printf("\nCriando Filas\n");

    filaB = cria_fila();
    filaC = cria_fila();
    filaD = cria_fila();
    filaE = cria_fila();

    printf("\nTesta se a fila está vazia\n");

    if (fila_vazia(filaB))
        printf("Fila B está vazia\n");
    else
        printf("Fila B não está vazia\n");

    printf("\n O tamanho da fila B é %d\n", tamanho_fila(filaB));

    if (fila_vazia(filaC))
        printf("\nFila C está vazia\n");
    else
        printf("\nFila C não está vazia\n");

    printf("\n O tamanho da fila C é %d\n", tamanho_fila(filaC));

    if (fila_vazia(filaD))
        printf("\nFila D está vazia\n");
    else
        printf("\nFila D não está vazia\n");

    printf("\n O tamanho da fila D é %d\n", tamanho_fila(filaD));
    
    if (fila_vazia(filaE))
        printf("\nFila E está vazia\n");
    else
        printf("\nFila E não está vazia\n");

    printf("\n O tamanho da fila E é %d\n", tamanho_fila(filaE));

    printf("\nInserindo elementos nas filas\n");

    for (i = 0; i <= 10; i++) 
    {
        insere_fila(filaB, i);
    }


    for (i = 10; i <= 20; i++) 
    {
        insere_fila(filaC, i);
    }


    for (i = 10; i >= 0; i--) 
    {
        insere_fila(filaD, i);
    }


    for (i = 20; i >= 10; i--) 
    {
        insere_fila(filaE, i);
    }

    printf("\nImprimindo filas\n");

    printf("\nFila B: ");
    imprime_fila(filaB);

    printf("\nFila C: ");

    imprime_fila(filaC);

    printf("\nFila D: ");

    imprime_fila(filaD);

    printf("\nFila E: ");

    imprime_fila(filaE);


    printf("\nTesta se a fila está vazia\n");

    if (fila_vazia(filaB))
        printf("Fila B está vazia\n");
    else
        printf("Fila B não está vazia\n");

    printf("\n O tamanho da fila B é %d\n", tamanho_fila(filaB));

    if (fila_vazia(filaC))
        printf("\nFila C está vazia\n");
    else
        printf("\nFila C não está vazia\n");

    printf("\n O tamanho da fila C é %d\n", tamanho_fila(filaC));

    if (fila_vazia(filaD))
        printf("\nFila D está vazia\n");
    else
        printf("\nFila D não está vazia\n");

    printf("\n O tamanho da fila D é %d\n", tamanho_fila(filaD));
    
    if (fila_vazia(filaE))
        printf("\nFila E está vazia\n");
    else
        printf("\nFila E não está vazia\n");

    printf("\n O tamanho da fila E é %d\n", tamanho_fila(filaE));

    printf("\nInserindo elementos nas filas\n");


    printf("\nRemovendo elementos das filas\n");

    for (i = 0; i <= 5; i++) 
    {
        retira_fila(filaB, &i);
    }


    for (i = 10; i <= 15; i++) 
    {
        retira_fila(filaC, &i);
    }

    for (i = 10; i >= 5; i--) 
    {
        retira_fila(filaD, &i);
    }

    for (i = 20; i >= 15; i--) 
    {
        retira_fila(filaE, &i);
    }

    printf("\nImprimindo filas\n");

    printf("\nFila B: ");
    imprime_fila(filaB);

    printf("\nFila C: ");

    imprime_fila(filaC);

    printf("\nFila D: ");

    imprime_fila(filaD);

    printf("\nFila E: ");

    imprime_fila(filaE);

    printf("\nTesta as funções de ponteiros\n");

    inicializa_atual_fila(filaB);
    inicializa_atual_fila(filaC);
    inicializa_atual_fila(filaD);
    inicializa_atual_fila(filaE);

    printf("\nImprime o ponteiro atual\n");

    consulta_atual_fila(filaB, &i);
    printf("\nFila B: %d\n", i);

    consulta_atual_fila(filaC, &i);
    printf("\nFila C: %d\n", i);

    consulta_atual_fila(filaD, &i);
    printf("\nFila D: %d\n", i);

    consulta_atual_fila(filaE, &i);
    printf("\nFila E: %d\n", i);

    printf("\nIncrementa o ponteiro\n");

    incrementa_atual_fila(filaB);
    incrementa_atual_fila(filaC);
    incrementa_atual_fila(filaD);
    incrementa_atual_fila(filaE);

    printf("\nImprime o ponteiro atual\n");

    consulta_atual_fila(filaB, &i);
    printf("\nFila B: %d\n", i);

    consulta_atual_fila(filaC, &i);
    printf("\nFila C: %d\n", i);

    consulta_atual_fila(filaD, &i);
    printf("\nFila D: %d\n", i);

    consulta_atual_fila(filaE, &i);
    printf("\nFila E: %d\n", i);

    printf("\nRetira o elemento que está sendo apontado\n");

    retira_atual_fila(filaB, &i);
    retira_atual_fila(filaC, &i);
    retira_atual_fila(filaD, &i);
    retira_atual_fila(filaE, &i);

    printf("\nImprime as filas\n");

    printf("\nFila B: ");
    imprime_fila(filaB);

    printf("\nFila C: ");
    imprime_fila(filaC);

    printf("\nFila D: ");
    imprime_fila(filaD);

    printf("\nFila E: ");
    imprime_fila(filaE);

    printf("\n Destruindo filas\n");

    destroi_fila(filaB);
    destroi_fila(filaC);
    destroi_fila(filaD);
    destroi_fila(filaE);

    return 0;
}