#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int** alocarMatriz(int Tam);
void geraMatriz(int **M, int Tam);
void printMatriz(int **M, int Tam);
void multiplicarMatriz(int **A, int **B, int **C,int Tam);
void soma(int **A, int **B, int **C, int Tam);
void subtracao(int **A, int **B, int **C, int Tam);
void algoritmoDeStrassen(int **A, int **B, int **D, int Tam);
void liberamemoria(int **A, int Tam);

int main (int argc, char *argv[]){
  int Tamanho = atoi(argv[1]); /*Converto o argumento recebido pela main em inteiro*/
  /*Aloco as Matrizes necessárias, onde A e B são meus operandos e C e D para guardar os resultados*/
  int **A = alocarMatriz(Tamanho);
  int **B = alocarMatriz(Tamanho);
  int **C = alocarMatriz(Tamanho);
  int **D = alocarMatriz(Tamanho);

  srand(time(NULL)); /*Pego o horário do PC como base para gerar o números aleatórios*/

  /*Gera a matriz A e B que serão utilizadas no Método Tradicional e o Método de Strassen*/
  geraMatriz(A, Tamanho);
  geraMatriz(B, Tamanho);
/*
  printMatriz(A, Tamanho);
  printMatriz(B, Tamanho);
*/
  printf("_____________Método Tradicional_______________\n\n\n");
  clock_t inicialTradicional = clock();/*Pego o horário em que a função de multiplicação do método tradicional é chamada*/
  multiplicarMatriz(A,B,C,Tamanho); /*Chamo a função de multiplicação "tradicional"*/
  printf("demorou %li milésimos\n\n", clock() - inicialTradicional); /*Imprimo o tempo resultante*/
/*  printMatriz(C, Tamanho);*/

  printf("_____________Método de Strassen_______________\n\n\n");
  clock_t inicialStrassen = clock(); /*Pego o horário em que a função de multiplicação do método de Strassen é chamada*/
  algoritmoDeStrassen(A,B,D,Tamanho); /*Chamo a função de multiplicação de Strassen*/
  printf("demorou %li milésimos\n\n", clock() - inicialStrassen); /*Imprimo o tempo resultante*/
/*  printMatriz(D, Tamanho);*/

  /*Libero as matrizes restantes*/
  liberamemoria(A,Tamanho);
  liberamemoria(B,Tamanho);
  liberamemoria(C,Tamanho);
  liberamemoria(D,Tamanho);

  return 0;
}

int** alocarMatriz(int Tam){ /*Recebe o tamanho de linhas e colunas da matriz*/
  int i,j;
  int **m = (int**)malloc(Tam * sizeof(int*)); /*Aloca um vetor de ponteiros*/
  if(!m){ /*Verifico se a memória foi alocada para as linhas*/
    printf("Erro: Nao foi possível alocar memória.\n");
    exit(1);
  }
  for (i = 0; i < Tam; i++){
       m[i] = (int*) malloc(Tam * sizeof(int)); /*Aloca um vetor de inteiros para cada posição do vetor de ponteiros.*/
       if(!m[i]){ /*Verifico se a memória foi alocada para as colunas*/
         printf("Erro: Nao foi possível alocar memória.\n");
         exit(1);
       }
       for (j = 0; j < Tam; j++){
            m[i][j] = 0; /*inicializa com 0.*/
       }
  }
return m; /*Retorna o ponteiro para a matriz alocada*/
}

void geraMatriz(int **M, int Tam){ /*Recebo o endereço da matriz que será gerada*/
  int i,j;
  for(i = 0; i<Tam; i++){
    for(j = 0; j<Tam; j++){
      M[i][j]= rand()%100;/*Gera números aleatórios para cada posição da matriz.*/
    }
  }
}

void printMatriz(int **M, int Tam){ /*Recebo o endereço da matriz que será impressa.*/
  int i, j;
  for(i = 0; i<Tam; i++){
    for(j = 0; j<Tam; j++){
      printf("%d ", M[i][j]); /*Printa cada poisição a Matriz.*/
    }
    printf("\n");
  }
  printf("\n\n");
}

void multiplicarMatriz(int **A, int **B, int **C, int Tam){ /*Recebo endereço das 2 matrizes que serão multiplicadas pelo método "tradicional" e o endereço da matriz que receberá o resultado.*/
  int i, j, k;
  for(i = 0; i<Tam; i++){
    for(j = 0; j<Tam; j++){
      C[i][j] = 0;
      for(k = 0; k<Tam; k++){
        C[i][j] += A[i][k]*B[k][j]; /*Faço a multiplicação de Matrizes.*/
      }
    }
  }
}

void soma(int **A, int **B, int **C, int Tam){ /*Recebo o endereço das 2 matrizes que serão somadas.*/
  int i,j;
  for(i=0; i<Tam; i++){
    for(j=0; j<Tam; j++){
      C[i][j] = A[i][j]+B[i][j]; /*Faço a soma de cada posição das matrizes.*/
    }
  }
}

void subtracao(int **A, int **B, int **C, int Tam){ /*Recebo o endereço das 2 matrizes que serão subtraídas.*/
  int i,j;
  for(i=0; i<Tam; i++){
    for(j=0; j<Tam; j++){
      C[i][j] = A[i][j]-B[i][j]; /*Faço a subtração de cada posição das matrizes.*/
    }
  }
}

void liberamemoria(int **A, int Tam){ /*Recebo o endereço da Matriz que será liberada da memória e o tamanho da mesma.*/
	int i;
	for(i=0; i<Tam; i++){
		free(A[i]); /*Primeiro libero cada uma das colunas.*/
	}
	free(A); /*Aqui libero as linhas.*/
}

void algoritmoDeStrassen(int **A, int **B, int **D, int Tam){ /*Recebo endereço das 2 matrizes que serão multiplicadas pelo método de Strassen, o endereço da matriz que receberá o resultado e o tamanho*/

  int i, j;
  int newTam = Tam/2;

  if(Tam == 1){ /*Caso Base*/
      D[0][0] = A[0][0] * B[0][0];
      return;
    }

    int **A11 = alocarMatriz(newTam);
    int **A12 = alocarMatriz(newTam);
    int **A21 = alocarMatriz(newTam);
    int **A22 = alocarMatriz(newTam);
    int **B11 = alocarMatriz(newTam);
    int **B12 = alocarMatriz(newTam);
    int **B21 = alocarMatriz(newTam);
    int **B22 = alocarMatriz(newTam);
	  int **C11 = alocarMatriz(newTam);
	  int **C12 = alocarMatriz(newTam);
	  int **C21 = alocarMatriz(newTam);
	  int **C22 = alocarMatriz(newTam);
    int **M1 = alocarMatriz(newTam);
    int **M2 = alocarMatriz(newTam);
    int **M3 = alocarMatriz(newTam);
    int **M4 = alocarMatriz(newTam);
    int **M5 = alocarMatriz(newTam);
    int **M6 = alocarMatriz(newTam);
    int **M7 = alocarMatriz(newTam);
	  int **aux1 = alocarMatriz(newTam); /*aux1 e aux2 são usadas nos processos de soma e subtração, uma vez que preciso guardar tais endereços para serem liberados*/
	  int **aux2 = alocarMatriz(newTam);

    /*Gero cada um dos pedaços da Matriz A e da Matriz B*/
    for(i = 0; i<newTam; i++){
      for(j = 0; j<newTam; j++){
        A11[i][j] = A[i][j];
        A12[i][j] = A[i][newTam+j];
        A21[i][j] = A[newTam+i][j];
        A22[i][j] = A[newTam+i][newTam+j];

        B11[i][j] = B[i][j];
        B12[i][j] = B[i][newTam+j];
        B21[i][j] = B[newTam+i][j];
        B22[i][j] = B[newTam+i][newTam+j];
      }
    }

  soma(A11,A22,aux1,newTam);
  soma(B11,B22,aux2,newTam);
  algoritmoDeStrassen(aux1,aux2,M1,newTam); /*M1 = (A[0][0] + A[1][1])*(B[0][0] + B[1][1]);*/

  soma(A21,A22,aux1,newTam);
  algoritmoDeStrassen(aux1,B11,M2,newTam); /* M2 = (A[1][0] + A[1][1])*B[0][0];*/

  subtracao(B12,B22,aux1,newTam);
  algoritmoDeStrassen(A11,aux1,M3,newTam); /*M3 = A[0][0]*(B[0][1] - B[1][1]);*/

  subtracao(B21,B11,aux1,newTam);
  algoritmoDeStrassen(A22,aux1,M4,newTam); /*M4 = A[1][1]*(B[1][0]-B[0][0]);*/

  soma(A11,A12,aux1,newTam);
  algoritmoDeStrassen(aux1,B22,M5,newTam); /*M5 = (A[0][0] + A[0][1])*B[1][1];*/

  subtracao(A21,A11,aux1,newTam);
  soma(B11,B12,aux2,newTam);
  algoritmoDeStrassen(aux1,aux2,M6,newTam); /*M6 = (A[1][0] - A[0][0])*(B[0][0] + B[0][1]);*/

  subtracao(A12,A22,aux1,newTam);
  soma(B21,B22,aux2,newTam);
  algoritmoDeStrassen(aux1,aux2,M7,newTam); /*M7 = (A[0][1] - A[1][1])*(B[1][0] + B[1][1]);*/

  soma(M1,M4,aux1,newTam);
  soma(aux1,M7,aux2,newTam);
  subtracao(aux2,M5,C11,newTam); /*C11 = M1+M4+M7-M5*/

  soma(M2,M4,C21,newTam); /*C21 = M2+M4*/

  soma(M3,M5,C12,newTam); /*C12 = M3 + M5*/

  soma(M1,M3,aux1,newTam);
  soma(aux1,M6,aux2,newTam);
  subtracao(aux2,M2,C22,newTam);  /*C22 = M1+M3+M6-M2*/

  /*Montagem do Resultado apartir dos C's*/
  for(i = 0; i<newTam; i++){
    for(j = 0; j<newTam; j++){
        D[i][j] = C11[i][j];
        D[i][newTam+j] = C12[i][j];
        D[newTam+i][j] = C21[i][j];
        D[newTam+i][newTam+j] = C22[i][j];
    }
  }

  /*Libero memória*/
  liberamemoria(aux1,newTam);
  liberamemoria(aux2,newTam);
  liberamemoria(A11,newTam);
  liberamemoria(A21,newTam);
  liberamemoria(A12,newTam);
  liberamemoria(A22,newTam);
  liberamemoria(B11,newTam);
  liberamemoria(B21,newTam);
  liberamemoria(B12,newTam);
  liberamemoria(B22,newTam);
  liberamemoria(C11,newTam);
  liberamemoria(C21,newTam);
  liberamemoria(C12,newTam);
  liberamemoria(C22,newTam);
  liberamemoria(M1,newTam);
  liberamemoria(M2,newTam);
  liberamemoria(M3,newTam);
  liberamemoria(M4,newTam);
  liberamemoria(M5,newTam);
  liberamemoria(M6,newTam);
  liberamemoria(M7,newTam);

}
