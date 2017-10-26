/*
Nome: Eduardo da Silva Barbosa
DRE: 116150432
Segundo Trabalho: expressões
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define Tam 100

char* init_char(int *topo);
int* init_int(int *topo);
void push_char(char x, char *pilha, int *topo);
void push_int(int x, int *pilha, int *topo);
void overflow_char(char *pilha, int topo);
void overflow_int(int *pilha, int topo);
int pop_int(int *pilha, int *topo);
void pop_char(int *topo);
int compoeNumero(char *ex, int index, int *N);

int main(){
  char *ex = (char*)malloc(Tam * sizeof(char*));
  char *pilhaOperadores;
  int *pilhaOperandos;
  int topoOperadores, topoOperandos, i, num, aux1,aux2, aux3;
  /*É Iniciada as duas pilhas, uma para os operadores(tipo: char) e outra para os operandos(tipo: int)*/
  pilhaOperadores = init_char(&topoOperadores);
  pilhaOperandos = init_int(&topoOperandos);

  scanf("%s", ex);/*É lido a entrada do usuário*/
  getchar();/*É lido possível "enter" que esteja no buffer*/

  for(i = 0; i < (int)strlen(ex); i++){
    /*É Separado os operandos e operadores em duas pilhas distintas*/
    if(((127-ex[i]) >= 70) && ((127-ex[i]) <= 79)){/*É Verificado se é um número. Me baseando na tabela ascii*/
      i = compoeNumero(ex, i, &num); /*O index (i) é alterado pro primeiro dígito (da direita para a esquerda)*/
      push_int(num, pilhaOperandos, &topoOperandos);/*Os números são colocados na pilha*/
    }else if((((127-ex[i]) >= 80) && ((127-ex[i]) <= 85) && (ex[i] != 46) && (ex[i] != 44))){/*Verifico se é um operador se baseando na tabela ascii*/
      push_char(ex[i], pilhaOperadores, &topoOperadores);/*Os operadores são colocados na pilha*/
    }
    if((ex[i] == 41) && topoOperandos != 1){/*É Verificado se é ")". Me baseando na tabela ascii*/
      if(pilhaOperadores[topoOperadores-1] == 43){/*É Verificado se é o operador de soma*/
        aux1 = pop_int(pilhaOperandos, &topoOperandos);
        aux2 = pop_int(pilhaOperandos, &topoOperandos);
        aux3 = aux2 + aux1;
        push_int(aux3, pilhaOperandos, &topoOperandos);
        pop_char(&topoOperadores);
      }
      if(pilhaOperadores[topoOperadores-1] == 45){/*É Verificado se é o operador de subtração*/
        aux1 = pop_int(pilhaOperandos, &topoOperandos);
        aux2 = pop_int(pilhaOperandos, &topoOperandos);
        aux3 = aux2 - aux1;
        push_int(aux3, pilhaOperandos, &topoOperandos);
        pop_char(&topoOperadores);
      }
      if(pilhaOperadores[topoOperadores-1] == 42){/*É Verificado se é o operador de multiplicação*/
        aux1 = pop_int(pilhaOperandos, &topoOperandos);
        aux2 = pop_int(pilhaOperandos, &topoOperandos);
        aux3 = aux2 * aux1;
        push_int(aux3, pilhaOperandos, &topoOperandos);
        pop_char(&topoOperadores);
      }
      if(pilhaOperadores[topoOperadores-1] == 47){/*É Verificado se é o operador de divisão*/
        aux1 = pop_int(pilhaOperandos, &topoOperandos);
        aux2 = pop_int(pilhaOperandos, &topoOperandos);
        aux3 = aux2 / aux1;
        push_int(aux3, pilhaOperandos, &topoOperandos);
        pop_char(&topoOperadores);
      }
    }
  }

  printf("O resultado é : %d", pilhaOperandos[0]);/*É Impresso o resultado*/
  /*É Liberado as alocações*/
  free(ex);
  free(pilhaOperadores);
  free(pilhaOperandos);
  return 0;
}

int compoeNumero(char *ex, int index, int *N){/*Essa função é responsavél por compor os números e transforma-los em inteiros*/
  int cont = 0;
  int i = index;
  char *temp = (char*)malloc(Tam * sizeof(char*));
  while(((127-ex[i]) >= 70) && ((127-ex[i]) <= 79)){/*Enquanto for um dígito ele vai jogar no temp*/
    temp[cont] = ex[i];
    i++;
    cont++;
  }
  (*N) = atoi(temp);/*Converte a string no temp em um inteiro*/
  free(temp);
  i--;
  return i;/*Retorno a nova posição do index*/
}

char* init_char(int *topo){/*Inicia a pilha de char(operadores)*/
  char *pilha = (char*)malloc(Tam * sizeof(char*));
  if(!pilha){
    printf("Sem memoria disponivel!\n");
    exit(1);
  }
  (*topo) = 0;
  return pilha;
}

int* init_int(int *topo){/*Inicia a pilha de int(operandos)*/
  int *pilha = (int*)malloc(Tam * sizeof(int*));
  if(!pilha){
    printf("Sem memoria disponivel!\n");
    exit(1);
  }
  (*topo) = 0;
  return pilha;
}

void push_char(char x, char *pilha, int *topo){/*Insere na pilha de operadores*/
  if(*topo >= Tam){/*Caso a pilha fique cheia será expandido o tamanho*/
    overflow_char(pilha,(*topo));
  }
  pilha[*topo] = x;/*É Inserido o novo elemento*/
  (*topo)++;/*O topo é incrementado */
}

void push_int(int x, int *pilha, int *topo){/*Insere na pilha de operandos*/
  if(*topo >= Tam){/*Caso a pilha fique cheia será expandido o tamanho*/
    overflow_int(pilha,(*topo));
  }
  pilha[*topo] = x;/*É Inserido o novo elemento*/
  (*topo)++;/*O topo é incrementado */
}

int pop_int(int *pilha, int *topo){/*O topo é reduzido e retorna o elementono topo*/
  if(*topo == 0){/*É verificado se a pilha já não está vazia.*/
    printf("Erro! Pilha está vazia.\n");
    return -1;
  }
  (*topo)--;
  return pilha[(*topo)];/*O elemento do topo da pilha é retornado*/
}

void pop_char( int *topo){/*O topo é reduzido*/
  if(*topo == 0){/*É verificado se a pilha já não está vazia.*/
    printf("Erro! Pilha está vazia.\n");
    return;
  }
  (*topo)--;
}

void overflow_char(char *pilha, int topo){ /*Faz a expansão da pilha dos operadores*/
  int i;
  int tam = topo*2;
  char *temp = (char*)malloc(tam * sizeof(char*));/*É Alocada a nova pilha*/
  if(!pilha){/*É veficado se a mémoria foi alocada*/
    printf("Sem memoria disponivel!\n");
    exit(1);
  }
  for(i = 0; i<topo; i++){
    temp[i] = pilha[i];/*É passado todos os elementos da pilha antiga para a nova*/
  }
  free(pilha);/*Libera a pilha antiga*/
  pilha  = temp;
}

void overflow_int(int *pilha, int topo){ /*Faz a expansão da pilha dos operandos*/
  int i;
  int tam = topo*2;
  int *temp = (int*)malloc(tam * sizeof(int*));/*É Alocada a nova pilha*/
  if(!pilha){/*É veficado se a mémoria foi alocada*/
    printf("Sem memoria disponivel!\n");
    exit(1);
  }
  for(i = 0; i<topo; i++){
    temp[i] = pilha[i];/*É passado todos os elementos da pilha antiga para a nova*/
  }
  free(pilha);/*Libera a pilha antiga*/
  pilha  = temp;
}
