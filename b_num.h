#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//STRUCT DA LISTA DE NÚMEROS
typedef struct no{
	int info;
	struct no *ant, *prox;
} NO;

//DESCRITOR QUE CONTÉM A LISTA DE NÚMEROS
typedef struct num{
	char sinal;
	NO * inicio;
	NO * fim;
} NUM;

//FUNÇÕES DE MANIPULAÇÃO E OBTENÇÃO DAS LISTAS NUMÉRICAS
NO * insere(NO *l, int elem);
void imprime(NUM *l);
void libera(NO *l);
void liberaNum(NUM *l);
NO* busca(NO *l, int elem);
void limpaZero(NUM *l);
NO* inverte(NO *l);
NUM * copia(NUM * l1);
NO * copiaNo(NUM * l1);
void limpaLista(NUM *l);

//FUNÇÕES DE OBTENÇÃO DE DADOS DAS LISTAS
int testa_lista_zero(NUM * l1);
int tamanhoNumero(NO * l);
NO * fimNoLista(NUM * l);
char * leitura_num();
NUM * string_para_lista(char * vet);
int comparadorModular(NUM * l1, NUM * l2);
int getTamanhoMaximo();
int tamanhoNumero(NO * l);

//FUNÕES DE OPERAÇÃO MATEMÁTICA
NUM * opera(NUM * l1, NUM * l2, char op);
NO * soma(NUM *l1, NUM *l2);
NO * subtracao(NUM * l1, NUM * l2);
NO * multiplica(NUM * l1, NUM * l2);
NO * divide(NUM * l1, NUM * l2);
NO * divide_sum(NUM * l1, NUM * l2);
