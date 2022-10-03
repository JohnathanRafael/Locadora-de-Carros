#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<locale.h>
#include<ctype.h>

#define T 50

typedef char String[T];
int IdL=0, IdF=0, IdP=0; // controla os ids 
/*--------------struct Fila do Cliente------------*/
typedef struct Fila{
	int id;
	String nome;
	// colocar mais coisas para inserir um cliente 
	Fila *prox;
	Fila *ant;
}Fila;

/*------------struct pilha de Carros-------------------*/
typedef struct Cel{
	int id;
	String carro;
	// colocar mais coisas para inserir um carro
	Cel *prox;
}Pilha;

/*------------struct Lista de Modelos-------------------*/
typedef struct Celula{
	int id;
	String nome;
	Pilha *carros;
	Pilha *listalocados;
	Fila *clientes;
	struct Celula *prox;
}Tipos;

// inicia estruturas 
void inicia_Lista(Tipos *f){
	f->prox = NULL;
}

void inicia_L(Pilha *f){
	f->prox = NULL;
}

/*------------testa estruturas vazias------------------*/
int fila_vazia(Fila *le)
{
	if(le->prox == le)
	{
		return 1;
	}else{
		return 0;
	}
}
int pilha_vazia(Pilha *tp){
	if(tp->prox == NULL){
		return 1;
	}else{
		return 0;
	}
}
int modelos_vazio(Tipos *tp){
	if(tp->prox == NULL){
		return 1;
	}else{
		return 0;
	}
}

/*------------ inserir dados ------------------*/
void insere_Modelos(Tipos *Modelo, String nome, int id)
{
	Tipos *Nova;
	
	Nova = (Tipos*) malloc(sizeof(Tipos));
	strcpy(Nova->nome, nome);
	Nova->id = id;
	
	Nova->carros = (Pilha*) malloc(sizeof(Pilha));
	Nova->carros->prox = NULL;
	
	Nova->clientes = (Fila*) malloc(sizeof(Fila));
	Nova->clientes->prox = Nova->clientes;
	Nova->clientes->ant = Nova->clientes;
	
	Nova->listalocados = (Pilha*) malloc(sizeof(Pilha));
	Nova->listalocados->prox = NULL;
	
	Nova->prox = Modelo->prox;
	Modelo->prox = Nova;
}

void enfileira(Fila *Modelo, String Nome, int id)
{
	Fila *Nova, *P;
	Nova = (Fila*) malloc (sizeof(Fila));
	strcpy(Nova->nome, Nome);
	Nova->id = id;
	
	if(Modelo->prox == Modelo)
	{
		printf("%s", Nova->nome);
		P = Modelo;
		Nova->prox = P->prox;
		P->prox = Nova;
		Nova->ant = P->ant;
		P->ant = Nova;
	}
	else
	{
		printf("%s", Nova->nome);
		P = Modelo->prox;
		Nova->prox = P;
		P->ant = Nova;
		Nova->ant = Modelo;
		Modelo->prox = Nova;
	}
}

void empilha(Pilha *tp, String Carro, int id){
	Pilha *novo = (Pilha*) malloc(sizeof(Pilha));
	strcpy(novo->carro, Carro);
	novo->id = id;
	novo->prox = tp->prox;
	tp->prox = novo;
}

/*------------ remove dados ------------------*/

Fila* desenfileira(Fila *Modelo) // retorna uma celula pois sao dois dados a serem informados, essa celula sendo apaga posteriormente
{
	Fila *P, *Retorna;
	P = Modelo->ant;
	Modelo->ant = P->ant;
	P->ant->prox = Modelo;
	Retorna = P;
	return Retorna;
}

Pilha* desempilha(Pilha *tp){
	Pilha *aux, *retorna;
	aux = tp->prox;
	tp->prox = aux->prox;
	retorna = aux;
	return retorna;
}

void* fura_Pilha (Pilha *Principal, Pilha *Lista)
{
	Pilha *X, *P;
	
	P = Principal;
	X = desempilha(P);
	X->prox = NULL;
	X->prox = Lista->prox;
	Lista->prox = X;
}

volta_estacionar(Pilha *Cars, Pilha *LCars, int Procura)
{
	Pilha *P, *U;
	U = LCars;
	P = LCars->prox;
	while(P != NULL && P->id != Procura)
	{
		U = P;
		P = P->prox;
	}
	if(P == NULL)
	{
		printf("ID não encontrado!!!\n");
	}
	else
	{
		U->prox = P->prox;
		P->prox = NULL;
		empilha(Cars, P->carro, P->id);
		printf("Inserido no estacionamento \n");
	}
}

/*------------ apresenta os dados ------------------*/

void imprime_pilha(Pilha *tp){
	system("clear||cls");
	if(pilha_vazia(tp)){
		printf("\n------------------------------------------\n");
		printf("Não existe carros na pilha.");
		printf("\n------------------------------------------\n");
	}else{
		Pilha *aux = tp->prox;
		printf("\n-----------------------------------------------\n");
		printf("                Carros para Alugar.");
		printf("\n-----------------------------------------------\n");
		while(aux != NULL){
			printf(" %d. %s\n", aux->id, aux->carro);
			aux = aux->prox;
		}
		printf("\n-----------------------------------------------\n");
	}
}

void escreve_fila(Fila *F)
{
	system("clear||cls");
	Fila *P;
	
	if(fila_vazia(F))
	{
		printf("\n------------------------------------------\n");
		printf("Não existe pessoas na fila.");
		printf("\n------------------------------------------\n");
	}
	else
	{
		printf("\n-----------------------------------------------\n");
		printf("                Clientes na fila.");
		printf("\n-----------------------------------------------\n");
		P = F->ant;
		while(P != F)
		{
			printf("%d. %s\n", P->id, P->nome);
			P = P->ant;
		}
		printf("\n-----------------------------------------------\n");
	}
}

int imprime_modelo(Tipos *tp){
	system("clear||cls");
	if(modelos_vazio(tp)){
		printf("\n------------------------------------------\n");
		printf("Não existe modelos na lista.");
		printf("\n------------------------------------------\n");
		return 0;	
	}else{
		Tipos *aux = tp->prox;
		printf("\n-----------------------------------------------\n");
		printf("                Modelos disponiveis ");
		printf("\n-----------------------------------------------\n");
		while(aux != NULL){
			printf(" %d. %s\n", aux->id, aux->nome);
			aux = aux->prox;
		}
		printf("\n-----------------------------------------------\n");
		return 1;
	}
}

int exibe_Locados(Pilha *I){
	system("clear||cls");
	if(pilha_vazia(I)){
		printf("\n------------------------------------------\n");
		printf("Nenhum carro locado.");
		printf("\n------------------------------------------\n");
		return 0;	
	}else{
		Pilha *aux = I->prox;
		printf("\n-----------------------------------------------\n");
		printf("                Carros em locação ");
		printf("\n-----------------------------------------------\n");
		while(aux != NULL){
			printf(" %d. %s\n", aux->id, aux->carro);
			aux = aux->prox;
		}
		printf("\n-----------------------------------------------\n");
		return 1;
	}
}

Tipos* consulta_Modelo(Tipos *Pessoas)
{
	Tipos *P;
	int modelo;
	
	P = Pessoas;
	printf("\n\n\tDigite o id de um modelo para consultar: ");
	scanf("%d", &modelo); fflush(stdin);

	while(P != NULL && P->id != modelo)
	{
		P = P->prox;
	}
	return P;
}

void passa_para_Fila(Tipos *P)
{
	int LerId;
	String LerNome;
	
	if(P == NULL)
	{
		printf("\n------------------------------------------\n");
		printf("Não existe o id do modelo pesquisado. Voltando ou menu anterior.\n");
		printf("\n------------------------------------------\n");
		system("pause");
	}
	else
	{
		printf("Digte o nome para inserir: ");
		gets(LerNome); fflush(stdin);
		IdF ++;
		enfileira(P->clientes, LerNome, IdF);
		printf("Inserido com sucesso !!!\n");
		system("pause");
	}
}

void exibe_fila(Tipos *P)
{
	if(P == NULL)
	{
		printf("\n------------------------------------------\n");
		printf("Não existe o id do modelo pesquisado. Voltando ou menu anterior.\n");
		printf("\n------------------------------------------\n");
		system("pause");
	}
	else
	{
		escreve_fila(P->clientes);
	}
}

void passa_para_Pilha(Tipos *P)
{
	int LerId;
	String LerNome;
	
	if(P == NULL)
	{
		printf("\n------------------------------------------\n");
		printf("Não existe o id do modelo pesquisado. Voltando ou menu anterior.\n");
		printf("\n------------------------------------------\n");
		system("pause");
	}
	else
	{
		printf("Digte o nome para inserir: ");
		gets(LerNome); fflush(stdin);
		IdP ++;
		empilha(P->carros, LerNome, IdP);
		printf("Inserido com sucesso !!!\n");
		system("pause");
	}
}

void exibe_pilha(Tipos *P)
{
	if(P == NULL)
	{
		printf("\n------------------------------------------\n");
		printf("Não existe o id do modelo pesquisado. Voltando ou menu anterior.\n");
		printf("\n------------------------------------------\n");
		system("pause");
	}
	else
	{
		imprime_pilha(P->carros);
	}
}

void loca_carro(Tipos *P)
{
	Tipos *X;
	int LerCarro;
	Fila *Remover;
	X = consulta_Modelo(P);
	if(X->clientes->prox == X->clientes)
	{
		printf("Não existem clientes na fila !!!\n ");
		printf("Voltando ao menu inicial\n ");
		system("pause");
	}
	else
	{
		fura_Pilha(X->carros, X->listalocados);
		Remover = desenfileira(X->clientes);
		free(Remover);
		printf("Locação concluida com SUCESSO !!!\n ");
		system("pause");
	}
}

void volta_carro(Tipos *P)
{
	Tipos *X;
	int LerCarro , Testa;
	Fila *Remover;
	X = consulta_Modelo(P);
	Testa = exibe_Locados(X->listalocados);
	if(Testa == 0)
	{
		printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
		system("pause");
	}
		else
	{
		printf("Selecione o carro que será finalizada a locação: ");
		scanf("%d", &LerCarro); fflush(stdin);
		volta_estacionar(X->carros, X->listalocados, LerCarro);
		printf("Devolução concluida com SUCESSO !!!\n ");
		system("pause");
	}
}


int main()
{
	setlocale (LC_ALL, "portuguese");
	Tipos *Modelos = (Tipos*) malloc(sizeof(Tipos));
	int modelo=0, opcao=0, LerId;
	String LerNome;
	
	inicia_Lista(Modelos);
	
	do{
			system("clear||cls");
			printf("\n\t1 - Inserir Modelo de carros.");
			printf("\n\t2 - Inserir Cliente na fila de espera.");
			printf("\n\t3 - Listar fila de espera.");
			printf("\n\t4 - Listar modelos disponiveis.");
			printf("\n\t5 - Inserir carro.");
			printf("\n\t6 - Listar carros.");
			printf("\n\t7 - Liberar locação de carros.");
			printf("\n\t8 - Devolver carro.");
			printf("\n\t9 - Sair.");
			printf("\n\n\tDigite uma opção: ");
			scanf("%d", &opcao);
			getchar();
			switch(opcao){
				case 1:
					modelo = imprime_modelo(Modelos);
					system("clear||cls");
					printf("\tDigte o nome do Modelo para inserir: ");
					gets(LerNome); fflush(stdin);
					IdL++;
					insere_Modelos(Modelos, LerNome, IdL);
					printf("\tInserido com sucesso !!!\n");
					system("pause");
					break;
				case 2:	
					system("clear||cls");
					modelo = imprime_modelo(Modelos);
					if(modelo == 0)
					{
						printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
						system("pause");
					}
					else
					{
						passa_para_Fila(consulta_Modelo(Modelos));
					}
					break;
				case 3:
					system("clear||cls");
					modelo = imprime_modelo(Modelos);
					if(modelo == 0)
					{
						printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
						system("pause");
					}
					else
					{
						exibe_fila(consulta_Modelo(Modelos));
						system("pause");
					}	
					break;
				case 4:	
					imprime_modelo(Modelos);
					system("pause");
				break;
				case 5:	
					system("clear||cls");
					modelo = imprime_modelo(Modelos);
					if(modelo == 0)
					{
						printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
						system("pause");
					}
					else
					{
						passa_para_Pilha(consulta_Modelo(Modelos));
					}
				break;
				case 6:	
					system("clear||cls");
					modelo = imprime_modelo(Modelos);
					if(modelo == 0)
					{
						printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
						system("pause");
					}
					else
					{
						exibe_pilha(consulta_Modelo(Modelos));
						system("pause");
					}
				break;
				case 7:	
					system("clear||cls");
					modelo = imprime_modelo(Modelos);
					if(modelo == 0)
					{
						printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
						system("pause");
					}
					else
					{
						loca_carro(Modelos);
					}
					
				break;
				case 8:	
					system("clear||cls");
					modelo = imprime_modelo(Modelos);
					if(modelo == 0)
					{
						printf("\n\nAperte qualquer tecla para voltar ou menu anterior.\n");
						system("pause");
					}
					else
					{	
						volta_carro(Modelos);
					}
				break;
				case 9:	
					exit(0);
				break;
			}
		}while(opcao);
	
	return 0;	
}
