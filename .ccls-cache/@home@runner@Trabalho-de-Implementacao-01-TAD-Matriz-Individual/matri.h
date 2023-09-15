//  Implementar o TAD Matriz (int)

// - Implementar o programa Apl.c com um menu coim as seguintes funcionalidades:
// --- Criar  a matriz A
// --- Criar  a matriz B
// --- Ler e inserir os dados da matriz A
// --- Ler e inserir os dados da matriz B
// --- Calcular a multiplicação de A por B sefor possível e eimprimir o
// resultado
// --- Calcular a transposta de A  e imprimir o resultado
// --- Calcular a transposta de B  e imprimir o resultado
// --- Destruir a matriz A
// --- Destruir a matriz B

// Entrega:
// - Upload dos arquivos apl.c matriz.h e matriz.c e do arquivo executável / se
// for no replit compartilha o link pra executarmos
#ifndef __MATRIZ_H
#define __MATRIZ_H

typedef struct matriz Matriz;

int *criarMatrix(int n, int m);

int **lerMatrix(Matriz *mat, int n, int m);

int inserirDados(Matriz *mat, int valor);

int *TornarTransposta(Matriz *mat);

int *multiplicar(Matriz *ma, int *mb);

int destruirMatriz(Matriz *mat);

#endif