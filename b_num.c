#include "b_num.h"

//TAMANHO MAXIMO DO VETOR DE INTEIROS RECEBIDO | OBS: PODE VARIAR DE 1-1000
#define TAMANHO 1000

//RETORNA O TAMANHO DA CONSTANTE TAMANHO
int getTamanhoMaximo(){
  return TAMANHO;
}

//######FUNÇÕES DE MANIPULAÇÃO E OBTENÇÃO DA LISTA#######//
NO* insere(NO *l, int elem){
  //CRIA UM NÓ NOVO
  NO *novo = (NO *) malloc(sizeof(NO));
  novo->ant = NULL;
  novo->prox = l;
  novo->info = elem;

  //FAZ O PRÓXIMO NÓ RECEBER O NOVO
  if(l) l->ant = novo;
  return novo;
}

//FUNÇÃO QUE INVERTE O NÚMERO
NO* inverte(NO *l){
  NO *resp = NULL;
  for(NO * p = l; p ;p = p->prox){
    resp = insere(resp,p->info);
  }
  //LIBERA O NÚMERO ORIGINAL
  libera(l);
  return resp;
}

//LIBERA UMA LISTA ALOCADA
void libera(NO *l){
  NO *p = l, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  }
}

//LIBERA UMA LISTA DO TIPO NÚMERO
void liberaNum(NUM *l){
  NO *p = l->inicio, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  }
  free(l);
}

//IMPRIME UMA LISTA DO TIPO NÚMERO COM SINAL
void imprime(NUM *l){
  NO *p = l->inicio;
  if(l->sinal != ' '){
    printf("\nResposta: %c",l->sinal);
  }else{
    printf("\nResposta: ");
  }
  while(p){
    printf("% d", p->info);
    p = p->prox;
  }
}

//REALIZA A BUSCA DA PRIMEIRA OCORRÊNCIA DE UM ELEMENTO
NO* busca(NO *l, int elem){
  NO *p = l;
  while(p){
    if(p->info == elem) return p;
    p = p->prox;
  }
  return NULL;
}
//#######################################################//


//#############FUNÇÕES INTERNAS DA BIBLIOTECA#############//

//CONTA A QUANTIDADE DE NÓS DE UMA LISTA
int tamanhoNumero(NO * l){
  int contador = 0;
  for (NO * p = l; p; p=p->prox)
  {
    contador ++;
  }
  return contador;
}

//RETORNA QUAL É O ÚLTIMO NÓ DE UMA LISTA DO TIPO NÚMERO
NO * fimNoLista(NUM * l){
  NO * no = NULL;
  for (NO * p = l->inicio; p; p = p->prox)
  {
    no = p;
  }
  return no;
}

//DUPLICA UMA LISTA DO TIPO NÚMERO
NUM * copia(NUM * l1){
  NUM * l2 = (NUM*) malloc(sizeof(NUM));
  NO * no = NULL;
  for (NO * p = l1->fim; p; p=p->ant)
  {
    no = insere(no, p->info);
  }

  l2->sinal = l1->sinal;
  l2->inicio = no;
  l2->fim = fimNoLista(l2);

  return l2;
}

//DUPLICA OS DIGITOS DE UM NÚMERO
NO * copiaNo(NUM * l1){
  NO * no = NULL;
  for (NO * p = l1->fim; p; p=p->ant)
  {
    no = insere(no, p->info);
  }

  return no;
}

//TESTA SE UM NÚMERO É TODO COMPOSTO POR ZEROS
int testa_lista_zero(NUM * l1){
  int resp = 1;
  for(NO * p = l1->inicio; p ;p = p->prox){
    if(p->info != 0){
      resp = 0;
    }
  }
  return resp;
}

//LIBERA UMA LISTA DO TIPO NÚMERO
void limpaLista(NUM *l){
  if(l->inicio == NULL)
    return;

  NO * p = l->inicio, *q;
  while(p){
    q = p;
    p = p->prox;
    free(q);
  }
  l->inicio = NULL;
  l->fim = NULL;
}

//LIBERA OS ZEROS À ESQUERDA DE UM NÚMERO
void limpaZero(NUM *l){
  NO * p = l->fim, *q;
  while((p->ant) && (p->info == 0)){
    q = p;
    p=p->ant;
    l->fim = p;
    p->prox = NULL;
    free(q);
  }
}

//########################################################//


//######FUNÇÕES PARA CRIAÇÃO DA LISTA#######//

//REALIZA A LEITURA DO NÚMERO E FAZ A VALIDAÇÃO
char * leitura_num(){
  char * vet = (char *) malloc(sizeof(char) * TAMANHO);
  scanf(" %1000[^\n]", vet);
  if(strlen(vet) > TAMANHO) return NULL;
  int is_number = 0;

  if(strlen(vet) < 1) return NULL;

  if(strlen(vet) == 1){
    if(vet[0] == '+' || vet[0] == '-'){
      return NULL;
    }
  }

  if((vet[0] >= '0' && vet[0] <= '9') || vet[0] == '+' || vet[0] == '-'){
    is_number = 1; //Ou seja o número está no formato correto
  }

  if(!is_number) return NULL;

  for(int i = 1; i < strlen(vet); i++){
    if(vet[i] >= '0' && vet[i] <= '9'){
      continue; //Se a posição armazenar um número verifica-se a próxima
    }
    is_number = 0;
    break;
  }

  if(!is_number) return NULL;

  return vet;
}

//TRANSFORMA A NOSSA STRING EM UMA LISTA DUPLAMENTE ENCADEADA DO TIPO NÚMERO
NUM * string_para_lista(char * vet){
  if(vet == NULL) return NULL;

  NO * l = NULL;
  NUM * n = (NUM *) malloc(sizeof(NUM));
  int inicio = 0;

  if(vet[0] != '+' && vet[0] != '-'){
    n->sinal = '+';
  }else{
    n->sinal = vet[0];
    inicio = 1;
  }

  for(int i = inicio; i < strlen(vet); i++){
    //Transforma os caracteres em números correspondentes
    l = insere(l, vet[i] - '0');
    //Como a função insere no início o primeiro número inserido será o último da lista
    if(i == inicio){
      n->fim = l;
    }
  }
  n->inicio = l;

  //LIMPA ZEROS A ESQUERDA NO NÚMERO
  limpaZero(n);

  //RETORNA A LISTA NUMÉRICA
  return n;
}
//##########################################//

//#########FAZ A OPERAÇÃO DE DOIS NÚMEROS##########//
NUM * opera(NUM * l1, NUM * l2, char op){
  NUM * l3 = (NUM *) malloc(sizeof(NUM));
  int aux_comp;
  aux_comp = comparadorModular(l1,l2);
  if(l1->sinal == '+' && l2->sinal == '+'){
    if(op == '+'){
      l3->inicio = soma(l1,l2);
      l3->sinal = '+';
    }else if(op == '-'){
      if(aux_comp == 1){
        l3->inicio = subtracao(l1,l2);
        l3->sinal = '+';
      }else if(aux_comp == -1){
        l3->inicio = subtracao(l2,l1);
        l3->sinal = '-';
      }else if(aux_comp == 0){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }
    }else if(op == '*'){
      l3->inicio = multiplica(l1,l2);
      l3->sinal = '+';
    }else if(op == '/'){
      if(aux_comp == 1){
        l3->inicio = divide(l1,l2);
        l3->sinal = '+';
      }else if(aux_comp == -1){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }else if(aux_comp == 0){
        if(testa_lista_zero(l1) && testa_lista_zero(l2)){
          printf("\nDivisão inválida por zero!\n");
          l3->inicio = NULL;
        }else{
          NO * novo = (NO *) malloc(sizeof(NO));
          novo->info = 1;
          novo->ant = NULL;
          novo->prox = NULL;
          l3->inicio = novo;
          l3->fim = novo;
          l3->sinal = '+';
        }
      }
    }
  }else if(l1->sinal == '+' && l2->sinal == '-'){
    if(op == '+'){
      if(aux_comp == 1){
        l3->inicio = subtracao(l1,l2);
        l3->sinal = '+';
      }else if(aux_comp == -1){
        l3->inicio = subtracao(l2,l1);
        l3->sinal = '-';
      }else if(aux_comp == 0){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }
    }else if(op == '-'){
      l3->inicio = soma(l1,l2);
      l3->sinal = '+';
    }else if(op == '*'){
      l3->inicio = multiplica(l1,l2);
      l3->sinal = '-';
    }else if(op == '/'){
      if(aux_comp == 1){
        l3->inicio = divide(l1,l2);
        l3->sinal = '-';
      }else if(aux_comp == -1){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }else if(aux_comp == 0){
        if(testa_lista_zero(l1) && testa_lista_zero(l2)){
          printf("\nDivisão inválida por zero!\n");
          l3->inicio = NULL;
        }else{
          NO * novo = (NO *) malloc(sizeof(NO));
          novo->info = 1;
          novo->ant = NULL;
          novo->prox = NULL;
          l3->inicio = novo;
          l3->fim = novo;
          l3->sinal = '-';
        }
      }
    }
  }else if(l1->sinal == '-' && l2->sinal == '+'){
    if(op == '+'){
      if(aux_comp == 1){
        l3->inicio = subtracao(l1,l2);
        l3->sinal = '-';
      }else if(aux_comp == -1){
        l3->inicio = subtracao(l2,l1);
        l3->sinal = '+';
      }else if(aux_comp == 0){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }
    }else if(op == '-'){
      l3->inicio = soma(l1,l2);
      l3->sinal = '-';
    }else if(op == '*'){
      l3->inicio = multiplica(l1,l2);
      l3->sinal = '-';
    }else if(op == '/'){
      if(aux_comp == 1){
        l3->inicio = divide(l1,l2);
        l3->sinal = '-';
      }else if(aux_comp == -1){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }else if(aux_comp == 0){
        if(testa_lista_zero(l1) && testa_lista_zero(l2)){
          printf("\nDivisão inválida por zero!\n");
          l3->inicio = NULL;
        }else{
          NO * novo = (NO *) malloc(sizeof(NO));
          novo->info = 1;
          novo->ant = NULL;
          novo->prox = NULL;
          l3->inicio = novo;
          l3->fim = novo;
          l3->sinal = '-';
        }
      }
    }
  }else if(l1->sinal == '-' && l2->sinal == '-'){
    if(op == '+'){
      l3->inicio = soma(l1,l2);
      l3->sinal = '-';
    }else if(op == '-'){
      if(aux_comp == 1){
        l3->inicio = subtracao(l1,l2);
        l3->sinal = '-';
      }else if(aux_comp == -1){
        l3->inicio = subtracao(l2,l1);
        l3->sinal = '+';
      }else if(aux_comp == 0){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }
    }else if(op == '*'){
      l3->inicio = multiplica(l1,l2);
      l3->sinal = '+';
    }else if(op == '/'){
      if(aux_comp == 1){
        l3->inicio = divide(l1,l2);
        l3->sinal = '+';
      }else if(aux_comp == -1){
        NO * novo = (NO *) malloc(sizeof(NO));
        novo->info = 0;
        novo->ant = NULL;
        novo->prox = NULL;
        l3->inicio = novo;
        l3->fim = novo;
      }else if(aux_comp == 0){
        if(testa_lista_zero(l1) && testa_lista_zero(l2)){
          printf("\nDivisão inválida por zero!\n");
          l3->inicio = NULL;
        }else{
          NO * novo = (NO *) malloc(sizeof(NO));
          novo->info = 1;
          novo->ant = NULL;
          novo->prox = NULL;
          l3->inicio = novo;
          l3->fim = novo;
          l3->sinal = '+';
        }
      }
    }
  }

  if(l3->inicio != NULL && l3 != NULL){

    //INVERTENDO A LISTA PARA MULTIPLAS OPERAÇÃO
    l3->inicio = inverte(l3->inicio);

    //ADICIONANDO O 'NO' NO 'FINAL' DO DESCRITOR NUM
    l3->fim = fimNoLista(l3);

    //LIMPANDO OS ZEROS À ESQUERDA
    limpaZero(l3);

    if(testa_lista_zero(l3)){
      l3->sinal = ' ';
    }
  }

  return l3;
}
//#################################################//

//###############FUNÇÕES MATEMÁTICAS###############//
//SOMA DOIS NÚMEROS
NO * soma(NUM * l1, NUM * l2){
  if(l1 == NULL || l2 == NULL) return NULL;
  if(!l1->inicio || !l2->inicio) return NULL;

  NO * a = l1->inicio, * b = l2->inicio;
  NO *novo = NULL;

  int n1 = 0, n2 = 0, v = 0;

  while(a || b){

    if(a){
      n1 = a->info;
      a = a->prox;
    }else{
      n1 = 0;
    }

    if(b){
      n2 = b->info;
      b = b->prox;
    }else{
      n2 = 0;
    }

    int soma = (n1 + n2 + v);
    if(soma >= 10){
      v = 1;
    }else{
      v = 0;
    }

    novo = insere(novo, soma%10);
  }

  if(v){
    novo = insere(novo, v);
  }

  return novo;
}

//SUBTRAI DOIS NÚMEROS
NO * subtracao(NUM * l1, NUM * l2){

  if(l1 == NULL || l2 == NULL) return NULL;
  if(!l1->inicio || !l2->inicio) return NULL;

  NO * a = l1->inicio, * b = l2->inicio;
  NO *novo = NULL;

  int n1 = 0, n2 = 0, v = 0;

  while(a || b){

    if(a){
      n1 = a->info;
      a = a->prox;
    }else{
      n1 = 0;
    }

    if(b){
      n2 = b->info;
      b = b->prox;
    }else{
      n2 = 0;
    }

    int sub = (n1 - n2 - v);
    if(sub < 0){
      v = 1;
      sub += 10;
    }else{
      v = 0;
    }

    novo = insere(novo, sub);
  }

  if(v){
    novo = insere(novo, v);
  }

  return novo;
}

//MULTIPLICA DOIS NÚMEROS
NO * multiplica(NUM * l1, NUM * l2){
  if(l1 == NULL || l2 == NULL) return NULL;
  if(!l1->inicio || !l2->inicio) return NULL;

  NO *novo = NULL;
  novo = insere(novo, 0);
  NUM *numero1 = (NUM *) malloc(sizeof(NUM));
  NUM *numero2 = (NUM *) malloc(sizeof(NUM));
  int contador_zeros = 0;
  for (NO * a = l1->inicio; a ; a = a->prox)
  {
    NO *parcial = NULL;
    int v = 0; //VAI DA MULTIPLICAÇÃO
    for (NO * b = l2->inicio; b ; b = b->prox)
    {
      int n = (a->info * b->info) + v;
      parcial = insere(parcial, n%10);
      v = n / 10;
    }
    if(v){
      parcial = insere(parcial, v);
    }

    numero1->inicio = parcial;
    parcial = inverte(parcial);
    for (int i = 0; i < contador_zeros; i++)
    {
      parcial = insere(parcial, 0);
    }
    contador_zeros++;
    numero1->inicio = parcial;

    numero2->inicio = novo;
    novo = soma(numero1, numero2);
    novo = inverte(novo);
    numero2->inicio = novo;

    //libera(parcial);
  }
  novo = inverte(novo);

  return novo;
}

//DIVIDE DOIS NÚMEROS SUBTRAINDO SUCESSIVAMENTE
NO * divide_sum(NUM * l1, NUM * l2){
  if(l1 == NULL || l2 == NULL) return NULL;

  if(testa_lista_zero(l2)) {
    printf("\nDivisão inválida por zero!\n");
    return NULL;
  }

  NUM * dividendo = copia(l1);
  NUM * divisor = copia(l2);
  NUM * resposta = (NUM *) malloc(sizeof(NUM));
  resposta->inicio = NULL;
  resposta->inicio = insere(resposta->inicio, 0);

  NUM * unitario = (NUM *) malloc(sizeof(NUM));
  unitario->inicio = NULL;
  unitario->inicio = insere(unitario->inicio, 1);

  NUM * resto = (NUM *) malloc(sizeof(NUM));

  while((comparadorModular(dividendo,divisor) != -1)){
    resto->inicio = inverte(subtracao(dividendo, divisor));
    limpaLista(dividendo);
    resto->fim = fimNoLista(resto);
    dividendo->inicio = copiaNo(resto);
    limpaLista(resto);
    char t;
    dividendo->fim = fimNoLista(dividendo);
    limpaZero(dividendo);
    resposta->inicio = inverte(soma(resposta, unitario));
  }

  //DEFININDO O RETORNO
  NO * retorno = inverte(resposta->inicio); 

  //RETORNANDO O NO DA DIVISÃO
  return retorno;
}

NO * divide(NUM *l1, NUM *l2){
  if(l1 == NULL || l2 == NULL) return NULL;

  if(testa_lista_zero(l2)) {
    printf("\nDivisão inválida por zero!\n");
    return NULL;
  }
  
  NUM * dividendo = copia(l1);    //NÚMERO QUE SERÁ DIVIDIDO
  NUM * divisor_prox = copia(l2); //DIVISOR PARA COMPARAÇÃO
  NUM * divisor_ant = copia(l2);  //DIVISOR ANTERIOR PARA USO 

  //LISTA COM O NÚMERO 10 PARA TRABALHAR COM A MULTIPLICAÇÃO
  NUM * multiplicador_10 = (NUM *) malloc(sizeof(NUM));
  multiplicador_10->sinal = '+';
  multiplicador_10->inicio = NULL;multiplicador_10->fim = NULL;
  multiplicador_10->inicio = insere(multiplicador_10->inicio, 1);
  multiplicador_10->inicio = insere(multiplicador_10->inicio, 0);
  multiplicador_10->fim = fimNoLista(multiplicador_10);

  //CONTADOR DE VEZES DIVÍSEIS POR 10 PARCIAL
  NUM * contador = (NUM *) malloc(sizeof(NUM));
  contador->inicio = NULL;
  contador->inicio = insere(contador->inicio, 1);

  //CONTADOR DE VEZES DIVISÍVEIS POR 10 TOTAL
  NUM * contador_total = (NUM *) malloc(sizeof(NUM));
  contador_total->inicio = NULL;
  contador_total->inicio = insere(contador_total->inicio, 0);
  
  //RESTO DA DIVISÃO
  NUM * resto = copia(l1);
  resto->fim = fimNoLista(resto);

  //LOOP PARA VER QUANTAS 10^n VEZES O DIVISOR CABE NO DIVIDENDO
  while(1){
    //TIRA ZEROS DA ESQUERDA DO RESTO
    limpaZero(resto);

    //SAI QUANDO O RESTO TIVER O MESMO NUMERO DE CASAS QUE O DIVISOR + 1
    if(tamanhoNumero(resto->inicio) <= tamanhoNumero(l2->inicio) + 1)
      break; //SAIDA
    
    while(1){      
      //FAZ O DIVISOR ANTERIOR RECEBER O NOVO
      limpaLista(divisor_ant);
      divisor_ant = copia(divisor_prox);
      divisor_ant->fim = fimNoLista(divisor_ant);
      

      //MULTIPLICO O PRÓXIMO DIVISOR POR 10
      NUM * p1 = (NUM *) malloc(sizeof(NUM));
      p1->inicio = inverte(multiplica(divisor_prox, multiplicador_10));
      p1->fim = fimNoLista(p1);
      limpaLista(divisor_prox);
      divisor_prox = copia(p1);
      limpaLista(p1);
      
      //SAIDA DO LOOP QUANDO O PRÓXIMO DIVISOR É MAIOR QUE O DIVIDENDO
      if(comparadorModular(resto ,divisor_prox) == -1){
        break;  //SAIDA
      }

      //ACRESENTO NO CONTADOR DE MÚLTIPLOS DE 10 LOCAL
      NUM * p2 = (NUM *) malloc(sizeof(NUM)); //VARIÁVEL PROVISÓRIA
      p2->inicio = inverte(multiplica(contador, multiplicador_10));
      p2->fim = fimNoLista(p2);
      limpaLista(contador); //LIMPO A LISTA PARA ELA RECEBER A NOVA
      contador = copia(p2);
      contador->fim = fimNoLista(contador);
      limpaLista(p2);
    }

    //MODIFICO A VARIÁVEL RESTO PARA RECEBER O RESTO DO DIVISOR PELO QUE FOI RETIRADO
    NUM * prov1 = (NUM *) malloc(sizeof(NUM));
    limpaZero(divisor_ant);
    prov1->inicio = inverte(subtracao(resto, divisor_ant));
    prov1->fim = fimNoLista(prov1);
    limpaLista(resto);
    resto = copia(prov1);
    resto->fim = fimNoLista(resto);
    limpaLista(prov1);

    //ACRESENTO NO CONTADOR DE MÚLTIPLOS DE 10 GERAL
    NUM * prov = (NUM *) malloc(sizeof(NUM));
    prov->inicio = inverte(soma(contador, contador_total));
    prov->fim = fimNoLista(prov);
    limpaLista(contador_total);
    contador_total = copia(prov);
    contador_total->fim = fimNoLista(contador_total);
    limpaLista(prov);

    //TERMINA O LOOP E ORGANIZA OS DADOS PARA A PRÓXIMA ITERAÇÃO
    limpaLista(divisor_prox);
    divisor_prox = copia(l2);
    limpaLista(contador);
    contador->inicio = insere(contador->inicio, 1);

  }

  //DIVIDE PELO MÉTODO MENOS EFICIENTE
  NUM * resposta = (NUM *) malloc(sizeof(NUM));
  resposta->inicio = inverte(divide_sum(resto, l2));

  //SOMA O VALOR DESCOBERTO PELO MÁTODO MAIS EFICIENTE COM O QUE VEIO DO MÉTODO MAIS EFICIENTE
  NUM * respostaFinal = (NUM *) malloc(sizeof(NUM));
  respostaFinal->inicio = inverte(soma(resposta, contador_total));
  respostaFinal->fim = fimNoLista(respostaFinal);

  //DEFININDO O RETORNO
  NO * retorno = inverte(respostaFinal->inicio);

  //RETORNANDO O NO DA DIVISÃO
  return retorno;
}


//FUNÇÃO QUE COMPARA O MÓDULO DE DOIS NÚMEROS
int comparadorModular(NUM * l1, NUM * l2){
  if(l1 == NULL || l2 == NULL) return -2;
  if(!l1->inicio || !l2->inicio) return -2;

  NO * p = l1->inicio, * q = l2->inicio;
  int retorno = 0; //-1 para l1 menor que l2, 0 para l1 igual a l2 e 1 para l1 maior que l2, -2 Erro de comparacao

  while(1){
    if(p->info > q->info){
      retorno = 1;
    }else if(p->info < q->info){
      retorno = -1;
    }

    int flag1 = 0, flag2 = 0;

    if(p->prox){
      p = p->prox;
    }else{
      flag1 = 1;
    }

    if(q->prox){
      q = q->prox;
    }else{
      flag2 = 1;
    }

    if(flag1 && flag2){
      return retorno;
    }else if(flag1 && !flag2){
      return -1;
    }else if(!flag1 && flag2){
      return 1;
    }
  }
}

//#################################################//