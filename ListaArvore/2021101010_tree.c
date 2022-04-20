#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Noh {
    char key;
    struct Noh *esquerda;
    struct Noh *direita;
} Noh;

Noh *reconstruir_arvore(char preordemEst[], int raizIndex, int *qtdNos) {
    Noh *raiz;
    int qtdNosSubarv;

    if (raizIndex < 0) {
        return NULL;
    }

    raiz = malloc(sizeof(Noh));
    raiz->key = preordemEst[raizIndex];
    raiz->esquerda = NULL;
    raiz->direita = NULL;

    *qtdNos = 1;

    if (preordemEst[raizIndex + 1] != '0') {
        raiz->esquerda = reconstruir_arvore(preordemEst, raizIndex + 3, &qtdNosSubarv);
        *qtdNos += qtdNosSubarv;
    }

    if (preordemEst[raizIndex + 2] != '0') {
        raiz->direita = reconstruir_arvore(preordemEst, raizIndex + (*qtdNos * 3), &qtdNosSubarv);
        *qtdNos += qtdNosSubarv;
    }

    return raiz;
}

void mostrar_arvore_inordem(Noh *raiz)
{
	if (raiz!=NULL) 
	{
    mostrar_arvore_inordem(raiz->esquerda);
    printf("%c", raiz->key);
    mostrar_arvore_inordem(raiz->direita);
  }
}

void mostrar_arvore_posordem(Noh *raiz)
{
	if (raiz!=NULL) 
	{
    mostrar_arvore_posordem(raiz->esquerda);
	  mostrar_arvore_posordem(raiz->direita);
	  printf("%c", raiz->key);
  }
}

void limpar_arvore(Noh *n)
{
	if (n==NULL) return;
	limpar_arvore(n->esquerda);
	limpar_arvore(n->direita);
  printf("0");
  free(n);
}

int main() {
    int qtdNos;
    int tamPreordemEst;
    char *preordemEst = NULL;
    Noh *raiz;

    scanf("%d", &qtdNos);

    tamPreordemEst = qtdNos * 3;
    preordemEst = malloc((tamPreordemEst + 1) * sizeof(char));

    scanf("\n");
    fgets(preordemEst, tamPreordemEst + 1, stdin);
    preordemEst[strcspn(preordemEst, "\n")] = '\0';

    if (qtdNos > 0) {
        raiz = reconstruir_arvore(preordemEst, 0, &qtdNos);
        mostrar_arvore_inordem(raiz);
        printf("\n");
        mostrar_arvore_posordem(raiz);
        printf("\n");
    }
    else {
        raiz = NULL;
    }

    limpar_arvore(raiz);
    printf("\n");
    return 0;
}

