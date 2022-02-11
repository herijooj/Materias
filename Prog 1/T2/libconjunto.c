#include <stdlib.h>
#include <stdio.h>
#include "libconjunto.h"

/* Funcoes adicionais */

/* busca binaria */ 
/* retorna o indice do elemento ou -1 se nao existir */
int busca_binaria(int x, conjunto_t *c) 
{
  int inicio = 0, fim = c->card - 1, meio;

  while (inicio <= fim) 
  {
    meio = (inicio + fim) / 2;

    if (c->v[meio] == x)
      return meio;
    else if (c->v[meio] < x)
      inicio = meio + 1;
    else
      fim = meio - 1;
  }

  return -1;
}

/* insere ordenado */
void insere_ordenado(int elemento, conjunto_t *c)
{
  int i = c->card;

  while (i > 0 && elemento < c->v[i - 1])
  {
    c->v[i] = c->v[i - 1];
    i--;
  }

  c->v[i] = elemento;
  c->card++;
}

/* remove ordenado */
void remove_ordenado(int elemento, conjunto_t *c)
{
  int i = busca_binaria(elemento, c);

  if (i != -1)
  {
    while (i < c->card - 1)
    {
      c->v[i] = c->v[i + 1];
      i++;
    }
    
    c->card--;
  }
}

/* ------------------ */

/*
 * Cria um conjunto vazio e o retorna, se falhar retorna NULL.
 * max eh o tamanho maximo do conjunto, isto eh, o tamanho maximo do vetor
*/
conjunto_t * cria_conjunto (int max)
{
  conjunto_t *c;

  /* aloca memoria para o conjunto */
  if (!(c = malloc(sizeof(conjunto_t))))
    return NULL;

  /* aloca memoria para o vetor */
  if (!(c->v = malloc(max * sizeof(int))))
  {
    free(c);
    return NULL;
  }

  /* inicializa o conjunto */
  c->card = 0;
  c->max = max;

  return c;
}

/*
 * Remove todos os elementos do conjunto, libera espaco e devolve NULL.
*/
conjunto_t * destroi_conjunto (conjunto_t *c)
{
  free(c->v);
  free(c);

  return NULL;
}

/*
 * Retorna 1 se o conjunto esta vazio e 0 caso contrario.
*/
int conjunto_vazio (conjunto_t *c)
{
  return (c->card == 0);
}

/*
 * Retorna a cardinalidade do conjunto, isto eh, o numero de elementos presentes nele.
*/
int cardinalidade (conjunto_t *c)
{
  return c->card;
}

/*
 * Insere o elemento no conjunto, garante que nao existam repeticoes.
 * Retorna 1 se a operacao foi bem sucedida, 0 se tenta inserir elemento existente,
 * e retorna -1 em caso de falha por falta de espaco.
*/
int insere_conjunto (conjunto_t *c, int elemento)
{
  /* checa se o elemento existe */
  if (busca_binaria(elemento, c) != -1)
    return 0;

  /* checa se o conjunto esta cheio */
  if (c->card == c->max)
    return -1;

  /* insere o elemento ordenado */
  insere_ordenado(elemento, c);
    return 1;
}

/*
 * Remove o elemento elemento do conjunto caso ele exista e o retorna.
 * Retorna 1 se a operacao foi bem sucedida e 0 se o elemento nao existe.
*/
int retira_conjunto (conjunto_t *c, int elemento)
{
  /* checa se o elemento existe */
  int i = busca_binaria(elemento, c);

  /* se nao existe, retorna 0 */
  if (i == -1)
    return 0;

  /* remove o elemento ordenado */
  while (i < c->card - 1)
  {
    c->v[i] = c->v[i + 1];
    i++;
  }

  /* decrementa a cardinalidade */
  c->card--;

  return 1;
}

/*
 * Retorna 1 se o elemento pertence ao conjunto e 0 caso contrario.
*/
int pertence (conjunto_t *c, int elemento)
{
  return (busca_binaria(elemento, c) != -1);
}

/*
 * Retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario.
*/
int contido (conjunto_t *c1, conjunto_t *c2)
{
  int i;

  /* checa se a cardinalidade do conjunto c1 eh maior que o do conjunto c2 */
  if (c1->card > c2->card)
    return 0;

  /* percorre o conjunto c1 */
  for (i = 0; i < c1->card; i++)
    if (busca_binaria(c1->v[i], c2) == -1)
      return 0;

  return 1;
}

/*
 * Retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario.
*/
int sao_iguais (conjunto_t *c1, conjunto_t *c2)
{
  int i;

  /* checa se a cardinalidade dos conjuntos sao iguais */
  if (c1->card != c2->card)
    return 0;

  /* percorre os conjuntos */
  for (i = 0; i < c1->card; i++)
    if (c1->v[i] != c2->v[i])
      return 0;
  return 1;
}

/*
 * Retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem.
 * Retorna 0 se a operacao falhou.
*/
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2)
{
  int i;

  conjunto_t *c_diferenca;

  /* cria um conjunto vazio */
  if (!(c_diferenca = cria_conjunto(c1->max)))
    return NULL;

  /* checa se o elemento não existe no outro conjunto e o insere */
  for (i = 0; i < c1->card; i++)
    if (busca_binaria(c1->v[i], c2) == -1)
      insere_conjunto(c_diferenca, c1->v[i]);

  return c_diferenca;
}

/*
 * Retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2.
 * Retorna 0 se a operacao falhou.
*/
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2)
{
  int i;

  conjunto_t *c_intersecao;

  /* cria um conjunto vazio */
  if (!(c_intersecao = cria_conjunto(c1->max)))
    return NULL;

  /* checa se o elemento existe no outro conjunto e o insere */
  for (i = 0; i < c1->card; i++)
    if (busca_binaria(c1->v[i], c2) != -1)
      insere_conjunto(c_intersecao, c1->v[i]);

  return c_intersecao;
}

/*
 * Retorna o endereco do conjunto uniao entre os conjuntos c1 e c2.
 * Retorna NULL se a operacao falhou.
*/
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2)
{
  int i;

  conjunto_t *c_uniao;

  /* cria um conjunto vazio */
  if (!(c_uniao = cria_conjunto(c1->max)))
    return NULL;

  /* insere os elementos do conjunto c1 */
  for (i = 0; i < c1->card; i++)
    insere_conjunto(c_uniao, c1->v[i]);

  /* insere os elementos do conjunto c2 */
  for (i = 0; i < c2->card; i++)
    insere_conjunto(c_uniao, c2->v[i]);

  return c_uniao;
}

/*
 * Retorna uma copia do conjunto c e 0 caso nao seja possivel.
*/
conjunto_t * cria_copia (conjunto_t *c)
{
  int i;

  conjunto_t *c_copia;

  /* cria um conjunto vazio */
  if ( !(c_copia = cria_conjunto(c->max)) )
    return 0;

  /* insere os elementos do conjunto c */
  for (i = 0; i < c->card; i++)
    insere_conjunto(c_copia, c->v[i]);

  return c_copia;
}

/*
 * Cria um subconjunto com elementos aleatorios do conjunto c.
 * Se o conjunto for vazio, retorna um subconjunto vazio.
 * Se o n >= cardinalidade (c) entao retorna o proprio conjunto c.
 * Supoe que a funcao srand () tenha sido chamada antes.
*/
conjunto_t * cria_subconjunto (conjunto_t *c, int n)
{
  int i;

  /* testa se o conjunto é vazio */
  if (c->card == 0)
    return cria_conjunto(c->max);

  /* testa se o n é maior que a cardinalidade do conjunto */
  if (n >= c->card)
    return cria_copia(c);

  conjunto_t *c_sub;

  /* cria um conjunto vazio */
  if (!(c_sub = cria_conjunto(c->max)))
    return NULL;

  /* insere n elementos aleatorios do conjunto c */
  for (i = 0; i < n; i++)
  {
    int r = rand() % c->card;
    insere_conjunto(c_sub, c->v[r]);
  }

  return c_sub;
}

/*
 * Imprime os elementos do conjunto sempre em ordem crescente,
 * mesmo que a estrutura interna nao garanta isso.
*/
void imprime (conjunto_t *c)
{
  int i;
  for (i = 0; i < c->card; i++)
    printf("%d ", c->v[i]);
  printf("\n");
}

/*
 * Retorna 1 se conseguiu dobrar o tamanho max do conjunto e 0 caso contrario.
*/
int redimensiona (conjunto_t *c)
{
  int * aux;

  /* realoca o vetor */
  if (!(aux = realloc(c->v, sizeof(int)*(c->max+1)*2)))
    return 0;
  
  /* atualiza o vetor */
  c->v = aux;
  c->max = c->max*2;
  return 1;
}

/*
 * As funcoes abaixo permitem acessar elementos apontados pelo ponteiro 'ptr'.
 * Este ponteiro pode ser inicializado e incrementado, viabilizando
 * a implementacao de um mecanismo iterador.
*/

/*
 * Inicializa o contador que sera usado na funcao incrementar_iterador 
*/
void iniciar_iterador (conjunto_t *c)
{
  c->ptr = -1;
}

/*
 * Incrementa iterador e retorna o elemento apontado. Retorna 0 se acabou conjunto 
*/
int incrementar_iterador (conjunto_t *c, int *elemento)
{
  /* testa se o iterador esta no final do conjunto */
  if (c->ptr == c->card - 1)
    return 0;

  /* incrementa o iterador */
  c->ptr++;
  *elemento = c->v[c->ptr];

  return *elemento;
}

/*
 * Escolhe um elemento qualquer do conjunto para ser removido e o remove.
 * Nao faz teste se conjunto eh vazio, deixa para main fazer isso       
*/
int retirar_um_elemento (conjunto_t *c)
{
  return retira_conjunto(c, c->v[rand() % c->card]);
}
