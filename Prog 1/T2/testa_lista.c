#include <stdio.h>
#include <stdlib.h>
#include "liblista.h"

void imprime_lista(lista_t *l)
{
    nodo_t *nodo = l->ini;
    while (nodo != NULL)
    {
        printf("%d ", nodo->elemento);
        nodo = nodo->prox;
    }
    printf("\n");
}

int main()
{
    lista_t *listaB, *listaC, *listaD, *listaE;
    int i;

    printf("\n Criando Listas\n");

    listaB = cria_lista();
    listaC = cria_lista();
    listaD = cria_lista();
    listaE = cria_lista();

    printf("\nTestando se a lista está vazia\n");

    if (lista_vazia(listaB))
        printf("Lista B está vazia\n");
    else
        printf("Lista B não está vazia\n");

    if (lista_vazia(listaC))
        printf("Lista C está vazia\n");
    else
        printf("Lista C não está vazia\n");

    if (lista_vazia(listaD))
        printf("Lista D está vazia\n");
    else
        printf("Lista D não está vazia\n");

    if (lista_vazia(listaE))
        printf("Lista E está vazia\n");
    else
        printf("Lista E não está vazia\n");

    printf("\n Inserindo elementos na lista B\n");
    for(i=1; i<10; i++)
    {
        insere_ordenado_lista(listaB, i);
    }

    printf("\n Inserindo elementos na lista C\n");

    for(i=10; i>=1; i--)
    {
        insere_ordenado_lista(listaC, i);
    }

    printf("\n Inserindo elementos na lista D\n");

    for(i=10; i<20; i++)
    {
        insere_ordenado_lista(listaD, i);
    }

    printf("\n Inserindo elementos na lista E\n");

    for(i=20; i>=10; i--)
    {
        insere_ordenado_lista(listaE, i);
    }

    printf("\n Imprimindo listas\n");

    imprime_lista(listaB);
    imprime_lista(listaC);
    imprime_lista(listaD);
    imprime_lista(listaE);

    printf("\nTesta se os elementos pertencem a lista\n");

    if(pertence_lista(listaB, 5))
        printf("\nO elemento 5 pertence a lista B\n");
    else
        printf("\nO elemento 5 nao pertence a lista B\n");

    if(pertence_lista(listaC, 15))
        printf("\nO elemento 15 pertence a lista C\n");
    else
        printf("\nO elemento 15 nao pertence a lista C\n");

    if(pertence_lista(listaD, 15))
        printf("\nO elemento 15 pertence a lista D\n");
    else
        printf("\nO elemento 15 nao pertence a lista D\n");

    if(pertence_lista(listaE, 5))
        printf("\nO elemento 5 pertence a lista E\n");
    else
        printf("\nO elemento 5 nao pertence a lista E\n");

    printf("\nInserindo elementos no início das listas\n");

    insere_inicio_lista(listaB, 15);
    insere_inicio_lista(listaC, 15);
    insere_inicio_lista(listaD, 5);
    insere_inicio_lista(listaE, 5);

    printf("\nImprimindo listas\n");

    imprime_lista(listaB);
    imprime_lista(listaC);
    imprime_lista(listaD);
    imprime_lista(listaE);

    printf("\nInserindo elementos no fim das listas\n");

    insere_fim_lista(listaB, 100);
    insere_fim_lista(listaC, 100);
    insere_fim_lista(listaD, 100);
    insere_fim_lista(listaE, 100);

    printf("\nImprimindo listas\n");

    imprime_lista(listaB);
    imprime_lista(listaC);
    imprime_lista(listaD);
    imprime_lista(listaE);

    printf("\nRetirando elementos do início da lista\n");

    retira_inicio_lista(listaB, &i);
    printf("%d\n", i);

    retira_inicio_lista(listaC, &i);
    printf("%d\n", i);

    retira_inicio_lista(listaD, &i);
    printf("%d\n", i);

    retira_inicio_lista(listaE, &i);
    printf("%d\n", i);

    printf("\nImprimindo listas\n");

    imprime_lista(listaB);
    imprime_lista(listaC);
    imprime_lista(listaD);
    imprime_lista(listaE);

    printf("\nRetirando elementos do fim da lista\n");

    retira_fim_lista(listaB, &i);
    printf("%d\n", i);
    retira_fim_lista(listaC, &i);
    printf("%d\n", i);
    retira_fim_lista(listaD, &i);
    printf("%d\n", i);
    retira_fim_lista(listaE, &i);
    printf("%d\n", i);

    printf("\nImprimindo listas\n");

    imprime_lista(listaB);
    imprime_lista(listaC);
    imprime_lista(listaD);
    imprime_lista(listaE);

    printf("\nRetirando elementos escolhidos\n");

    retira_elemento_lista(listaB, 5);
    retira_elemento_lista(listaC, 5);
    retira_elemento_lista(listaD, 15);
    retira_elemento_lista(listaE, 15);

    printf("\nImprimindo listas\n");

    imprime_lista(listaB);
    imprime_lista(listaC);
    imprime_lista(listaD);
    imprime_lista(listaE);

    printf("\nDestroi listas\n");

    listaB = destroi_lista(listaB);
    listaC = destroi_lista(listaC);
    listaD = destroi_lista(listaD);
    listaE = destroi_lista(listaE);

    return 0;
}