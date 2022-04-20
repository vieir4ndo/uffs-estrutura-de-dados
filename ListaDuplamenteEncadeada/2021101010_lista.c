#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Aluno {
  char matricula[10] ;
  char nome[40];
  struct Data * dataNascimento;
  float media;
  struct Aluno * prox;
  struct Aluno * ant;
} TAluno;

typedef struct Lista {
  TAluno *inicio;
  TAluno *fim;
} TLista;

typedef struct Data {
 int dia;
 int mes;
 int ano;
} TData;

void inicializa_lista(TLista *lista)
{
  lista->inicio = NULL;
  lista->fim = NULL;
}

int inserir_elemento(TLista *lista)
{
  TAluno *novo, *aux = lista->inicio;
  novo = (TAluno *)malloc(sizeof(TAluno));
  novo->dataNascimento = (TData *)malloc(sizeof(TData));

  char matriculaAnterior[10];

  scanf("%s\n", &matriculaAnterior);
  scanf("%s\n", &novo->matricula);
  scanf("%s\n", &novo->nome);
  scanf("%d/%d/%d\n", &novo->dataNascimento->dia, &novo->dataNascimento->mes, &novo->dataNascimento->ano);
  scanf("%f\n", &novo->media);

  if (lista->inicio == NULL)
  {
    novo->ant = NULL;
    novo->prox = NULL;
    lista->inicio = novo;
    lista->fim = novo;
  } 
  else if (strcmp(lista->inicio->matricula, matriculaAnterior) == 0 ) 
  {
    novo->ant = lista->inicio;
    novo->prox = lista->inicio->prox;
    lista->inicio->prox = novo;
  }
  else
  {
    while (aux != NULL)
    {
      if (strcmp(aux->matricula, matriculaAnterior) == 0)
      {
        break;
      }
      aux = aux->prox;
    }

    if (aux != NULL)
    {
      novo->ant = aux;
      novo->prox = aux->prox;
      aux->prox = novo;
    }
    else
    {
      novo->ant = NULL;
      novo->prox = lista->inicio;
      lista->inicio->ant = novo;
      lista->inicio = novo;
    }
  }
}

void apresentar_elementos(TLista *lista)
{
  TAluno *aux;
  aux = lista->inicio;

  if (aux == NULL)
    printf("Lista Vazia!\n");
  else 
  {
    while (aux != NULL)
    {
      printf("%s, %s, %d/%d/%d, %.2f\n", aux->matricula, aux->nome, aux->dataNascimento->dia, aux->dataNascimento->mes, aux->dataNascimento->ano, aux->media);
      aux = aux->prox;
    }
  }
}

void imprimir_elementos_inverso(TAluno *aux)
{
    if(aux == NULL)
        return;
    imprimir_elementos_inverso(aux->prox);
    printf("%s, %s, %d/%d/%d, %.2f\n", aux->matricula, aux->nome, aux->dataNascimento->dia, aux->dataNascimento->mes, aux->dataNascimento->ano, aux->media);
}  

void apresentar_elementos_inverso(TLista *lista)
{
   if (lista->inicio == NULL)
    printf("Lista Vazia!\n");
  else 
    imprimir_elementos_inverso(lista->inicio);
}

void excluir_elemento(TLista *lista)
{
  TAluno *anterior, *atual;
  char matricula[10];
  
  scanf("\n%s", &matricula);

  if (lista->inicio == NULL)
    printf("Lista Vazia!\n");
  else
  {
    anterior = lista->inicio;
    atual = lista->inicio;

    while (atual != NULL)
    {
      if (strcmp(atual->matricula, matricula) == 0)
      {
        if (lista->inicio == atual)
          lista->inicio = atual->prox;
 
        if (atual->prox != NULL)
          atual->prox->ant = atual->ant;
 
        if (atual->ant != NULL)
          atual->ant->prox = atual->prox;
      }
      anterior = atual;
      atual = atual->prox;
    }
  }
}

void conta_elementos(TLista *lista)
{
  TAluno *aux;
  aux = lista->inicio;
  int contador = 0;

  while (aux != NULL)
  {
     contador++;
     aux = aux->prox;
  }

  printf("%d\n", contador);
}

void apresentar_hifens(TLista * lista)
{
  TAluno *aux;
  aux = lista->inicio;
  int elementos = 0;

  while (aux != NULL)
  {
     elementos++;
     aux = aux->prox;
  }

  for (int i = 0; i<elementos; i++)
  {
    printf("*");
  }
  printf("\n\n");
}

int main(void) {
 
  TLista L1;

  inicializa_lista(&L1);

  int opcao = 1;

  do {
	  scanf("%d", &opcao);

    switch (opcao) {
      case 1:
			  inserir_elemento(&L1);
        break;
      case 2:
        excluir_elemento(&L1);
        break;
      case 3:
        apresentar_elementos(&L1);
        break;
      case 4:
        apresentar_elementos_inverso(&L1);
        break;
      case 5:
        conta_elementos(&L1);
        break;
      case 0:
        apresentar_hifens(&L1);
        return 0;        
    }
  } while(1);
}
