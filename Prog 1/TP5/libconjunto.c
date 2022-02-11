#include <stdlib.h>
#include <stdio.h>
#include "libconjunto.h"

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
*/
conjunto_t * cria_conjunto (int max)
{
  conjunto_t * conj = malloc(sizeof(conjunto_t));
  
  if (conj == NULL)
    return NULL;

  conj -> max = max;
  conj -> card = 0;
  conj -> v = malloc(max * sizeof(int));
  
  if (conj -> v == NULL)
    return NULL;
  
  return conj;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e faz com que ele aponte para NULL.
*/
void destroi_conjunto (conjunto_t *c)
{
  free(c -> v);
  c -> v = NULL;
  
  free(c);
  c = NULL;  
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
*/
int conjunto_vazio (conjunto_t *c)
{
  /* testa se a cardinalidade do conjunto é 0 */
  if (c -> card != 0)
    return 0;

  return 1;
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
*/
int cardinalidade (conjunto_t *c)
{
  return c -> card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida, 0 se tenta inserir elemento existente,
 * e retorna -1 em caso de falha por falta de espaco.
*/
int insere_conjunto (conjunto_t *c, int elemento)
{
  /* testa se o conjunto esta cheio */
  if (c -> card + 1 >= c -> max)
      return -1;

  /* testa se o elemento ja existe */
  if (pertence(elemento, c))
      return 0;

/* insere o elemento */
  if (c -> card == 0)
    c -> v[0] = elemento;
  else
    c -> v[c -> card] = elemento;

  /* ordena o conjunto */
  bubbleSort(c -> v, c -> card);

  /* incrementa a cardinalidade */
  c -> card+=1;

  return 1;
}

/*
 * Remove o elemento elemento do conjunto caso ele exista e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
*/
int retira_conjunto (conjunto_t *c, int elemento)
{
  /* testa se o elemento existe */
  if (!pertence(elemento,c))
    return 0;
  
  /* retira o elemento */
  int cont, i;
  for (cont = 0; cont < c -> card; cont++)
    if (elemento == c -> v[cont])
      for (i = cont; i < c -> card; i++)
        c -> v[i] = c -> v[i + 1];
  
  /* decrementa a cardinalidade */
  c -> card = c -> card - 1;

  return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
*/
int pertence (conjunto_t *c, int elemento)
{
  int cont;
  for(cont = 0; cont < c -> card; cont++) 
    if (elemento == c -> v[cont])
      return 1;

  return 0;
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
*/
int contido (conjunto_t *c1, conjunto_t *c2)
{
  if (c1 -> card == c2 -> card)
  {
    int cont;
    for (cont = 0; cont < c1 -> card; cont++)
      if (!pertence(c1 -> v[cont], c2))
        return 0;

    return 1;
  }
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
*/
int sao_iguais (conjunto_t *c1, conjunto_t *c2)
{
  if (c1 -> card == c2 -> card)
  {
    int cont;
    for (cont = 0; cont < c1 -> card; cont++)
      if (c1 -> v[cont] != c2 -> v[cont])
        return 0;

    return 1;
  }
}

/*
 * Retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2)
{
  conjunto_t *dif = cria_conjunto(c1 -> max);
  int cont;

  if (dif == NULL)
    return NULL;

  for (cont = 0; cont < c1 -> card; cont++)
    if (!pertence(c1 -> v[cont], c2))
      insere_conjunto(dif, c1 -> v[cont]);

  return dif;
}

/*
 * Retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2)
{
  conjunto_t *inter = cria_conjunto(c1 -> max);
  int cont;

  if (inter == NULL)
    return NULL;

  for (cont = 0; cont < c1 -> card; cont++)
    if (pertence(c1 -> v[cont], c2))
      insere_conjunto(inter, c1 -> v[cont]);

  return inter;
}

/*
 * Retorna o endereco do conjunto uniao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2)
{
  conjunto_t *uniao = cria_conjunto(c1 -> max);
  int cont;

  if (uniao == NULL)
    return NULL;

  for (cont = 0; cont < c1 -> card; cont++)
    insere_conjunto(uniao, c1 -> v[cont]);

  for (cont = 0; cont < c2 -> card; cont++)
    insere_conjunto(uniao, c2 -> v[cont]);

  return uniao;
}

/*
 * Retorna uma copia do conjunto c e 0 caso nao seja possivel.
*/
conjunto_t * cria_copia (conjunto_t *c)
{
  conjunto_t *copia = cria_conjunto(c -> max);
  int cont;

  if (copia == NULL)
    return 0;

  for (cont = 0; cont < c -> card; cont++)
    insere_conjunto(copia, c -> v[cont]);

  return copia;
}

/*
 * Cria um subconjunto de cardinalidade n com elementos aleatorios do conjunto c.
 * Retorna o conjunto em caso de sucesso e NULL caso contrario.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se o n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand() tenha sido chamada antes.
*/
conjunto_t * cria_subconjunto (conjunto_t *c, int n);

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
*/
void imprime (conjunto_t *c);

/*
 * Retorna 1 se conseguiu dobrar o tamanho max do conjunto e 0 caso contrario.
*/
int redimensiona (conjunto_t *c);

/*
 * As funcoes abaixo permitem acessar elementos apontados pelo ponteiro 'ptr'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
*/

/*
 * Inicializa o contador que sera usado na funcao incrementar_iterador 
*/
void iniciar_iterador (conjunto_t *c);

/*
 * Incrementa iterador e retorna o elemento apontado. Retorna 0 se acabou conjunto 
*/
int incrementar_iterador (conjunto_t *c, int *elemento);

/*
 * Escolhe um elemento qualquer do conjunto para ser removido e o remove.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
*/
int retirar_um_elemento (conjunto_t *c);
