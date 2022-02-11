#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liblef.h"

/* 
 * Cria uma LEF vazia 
*/
lef_t * cria_lef ()
{
    lef_t * lef;
    if (!(lef = (lef_t *) malloc (sizeof(lef_t))))
        return NULL;
    
    lef->Primeiro = NULL;

    return lef;
}

/* 
 * Destroi a LEF, sempre retorna NULL. 
 * Note que nao eh possivel desalocar estruturas dentro de evento->dados se existirem 
*/ 
lef_t * destroi_lef (lef_t *l)
{
    nodo_lef_t *aux;

    if (l ->Primeiro == NULL)
        free(l);
    
    return NULL;

    while (l->Primeiro != NULL)
    {
        aux = l->Primeiro;
        l->Primeiro = l->Primeiro->prox;
        free(aux);
    }

    free(l);
    return NULL;
}

/* 
 * Adiciona um evento na primeira posicao da LEF. Uma nova copia
 * da estrutura evento sera feita .
*/ 
int adiciona_inicio_lef (lef_t *l, evento_t *evento)
{
    evento_t *novo;
    nodo_lef_t *novo_nodo;

    if (!(novo = (evento_t *) malloc (sizeof(evento_t))))
        return 0;

    novo -> dados = malloc(evento -> tamanho);
    memcpy(novo -> dados, evento -> dados, evento -> tamanho);
    novo -> tamanho = evento -> tamanho;
    novo -> tempo = evento -> tempo;
    novo -> tipo = evento -> tipo;

    if (!(novo_nodo = (nodo_lef_t *) malloc (sizeof(nodo_lef_t))))
        return 0;
    
    novo_nodo -> evento = novo;
    novo_nodo -> prox = l->Primeiro;
    l->Primeiro = novo_nodo;

    return 1;
}

/* 
 * Adiciona um evento de acordo com o valor evento->tempo na LEF. 
 * Uma nova copia da estrutura evento sera feita 
*/
void adiciona_ordem_lef  (lef_t *l, evento_t *evento)
{
    nodo_lef_t *novo_nodo;
    nodo_lef_t *aux;
    evento_t *novo;

    if (!(novo = (evento_t *) malloc (sizeof(evento_t))))
        return;

    novo -> dados = malloc(evento -> tamanho);
    memcpy(novo -> dados, evento -> dados, evento -> tamanho);
    novo -> tamanho = evento -> tamanho;
    novo -> tempo = evento -> tempo;
    novo -> tipo = evento -> tipo;

    if (!(novo_nodo = (nodo_lef_t *) malloc (sizeof(nodo_lef_t))))
        return;

    novo_nodo -> evento = novo;

    if (l->Primeiro == NULL)
    {
        novo_nodo -> prox = NULL;
        l->Primeiro = novo_nodo;
        return;
    }

    if (l->Primeiro->evento->tempo > evento->tempo)
    {
        novo_nodo -> prox = l->Primeiro;
        l->Primeiro = novo_nodo;
        return;
    }

    aux = l->Primeiro;
    while (aux->prox != NULL && aux->prox->evento->tempo < evento->tempo)
        aux = aux->prox;

    novo_nodo -> prox = aux->prox;
    aux->prox = novo_nodo;
}

/* 
 * Retorna o primeiro evento da LEF. A responsabilidade por desalocar
 * a memoria associado eh de quem chama a funcao 
*/
evento_t * obtem_primeiro_lef (lef_t *l)
{
    nodo_lef_t *aux;
    evento_t *evento;

    if (l->Primeiro == NULL)
        return NULL;

    aux = l->Primeiro;
    l->Primeiro = l->Primeiro->prox;
    evento = aux->evento;
    free(aux);

    return evento;
}