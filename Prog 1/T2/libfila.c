#include <stdlib.h>
#include <stdio.h>
#include "libfila.h"

/*
 * Cria uma fila vazia e a retorna, se falhar retorna NULL.
*/
fila_t * cria_fila ()
{
    fila_t *fila;

    /* Aloca memoria para a fila */
    if (!(fila = (fila_t *) malloc(sizeof(fila_t))))
        return NULL;

    /* Inicializa a fila */
    fila->tamanho = 0;
    fila->ini = NULL;
    fila->atual = NULL;
    fila->fim = NULL;

    return fila;
}

/*
 * Remove todos os elementos da fila, libera espaco e devolve NULL.
*/
fila_t * destroi_fila (fila_t *f)
{
    nodo_f_t *aux;

    /* Se a fila esta vazia, retorna NULL */
    if (fila_vazia(f))
    {
        free(f);
        return NULL;
    }

    /* Libera todos os elementos da fila */
    while (f->ini != NULL)
    {
        aux = f->ini;
        f->ini = f->ini->prox;
        free(aux);
    }

    /* Libera a fila */
    f-> tamanho--;
    free(f);

    return NULL;
}

/*
 * Retorna 1 se a fila esta vazia e 0 caso contrario.
*/
int fila_vazia (fila_t *f)
{
    return f->tamanho == 0;
}

/*
 * Retorna o tamanho da fila, isto eh, o numero de elementos presentes nela.
*/
int tamanho_fila (fila_t *f)
{
    return f->tamanho;
}

/*
 * Insere o elemento no final da fila (politica FIFO).
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int insere_fila (fila_t *f, int elemento)
{
    nodo_f_t *novo;

    /* Aloca memoria para o novo nodo */
    if (!(novo = (nodo_f_t *) malloc(sizeof(nodo_f_t))))
        return 0;

    /* Inicializa o novo nodo */
    novo->chave = elemento;
    novo->prox = NULL;

    /* Se a fila esta vazia, insere o novo nodo como inicio*/
    if (fila_vazia(f))
        f->ini = novo;
    else
        f->fim->prox = novo;

    f->fim = novo;
    f->tamanho++;

    return 1;
}

/*
 * Remove o elemento do inicio da fila (politica FIFO) e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 caso contrario.
*/
int retira_fila (fila_t *f, int *elemento)
{
    nodo_f_t *aux;

    /* Se a fila esta vazia, retorna 0 */
    if (fila_vazia(f))
        return 0;

    /* Retorna o elemento do inicio da fila */
    *elemento = f->ini->chave;
    aux = f->ini;
    f->ini = f->ini->prox;

    /* Se a fila ficou vazia, atualiza o fim */
    if (fila_vazia(f))
        f->fim = NULL;

    /* Libera o nodo */
    free(aux);
    f->tamanho--;

    return 1;
}

/*
 * Inicializa o ponteiro atual para o primeiro elemento da fila.
 * Retorna 1 se a operacao foi bem sucedida e zero caso contrario.
*/
int inicializa_atual_fila (fila_t *f)
{
    /* Se a fila esta nula, retorna 0 */
    if (f == NULL)
        return 0;

    /* se a fila esta vazia, retorna 0 */
    if (fila_vazia(f))
        return 0;

    /* Inicializa o atual para o inicio da fila */
    f->atual = f->ini;

    return 1;
}

/*
 * Faz o ponteiro atual apontar para o próximo nodo da fila f e retorna 
 * este ponteiro. Se atual estiver apontando para o último, isto eh, nao 
 * tem proximo, retorna NULL.
*/
void incrementa_atual_fila (fila_t *f)
{
    if (fila_vazia (f))
        return;

    if (f->atual->prox == NULL)
        return;

    f->atual = f->atual->prox;
}

/*
 * Retorna em *elemento o valor contido na chave apontada pelo ponteiro atual. 
 * Se atual não for válido a função retorna zero senão retorna 1.
*/
int consulta_atual_fila (fila_t *atual, int *elemento)
{
    if (fila_vazia(atual))
        return 0;

    if (atual->atual == NULL)
        return 0;

    *elemento = atual->atual->chave;

    return 1;
}

/*
 * Remove o elemento apontado por atual da fila f e o retorna em *elemento.
 * Faz o atual apontar para o sucessor do nodo removido.
 * Retorna 1 se houve sucesso e zero caso contrario.
*/
int retira_atual_fila (fila_t *f, int *elemento)
{
    nodo_f_t *nodo;

    /* Se a fila esta vazia, retorna 0 */
    if (fila_vazia(f))
        return 0;

    /* Se atual nao for valido, retorna 0 */
    if (f->atual == NULL)
        return 0;

    /* Se atual for o ultimo elemento, faz o fim apontar para NULL */
    nodo = f->atual;

    if (f->atual == f->ini)
    {
        f->ini = f->ini->prox;
        if (f->ini == NULL)
            f->fim = NULL;
    }
    else
    {
        nodo_f_t *aux = f->ini;
        while (aux->prox != f->atual)
            aux = aux->prox;
        aux->prox = f->atual->prox;
        if (aux->prox == NULL)
            f->fim = aux;
    }

    /* Atualiza o atual */
    f->atual = f->atual->prox;
    *elemento = nodo->chave;
    free(nodo);
    f->tamanho--;

    return 1;
}
