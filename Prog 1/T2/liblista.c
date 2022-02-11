#include <stdlib.h>
#include <stdio.h>
#include "liblista.h"

/* insere elemento na lista vazia */
int insere_lista_vazia(lista_t *l, int elemento)
{
    nodo_t *novo;
    
    /* aloca memoria para o novo nodo */
    if (!(novo = (nodo_t *) malloc(sizeof(nodo_t))))
        return 0;

    /* inicializa o novo nodo */
    novo->elemento = elemento;
    novo->prox = NULL;
    l->ini = novo;
    l->fim = novo;
    l->tamanho++;

    return 1;
}

/*
 * Cria uma lista vazia e a retorna, se falhar retorna NULL.
*/
lista_t * cria_lista () 
{
    lista_t * lista;

    /* Aloca memoria para a lista */
    if (!(lista = (lista_t *) malloc(sizeof(lista_t))))
        return NULL;
    
    /* Inicializa a lista */
    lista->tamanho = 0;

    return lista;
}

lista_t * destroi_lista (lista_t *l)
{
    /* Se a lista esta vazia, retorna NULL */
    if (lista_vazia(l)) 
    {
        free(l);
        return NULL;
    }

    nodo_t *nodo = l->ini;
    nodo_t *aux;

    /* Libera todos os elementos da lista */
    while (nodo != NULL)
    {
        aux = nodo->prox;
        free(nodo);
        nodo = aux;
    }

    free(l);
    return NULL;
}

/*
 * Retorna 1 se a lista esta vazia e 0 caso contrario.
*/
int lista_vazia (lista_t *l)
{
  return (l->tamanho == 0);
}

/*
 * Retorna o tamanho da lista, isto eh, o numero de elementos presentes nela.
*/
int tamanho_lista (lista_t *l)
{
  return l->tamanho;
}

/*
 * Insere o elemento no inicio da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_inicio_lista (lista_t *l, int elemento)
{  
    nodo_t *novo;

    /* Aloca memoria para o novo nodo */
    if (!(novo = (nodo_t *) malloc(sizeof(nodo_t))))
        return 0;

    /* Inicializa o novo nodo */
    novo->elemento = elemento;
    novo->prox = l->ini;
    l->ini = novo;

    /* Se a lista esta vazia, insere o novo nodo como fim */
    if (l->tamanho == 0)
        l->fim = novo;

    l->tamanho++;

    return 1;
}

/*
 * Insere o elemento no final da lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_fim_lista (lista_t *l, int elemento)
{
    nodo_t *novo;

    /* Aloca memoria para o novo nodo */
    if (!(novo = (nodo_t *) malloc(sizeof(nodo_t))))
        return 0;

    /* Inicializa o novo nodo */
    novo->elemento = elemento;
    novo->prox = NULL;

    /* Se a lista esta vazia, insere o novo nodo como inicio */
    if (l->tamanho == 0)
    {
        l->ini = novo;
        l->fim = novo;
    }
    else
    {
        /* Insere o novo nodo no fim da lista */
        l->fim->prox = novo;
        l->fim = novo;
    }

    l->tamanho++;

    return 1;
}

/*
 * Insere o elemento na lista garantindo ordenacao em ordem crescente.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_ordenado_lista (lista_t *l, int elemento)
{
    nodo_t *novo;
    nodo_t *aux;

    /* Aloca memoria para o novo nodo */
    if (!(novo = (nodo_t *) malloc(sizeof(nodo_t))))
        return 0;

    /* Inicializa o novo nodo */
    novo->elemento = elemento;
    novo->prox = NULL;

    /* Se a lista esta vazia, insere o novo nodo como inicio */
    if (l->tamanho == 0)
    {
        l->ini = novo;
        l->fim = novo;
        l->tamanho++;
        return 1;
    }

    /* se o elemento for menor que o primeiro elemento, insere no inicio */
    if (l->ini->elemento > elemento)
    {
        novo->prox = l->ini;
        l->ini = novo;
        l->tamanho++;
        return 1;
    }
    else
    {
        /* se o elemento for maior que o ultimo elemento, insere no fim */
        l->fim->prox = novo;
        l->fim = novo;
        l->tamanho++;
        return 1;
    }

    aux = l->ini;

    /* procura o nodo anterior ao elemento a ser inserido */
    while (aux->prox != NULL && aux->prox->elemento < elemento)
        aux = aux->prox;

    if (aux == l->ini)
    {
        free(novo);
        insere_inicio_lista(l, elemento);
        return 1;
    }

    if (aux->prox == NULL)
    {
        l->fim->prox = novo;
        l->fim = novo;
    }
    else
    {
        novo->prox = aux->prox;
        aux->prox = novo;
    }

    l->tamanho++;

    return 1;
}

/*
 * Remove o elemento do inicio da lista e o retorna em 'elemento'.
 * Retorna o elemento.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_inicio_lista (lista_t *l, int *elemento)
{
    nodo_t * aux;

    /* Se a lista esta vazia, retorna 0 */
    if (l->tamanho == 0)
        return 0;

    /* Retorna o elemento do inicio da lista */
    aux = l->ini;
    l->ini = l->ini->prox;

    /* Se a lista ficou vazia, atualiza o fim */
    if (l->tamanho == 1)
        l->fim = NULL;

    /* Libera a memoria do nodo removido */
    *elemento = aux->elemento;
    free(aux);
    l->tamanho--;

    return 1;
}

/*
 * Remove o elemento do final da lista e o retorna em 'elemento'.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_fim_lista (lista_t *l, int *elemento)
{
    nodo_t * aux;

    /* Se a lista esta vazia, retorna 0 */
    if (l->tamanho == 0)
        return 0;

    aux = l->ini;

    /* Se a lista tem apenas um elemento, retira o elemento do inicio */
    if (l->tamanho == 1)
    {
        *elemento = aux->elemento;
        free(aux);
        l->ini = NULL;
        l->fim = NULL;
    }
    else /* Se a lista tem mais de um elemento */
    {
        /* Procura o nodo anterior ao fim da lista */
        while (aux->prox != l->fim)
            aux = aux->prox;

        *elemento = l->fim->elemento;
        free(l->fim);
        l->fim = aux;
        l->fim->prox = NULL;
    }

    l->tamanho--;

    return 1;
}

/*
 * Remove o elemento 'elemento' caso ele exista na lista.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
 * Se o elemento nao for encontrado na lista tambem retorna 0.
*/
int retira_elemento_lista (lista_t *l, int elemento)
{
    nodo_t * aux = l->ini;
    nodo_t * ant = NULL;

    /* Se a lista esta vazia, retorna 0 */
    if (l->tamanho == 0)
        return 0;

    while (aux != NULL && aux->elemento != elemento)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
        return 0;

    if (ant == NULL)
        l->ini = l->ini->prox;
    else
        ant->prox = aux->prox;

    if (aux == l->fim)
        l->fim = ant;

    free(aux);
    l->tamanho--;

    return 1;
}

/*
 * Retorna 1 se o elemento existe na lista e 0 caso contrario.
*/
int pertence_lista (lista_t *l, int elemento)
{
    nodo_t * aux = l->ini;

    while (aux != NULL && aux->elemento != elemento)
        aux = aux->prox;

    return (aux != NULL);
}