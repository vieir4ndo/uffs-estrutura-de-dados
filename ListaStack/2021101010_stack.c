#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Browser {
  char site[60] ;
  struct Browser * prox;
} TBrowser;

typedef struct Pilha {
  TBrowser *top;
} TPilha;

void inicializa_pilha(TPilha *pilha)
{
  pilha->top = NULL;
}

void empurar(TPilha *pilha, char site[60])
{
  TBrowser *novo;
  novo = (TBrowser *)malloc(sizeof(TBrowser));
  strcpy(novo->site, site);
  novo->prox = NULL;

  if (pilha->top == NULL)
  {
    pilha->top = novo;
  }
  else 
  {
    novo->prox = pilha->top;
    pilha->top = novo;
  }
}

void imprimir_arrobas(TPilha *pilha)
{
  TBrowser *aux;
  aux = pilha->top;
  if (aux == NULL)
  {
    printf("!\n");
    return;
  }
  while(aux != NULL)
  {
     printf("@");
    aux = aux->prox;
  }
  printf("\n");
  return;
}

void imprimir_ultimo_pilha(TPilha *pilha)
{
  if (pilha->top != NULL){
    printf("%s\n", pilha->top->site);  
  }
}  

void estourar(TPilha *pilha)
{
  TBrowser *aux;
  if (pilha->top==NULL)
  {
     printf("Vazio\n");
  }
  else
  {
    aux = pilha->top;
    
    if (pilha->top->prox == NULL)
    {
      pilha->top = NULL;
    }
    else 
    {
      pilha->top = pilha->top->prox;
    }
  }
}

int main()
{
  TPilha *pilha;
  pilha = (TPilha *)malloc(sizeof(TPilha));

  inicializa_pilha(&pilha);

  char site[60];

  do {

    scanf("%s", &site);

    if (strcmp(site, "B") == 0)
    {
      imprimir_ultimo_pilha(&pilha);
      estourar(&pilha);
    }
    else if (strcmp(site, "E") != 0)
    {
      empurar(&pilha,site);
    }
  } while (strcmp(site, "E") != 0);
  
  imprimir_arrobas(&pilha);
  inicializa_pilha(&pilha);
}