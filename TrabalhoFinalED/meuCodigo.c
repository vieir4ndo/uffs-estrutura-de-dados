#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void clear_screen()
{
	system("clear");
}

void apresenta_menu()
{
	printf("MENU DE GERENCIAMENTO DA BODEGA:\n");
	printf("1 - Cadastrar bebida\n");
	printf("2 - Listar bebidas\n");
	printf("3 - Buscar bebida\n");
	printf("4 - Excluir bebida\n");
	printf("5 - Comprar bebida\n");
	printf("6 - Vender bebida\n");
	printf("7 - Sair do sistema\n");
}

void press_to_continue()
{
	printf("Pressione enter para voltar ao menu principal.");
	getchar();
	getchar();
	clear_screen();
	apresenta_menu();
}

typedef struct Bebida
{
	int codigo;
	char nome[30];
	int volume;
	float preco;
	int quantidade_estoque;
	int ehAlcoolica;
	struct Bebida *prox, *ant;
}

TBebida;

typedef struct Lista
{
	TBebida * inicio;
	TBebida * fim;
}

TLista;

void inicializa_lista(TLista *lista)
{
	lista->inicio = NULL;
	lista->fim = NULL;
}

TBebida* ler_bebida()
{
	TBebida * novo;
	novo = (TBebida*) malloc(sizeof(TBebida));
	printf("Informe o código:");
	scanf("%d", &novo->codigo);

	printf("Informe o nome:");
	scanf("%s", &novo->nome);

	printf("Informe o volume em mL:");
	scanf("%d", &novo->volume);

	printf("Informe o preço em R$:");
	scanf("%f", &novo->preco);

	printf("Informe a quantidade em estoque:");
	scanf("%d", &novo->quantidade_estoque);

	printf("Caso a bebida seja alcoolica digite 1, se não for digite 0:");
	scanf("%d", &novo->ehAlcoolica);

	return novo;
}

int inserir_elemento(TLista *lista)
{
	clear_screen();
	TBebida *novo, *aux = lista->inicio;
	novo = (TBebida*) malloc(sizeof(TBebida));
	bool naoSalva = false;

	novo = ler_bebida();
	clear_screen();

	if (lista->inicio == NULL)
	{
		novo->ant = NULL;
		novo->prox = NULL;
		lista->inicio = novo;
		lista->fim = novo;
		printf("Bebida cadastrada com sucesso!\n\n");
	}
	else
	{
		while (aux != NULL)
		{
			if (aux->codigo == novo->codigo)
			{
				naoSalva = true;
				break;
			}

			aux = aux->prox;
		}

		if (!naoSalva)
		{
			novo->prox = NULL;
			novo->ant = lista->fim;
			lista->fim->prox = novo;
			lista->fim = novo;
			printf("Bebida cadastrada com sucesso!\n\n");
		}
		else
		{
			printf("Bebida não cadastrada!\n");
			printf("Já existe bebida com o mesmo código.\n\n");
		}
	}

	press_to_continue();
}

void imprime_bebida(TBebida *aux)
{
	printf("Códgio: %d \n", aux->codigo);
	printf("Nome: %s \n", aux->nome);
	printf("Volume: %d \n", aux->volume);
	printf("Preço: %f \n", aux->preco);
	printf("Qnt. Disponível: %d \n", aux->quantidade_estoque);
	printf("Alcoólica (1/s,0/n): %d\n", aux->ehAlcoolica);
}

void apresentar_elementos(TLista *lista)
{
	TBebida * aux;
	aux = lista->inicio;

	if (aux == NULL)
	{
		clear_screen();
		printf("Não há bebidas cadastradas!\n\n");
	}
	else
	{
		clear_screen();
		printf("Lista de Bebidas\n\n");

		while (aux != NULL)
		{
			imprime_bebida(aux);
			printf("\n");
			aux = aux->prox;
		}
	}

	press_to_continue();
}

void apresentar_elemento(TLista *lista)
{
	TBebida *aux, *imprimeEssa;
	bool vaiImprimir = false;
	aux = lista->inicio;
	int codigo;

	clear_screen();
	printf("Informe o código:");
	scanf("%d", &codigo);

	if (aux == NULL)
	{
		clear_screen();
		printf("Não há bebidas cadastradas!\n\n");
	}
	else
	{
		while (aux != NULL)
		{
			if (aux->codigo == codigo)
			{
				imprimeEssa = aux;
				vaiImprimir = true;
			}

			aux = aux->prox;
		}

		clear_screen();

		if (vaiImprimir)
		{
			imprime_bebida(imprimeEssa);
			printf("\n");
		}
		else
		{
			printf("Bebida não cadastrada!\n\n");
		}
	}

	press_to_continue();
}

void excluir_elemento(TLista *lista)
{
	TBebida *anterior, *atual;
	int codigo;
	bool excluiu = false;

	clear_screen();
	printf("Informe o código:");
	scanf("%d", &codigo);
	clear_screen();

	if (lista->inicio == NULL)
	{
		printf("Não há bebidas cadastradas!\n\n");
	}
	else
	{
		anterior = lista->inicio;
		atual = lista->inicio;

		while (atual != NULL)
		{
			if (atual->codigo == codigo)
			{
				if (lista->inicio == atual)
					lista->inicio = atual->prox;

				if (atual->prox != NULL)
					atual->prox->ant = atual->ant;

				if (atual->ant != NULL)
					atual->ant->prox = atual->prox;

				printf("Bebida excluída com sucesso!\n\n");
				excluiu = true;
			}

			anterior = atual;
			atual = atual->prox;
		}

		if (!excluiu)
		{
			printf("Bebida não excluída!\n");
			printf("Não existe bebida com esse código!\n\n");
		}
	}

	press_to_continue();
}

void comprar_bebida(TLista *lista)
{
	TBebida *anterior, *atual;
	int codigo, quantidade;

	clear_screen();
	printf("Informe o código:");
	scanf("%d", &codigo);
	printf("Informe a quantidade:");
	scanf("%d", &quantidade);
	clear_screen();

	if (lista->inicio == NULL)
	{
		printf("Não há bebidas cadastradas!\n\n");
	}
	else
	{
		anterior = lista->inicio;
		atual = lista->inicio;
		bool comprou = false;

		while (atual != NULL)
		{
			if (atual->codigo == codigo)
			{
				comprou = true;
				atual->quantidade_estoque += quantidade;
			}

			anterior = atual;
			atual = atual->prox;
		}

		if (comprou)
			printf("Bebida comprada com sucesso!\n\n");
		else
		{
			printf("Bebida não comprada!\n");
			printf("Não existe bebida com esse código.\n\n");
		}
	}

	press_to_continue();
}

void vender_bebida(TLista *lista)
{
	TBebida *anterior, *atual;
	int codigo, quantidade, idade;
	bool vendeu = false;

	clear_screen();
	printf("Informe o código:");
	scanf("%d", &codigo);
	printf("Informe a quantidade:");
	scanf("%d", &quantidade);
	printf("Informe a idade:");
	scanf("%d", &idade);
	clear_screen();

	if (lista->inicio == NULL)
	{
		printf("Não há bebidas cadastradas para venda!\n\n");
	}
	else
	{
		anterior = lista->inicio;
		atual = lista->inicio;

		while (atual != NULL)
		{
			if (atual->codigo == codigo)
			{
				if (atual->quantidade_estoque >= quantidade)
				{
					if (atual->ehAlcoolica == 1)
					{
						if (idade < 18)
						{
							clear_screen();
							printf("Compra não realizada!\n");
							printf("Você não pode comprar bebida alcoolica, pois é menor de idade!\n\n");
							break;
						}
					}

					atual->quantidade_estoque -= quantidade;
					vendeu = true;
					printf("Compra realizada com sucesso!\n\n");
				}
				else
				{
					printf("Compra não realizada!\n");
					printf("Não há bebidas suficiente em estoque!\n\n");
				}
			}

			anterior = atual;
			atual = atual->prox;
		}

		if (!vendeu)
		{
			printf("Compra não realizada!\n");
			printf("Não há bebida cadastrada com esse códido!\n\n");
		}
	}

	press_to_continue();
}

int main(void)
{
	TLista L1;

	inicializa_lista(&L1);

	int opcao = 1;

	clear_screen();

	apresenta_menu();

	do {
		scanf("%d", &opcao);

		switch (opcao)
		{
			case 1:
				inserir_elemento(&L1);
				break;
			case 2:
				apresentar_elementos(&L1);
				break;
			case 3:
				apresentar_elemento(&L1);
				break;
			case 4:
				excluir_elemento(&L1);
				break;
			case 5:
				comprar_bebida(&L1);
				break;
			case 6:
				vender_bebida(&L1);
				break;
			default:
				return 0;
		}
	} while (opcao != 7);
}