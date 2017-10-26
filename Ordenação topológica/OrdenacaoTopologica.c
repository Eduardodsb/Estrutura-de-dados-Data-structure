#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct _NO
{
  int vertice;
  struct _NO *prox;
} NO;

NO* criaLista(char *temp, int NVertice, int *grau);
int* converteString(char *string, int NVertice, int *tam);
void bubbleSort(int *A, int tam);
NO* insere(int vertice, NO *prox,  int *grau);
int busca(NO *ptlista, int vertice);
void inicializaVetorInt(int *vetor,int tam);
void inicializaVetorChar(char *vetor, int tam);
void ordenacaoTopologica(NO **adj,int *grau, int *verticesord, int tam);
void imprimeVetor(int *vetor, int tam);

int main(){
  int NVertice, NAresta, i, *grau, *verticesord;
  char *Lista;
  NO **adj;

  printf("Entre com o numero de vertices e arestas respectivamente :\n");
  scanf("%d %d", &NVertice, &NAresta); /*É lida as entradas do terminal. Número de vertices e número de arestas*/
  do{} while (getchar() != '\n');/*É feito para tirar qualquer 'enter' que possa está no buffer*/

  grau = (int*) malloc(NVertice * sizeof(int*)); /*Vetor que vai guardar os graus de entrada*/
  verticesord = (int*) malloc(NVertice * sizeof(int*)); /*Vetor que vai guardar o resultado da ordenação topólica*/
  adj = (NO**) malloc(NVertice * sizeof(NO**));/*Vetor adjacente que vai guardar cada ponteiro para cada umas das listas */
  Lista = (char*) malloc(2*NVertice+2 * sizeof(char*));/*Vetor de char(String) que vai receber a relação ligada a cada vertice*/

  if(!adj && !Lista && !grau && !verticesord){ /*É verificado se os espaços foram alocados*/
    printf("Erro: Nao foi possivel alocar memoria.\n");
    exit(1);
  }

  inicializaVetorInt(grau, NVertice); /*É inicializado os vetores alocados acima*/
  inicializaVetorInt(verticesord, NVertice);
  inicializaVetorChar(Lista, 2*NVertice+2);

  for(i = 0; i<NVertice; i++){
    printf("Digite as arestas ligada ao vertice : %d (Separadas por espaco)\n", i+1);
    fgets(Lista, 2*NVertice+2, stdin);/*É lida as entradas do terminal. a relação de vertices ligado ao um determinado vertice*/
    adj[i] = criaLista(Lista, NVertice, grau);/*É chamda a função responsável por criar a lista encadeada e o vetor de grau de entrada*/
  }

  puts("\nGrau de Entrada\n"); /*Imprime o grau de entrada*/
  imprimeVetor(grau, NVertice);

  ordenacaoTopologica(adj, grau, verticesord, NVertice);/*É chamada a função responsável por fazer a ordenação topológica*/
  puts("\nOrdenacao topologica\n");
  imprimeVetor(verticesord, NVertice);

  free(grau); /*É liberado espaços alocados*/
  free(verticesord);
  free(adj);
  free(Lista);
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

void imprimeVetor(int *vetor, int tam){
  int i;
  for(i = 0; i<tam; i++){
    printf("%d ", vetor[i]);
  }
  puts("\n");
}

int* converteString(char *string, int NVertice, int *tam){
  int i,k,j,z,*vertices;
  char *aux;
  i = j = k = z= 0;
  aux = (char*) malloc(strlen(string) * sizeof(char*));/*Vetor intermediário para fazer a conversão*/
  vertices = (int*) malloc(NVertice * sizeof(int*));/*Vetor que receberá cada um dos números convertidos para inteiro*/

  if(!aux && !vertices){
    printf("Erro: Nao foi possivel alocar memoria.\n");
    exit(1);
  }
  inicializaVetorChar(aux, strlen(string));
  inicializaVetorInt(vertices, NVertice);

  while(i <= strlen(string)){
    if((string[i] == ' ' || string[i] == '\0') && (string[i] != '\n')){
      vertices[j] = atoi(aux);
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
  *tam = j;
  return vertices;
}

void bubbleSort(int *vetor, int tam){
  int i, j, temp;
  for(i=0; i<tam-1; i++){
    for(j=0; j<tam-i-1; j++){
      if(vetor[j]>vetor[j+1]){
        temp = vetor[j];
        vetor[j] = vetor[j+1];
        vetor[j+1] = temp;
      }
    }
  }
}

int busca(NO *ptlista, int vertice){
  NO *pt;
  pt = ptlista;
  while(pt != NULL){
    if(pt->vertice == vertice){
      return 1;
    }
    pt = pt->prox;
  }
  return 0;
}

NO* insere(int vertice, NO *prox,  int *grau){
  if(busca(prox, vertice) != 1){/*É chamado busca pára saber se o vertice já não foi incluido*/
    NO *temp;
    temp = (NO*)malloc(sizeof(NO*));
    temp->vertice = vertice;
    temp->prox = prox;
    grau[vertice-1] = grau[vertice-1] + 1;
    return temp;
  }
  return prox;
}

NO* criaLista(char *string, int NVertice, int *grau){
  int *vertices, i, tam;
  NO *prox = NULL;
  if(strlen(string) != 1 && string[0] != ' '){/*Se a entrada for um 'Enter' ou tiver um espaço vazio no início da string considero NULL*/
    vertices = converteString(string, NVertice, &tam); /*É chamada a função responsável por converter a entrada em um vetor de inteiros*/
    bubbleSort(vertices,tam); /*É ordenado o vetor de inteiros criado*/
    for(i=tam-1; i>=0; i--){/*É chamada a função responsável por criar cada uma das structs e é feita a ligação das structs.*/
      prox = insere(vertices[i], prox, grau);
    }
    free(vertices);
  }
  return prox;
}

void ordenacaoTopologica(NO **adj, int *grau, int *verticesord, int tam){
  int i, j, k, *index, x;
  NO *temp;
  x=0;
  index = (int*) malloc(tam*sizeof(int*));
  inicializaVetorInt(index,tam);
  for(i = k = 0; i<tam; i++){
    for(j = 0; j<tam; j++){/*corre o vetor pegando os vértices que tem grau zero*/
      if(grau[j] == 0){/*Se o grau é zero a posição é copiada para o vetor verticesord(Vértices ordenados)*/
        verticesord[k] = j+1;
        k++;
        grau[j]--;
        index[x] = j;
        x++;
      }
    }
    for(j=0; j<x; j++){/*É reduzido 1 aos graus dos adjacentes dos vértices que tinham grau zero e foram guardados no vetor index*/
      temp = adj[index[j]];
      while(temp != NULL){
        grau[temp->vertice-1]--;
        temp = temp->prox;
      }
    }
    x=0;
  }
  free(index);
}
