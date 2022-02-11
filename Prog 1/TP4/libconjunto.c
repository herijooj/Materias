#include <stdlib.h>
#include <stdio.h>
#include "libconjunto.h"

/* ----- funções adicionais ----- */

/* busca binaria */
int busca_binaria(int *v, int n, int x) {
    int inicio = 0, fim = n-1, meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (v[meio] == x) return meio;
        else if (v[meio] < x) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

/* insere ordenado */
int insere_ordenado(int *v, int n, int x) {
    int i = 0;
    while (i < n && v[i] < x) i++;
    if (i == n) return -1;
    else {
        int j = n;
        while (j > i) {
            v[j] = v[j-1];
            j--;
        }
        v[i] = x;
        return i;
    }
}

/* ----- funções do trabalho ----- */

/* cria um conjunto e retorna seu endereço se a operacao foi bem sucedida e 0 caso contrario */
/* o tamanho máximo do conjunto eh max */
conjunto_t * cria_conjunto (int max) 
{
  conjunto_t * conj = malloc(sizeof(conjunto_t));
  
  if (conj == NULL)
    return 0;

  conj -> max = max;
  conj -> card = 0;
  conj -> v = malloc(max * sizeof(int));
  
  if (conj -> v == NULL)
    return 0;
  
  return conj;
}

/* retorna 1 se o elemento n pertence ao conjunto c e 0 caso contrario   */
int pertence (int n, conjunto_t *c)
{
  return (busca_binaria(c -> v, c -> card, n) != -1);
}

/* destroi o conjunto c liberando todo espaco previamente alocado a este conjunto */
void destroi_conjunto (conjunto_t *c)
{
  free(c -> v);
  c -> v = NULL;
  
  free(c);
  c = NULL;  
}

/* insere o elemento n no conjunto c caso ele nao exista                     */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se tente inserir     */
/* elemento ja existente (conjuntos nao tem repeticao) e -1 se nao ha espaco */
int insere (int n, conjunto_t *c)
{
  /* testa se o conjunto esta cheio */
  if (c -> card + 1 >= c -> max)
      return -1;
  
  /* testa se o elemento ja existe */
  if (pertence(n, c))
      return 0;
  
  /* insere o elemento */
  insere_ordenado(c -> v, c -> card, n);
  
  /* incrementa a cardinalidade */
  c -> card+=1;

  return 1;
}

/* retira o elemento n do conjunto c caso ele exista */
/* retorna 1 se a operacao foi bem sucedida e retorna 0 se nao existe  */
int retira (int n, conjunto_t *c)
{
  /* testa se o elemento existe */
  if (!pertence(n,c))
    return 0;
  
  /* retira o elemento */
  int i = busca_binaria(c -> v, c -> card, n);
  int j;
  
  for (j = i; j < c -> card - 1; j++)
    c -> v[j] = c -> v[j+1];
  
  /* decrementa a cardinalidade */
  c -> card = c -> card - 1;

  return 1;
}

/* imprime os elementos do conjunto sempre em ordem crescente */
/* mesmo que a estrutura interna nao garanta isso             */
void imprime (conjunto_t *c)
{
  /* ordena o conjunto */


  /* imprime os elementos */
  int cont;
  for(cont = 0; cont < c -> card; cont++)
    printf("%d ", c -> v[cont]);
  
  printf("\n");
}

/* retorna 1 se o conjunto c1 esta contido no conjunto c2 e 0 caso contrario */
int contido (conjunto_t *c1, conjunto_t *c2)
{
  /* testa se o conjunto c1 é maior que o c2 */
  if (c1 -> card > c2 -> card)
    return 0;

  /* testa se o conjunto c1 é igual ao c2 */
  int cont;
  for (cont = 0; cont < c1 -> card; cont++)
    if (busca_binaria(c2 -> v, c2 -> card, c1 -> v[cont]) == -1)
      return 0;

  return 1;
}

/* retorna 1 se o conjunto c1 eh igual ao conjunto c2 e 0 caso contrario */
int sao_iguais (conjunto_t *c1, conjunto_t *c2)
{
  /* testa se as cardinalidades dos conjuntos são iguais */
  if (c1 -> card != c2 -> card) 
    return 0;

  /* testa se os conjuntos são iguais */
  int cont;
  for(cont = 0; cont < c1 -> card; cont++)
    if (c1 -> v[cont] != c2 -> v[cont])
      return 0;

  return 1;
}

/* retorna a cardinalidade do conjunto c */
int cardinalidade (conjunto_t *c)
{
  return c -> card;
}

/* retorna 1 se o conjunto c eh vazio e 0 caso contrario   */
int eh_vazio (conjunto_t *c)
{
  /* testa se a cardinalidade do conjunto é 0 */
  return c->card == 0;
}

/* retorna o endereco do conjunto uniao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                   */
conjunto_t * cria_uniao (conjunto_t *c1, conjunto_t *c2)
{
  /* cria um conjunto união */
  conjunto_t * uniao = cria_conjunto(c1 -> max + c2 -> max);

  /* testa se o conjunto união foi criado */
  if (uniao == NULL)
    return 0;
  
  /* insere os elementos do conjunto c1 no conjunto união */
  int cont;
  for (cont = 0; cont < c1 -> card; cont++)
    insere(c1 -> v[cont], uniao);
  
  /* insere os elementos do conjunto c2 no conjunto união */
  for (cont = 0; cont < c2 -> card; cont++)
    insere(c2 -> v[cont], uniao);
  
  return uniao;
}

/* retorna o endereco do conjunto interseccao entre os conjuntos c1 e c2  */
/* retorna 0 se a operacao falhou                                         */
conjunto_t * cria_interseccao (conjunto_t *c1, conjunto_t *c2)
{
  /* cria um conjunto interseccao */
  conjunto_t * interseccao = cria_conjunto(c1 -> max + c2 -> max);

  /* testa se o conjunto interseccao foi criado */
  if (interseccao == NULL)
    return 0;
  
  /* checa se os elementos de c1 pertencem ao conjunto c2 e os insere no conjunto interseccao */
  int cont;
  for (cont = 0; cont < c1 -> card; cont++)
    if (pertence(c1 -> v[cont], c2))
      insere(c1 -> v[cont], interseccao);
  
  return interseccao;
}

/* retorna o endereco do conjunto diferenca entre c1 e c2, nesta ordem  */
/* retorna 0 se a operacao falhou                                       */
conjunto_t * cria_diferenca (conjunto_t *c1, conjunto_t *c2)
{
  /* cria um conjunto diferença */
  conjunto_t * diferenca = cria_conjunto(c1 -> max + c2 -> max);

  /* testa se o conjunto diferença foi criado */
  if (diferenca == NULL)
    return 0;
  
  /* checa se os elementos de c1 não pertencem ao conjunto c2 e os insere no conjunto diferença */
  int cont;
  for (cont = 0; cont < c1 -> card; cont++)
    if (!pertence(c1 -> v[cont], c2))
      insere(c1 -> v[cont], diferenca);
  
  return diferenca;
}