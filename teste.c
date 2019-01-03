#include "b_num.h"

int main(void)
{

	NUM * l1;
	NUM * l2;
	NUM * l3;
	char * vet1 = (char *) malloc(sizeof(char *) * getTamanhoMaximo());
	char * vet2 = (char *) malloc(sizeof(char *) * getTamanhoMaximo());

	int contador_eq = 1;
	while(1){

		printf("################OPERAÇÃO %d################\n", contador_eq);
		printf("Numero 1 : ");
		while(1){
			vet1 = leitura_num();
			if(vet1 != NULL) break;
			printf("Numero Inválido, insira novamente: ");
		}

		printf("Numero 2 : ");
		while(1){
			vet2 = leitura_num();
			if(vet2 != NULL) break;
			printf("Numero Inválido, insira novamente: ");
		}

		//CONDIÇÃO DE SAÍDA, DOIS NUMEROS IGUAIS A 0
		if(strlen(vet1) == 1 && strlen(vet2) == 1 && vet1[0] == '0' && vet2[0] == '0'){ break; }

		l1 = string_para_lista(vet1);
		l2 = string_para_lista(vet2);

		char op = '+';
		//Bug que não sabemos resolver
		printf("Operação (+, -, * ou /): ");
		while(1){
			char string_op[1];
			scanf(" %s",string_op);
			if((string_op[0] == '+' || string_op[0] == '-' || string_op[0] == '*' || string_op[0] == '/') && strlen(string_op) == 1){
				op = string_op[0];
				break;
			}
			printf("Operação Inválida, insira novamente: ");
		}

		l3 = opera(l1,l2,op);
		if(l3->inicio != NULL && l3 != NULL){
			l3->inicio = inverte(l3->inicio);
			imprime(l3);
			printf("\n");
		}

		//LIBERA MEMÓRIA
		liberaNum(l1);
		liberaNum(l2);
		liberaNum(l3);

		//ESPAÇAMENTO PARA A PRÓXIMA LEITURA
		printf("###########################################");
		printf("\n");
		contador_eq ++;
	}

	printf("###########################################\n");
	printf("FIM DE OPERAÇÕES\n");
	return 0;

}
