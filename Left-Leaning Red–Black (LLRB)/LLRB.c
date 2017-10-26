#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _NO
{
  int chave;
  char cor;
  struct _NO *dir;
  struct _NO *esq;
} NO;

void insereLLRN(NO **ptraiz, int chave);
void insere(NO **ptraiz, int chave);
int* converteString(char *string, int Nchaves);
void inicializaVetorInt(int *vetor,int tam);
void inicializaVetorChar(char *vetor, int tam);
void rotesq(NO **ptraiz);
void rotdir(NO **ptraiz);
char cor(NO *pt);
void imprimePreOrdem(NO *ptraiz);

int main(int argc, char const *argv[]) {
  char *string;
  int *chaves, Nchaves, i/*, chave*/;
  NO *ptraiz = NULL;

  printf("Digite a quantidade de chaves que serão inseridas\n");
  scanf("%d", &Nchaves);
  getchar();

/*  while(scanf("%d", &chave) != EOF){
    do{} while (getchar() != '\n');
    insere(&ptraiz,chave);
  }*/

  string = (char*) malloc(5*Nchaves+2 * sizeof(char*));

  printf("Digite as chaves sepradas por espaço\n");
  fgets(string, 5*Nchaves+2, stdin);

  chaves = converteString(string,Nchaves);

  for(i = 0; i<Nchaves; i++){
    insere(&ptraiz,chaves[i]);
  }

  imprimePreOrdem(ptraiz);

  return 0;
}

void inicializaVetorInt(int *vetor, int tam){
  int i;
  for(i=0; i<tam; i++){
    vetor[i] = 0;
  }
}

void inicializaVetorChar(char *vetor, int tam){
  int i;
  for(i=0; i<tam; i++){
    vetor[i] = '\0';
  }
}

int* converteString(char *string, int Nchaves){
  int i,k,j,*chaves;
  char *aux;
  i = j = k = 0;
  aux = (char*) malloc(strlen(string) * sizeof(char*));/*Vetor intermediário para fazer a conversão*/
  chaves = (int*) malloc(Nchaves * sizeof(int*));/*Vetor que receberá cada um dos números convertidos para inteiro*/

  if(!aux && !chaves){
    printf("Erro: Nao foi possivel alocar memoria.\n");
    exit(1);
  }
  inicializaVetorChar(aux, strlen(string));
  inicializaVetorInt(chaves, Nchaves);

  while(i <= strlen(string)){
    if((string[i] == ' ' || string[i] == '\0') && (string[i] != '\n')){
      chaves[j] = atoi(aux);
      j++;
      k = 0;
      i++;
      free(aux);
      aux = (char*) malloc(strlen(string) * sizeof(char*));
      inicializaVetorChar(aux, strlen(string));
    }
    aux[k] = string[i];
    k++;
    i++;
  }
  free(aux);
  return chaves;
}

void insere(NO **ptraiz, int chave){
  insereLLRN(ptraiz, chave);
  (*ptraiz)->cor = 'N';
}

void insereLLRN(NO **ptraiz, int chave){
  if(*ptraiz == NULL){
    *ptraiz = (NO*) malloc(sizeof(NO*));
    if(!ptraiz){
      printf("Erro: Nao foi possivel alocar memoria.\n");
      exit(1);
    }
    (*ptraiz)->chave = chave;
    (*ptraiz)->dir = (*ptraiz)->esq = NULL;
    (*ptraiz)->cor = 'R';
    return;
  }
  if(chave < (*ptraiz)->chave){
    insereLLRN(&(*ptraiz)->esq, chave);
  }else{
    insereLLRN(&(*ptraiz)->dir, chave);
  }
  if((cor((*ptraiz)->esq) == 'N') && (cor((*ptraiz)->dir) == 'R')){
    rotesq(ptraiz);
  }
  if((cor((*ptraiz)->esq) == 'R') && (cor(((*ptraiz)->esq)->esq) == 'R')){
    rotdir(ptraiz);
  }
  if((cor((*ptraiz)->esq) == 'R') && (cor((*ptraiz)->dir) == 'R')){
    (*ptraiz)->cor = 'R';
    ((*ptraiz)->esq)->cor = 'N';
    ((*ptraiz)->dir)->cor = 'N';
  }
}

char cor(NO *pt){
  return (pt == NULL)?'N':pt->cor;
}

void rotesq(NO **ptraiz){
  NO *temp;
  char aux;
  aux = (*ptraiz)->cor;
  (*ptraiz)->cor = 'R';
  temp = *ptraiz;
  *ptraiz = temp->dir;
  (*ptraiz)->cor = aux;
  temp->dir = (*ptraiz)->esq;
  (*ptraiz)->esq = temp;
}

void rotdir(NO **ptraiz){
  NO *temp;
  char aux;
  aux = (*ptraiz)->cor;
  (*ptraiz)->cor = 'R';
  temp = *ptraiz;
  *ptraiz = temp->esq;
  (*ptraiz)->cor = aux;
   temp->esq = (*ptraiz)->dir;
   (*ptraiz)->dir =  temp;
}

void imprimePreOrdem(NO *ptraiz){
  if(ptraiz != NULL){
    printf("chave: %d, cor: %c \n", ptraiz->chave, ptraiz->cor);
  /*  printf("Entrando na esquerda de: %d\n",ptraiz->chave );*/
    imprimePreOrdem(ptraiz->esq);
  /*  printf("Entrando na direita de: %d\n",ptraiz->chave );*/
    imprimePreOrdem(ptraiz->dir);
  }
}
