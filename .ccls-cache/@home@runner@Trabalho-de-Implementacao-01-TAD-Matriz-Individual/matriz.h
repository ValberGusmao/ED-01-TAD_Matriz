#ifndef __MATRIZ_H
#define __MATRIZ_H
#define TRUE 1
#define FALSE 0
#define INT_ERR -2147483648

typedef struct matriz Matriz;

// Pede uma Matriz para verifcar sua quantidade de linhas
// Retorna seu número de linhas
int numeroLinhas(Matriz *mat);

// Pede uma Matriz para verifcar sua quantidade de colunas
// Retorna seu número de colunas
int numeroColunas(Matriz *mat);

// Pede a quantidade de linhas e colunas para criar uma Matriz
// Se conseguir criar, retornar a Matriz
// senão, retorna NULL
Matriz *criarMatrix(int n, int m);

// Pede a Matriz e a posicao na matriz (linha e coluna) para acessar uma valor
// nessa posição Se existir, retorna o valor localizado nessa posição Senão,
// retorna INT_ERR
int lerMatrix(Matriz *mat, int n, int m);

// Pede uma Matriz, a posicao na matriz (linha e coluna) e um valor para poder
// alterar o dado nessa posicao. Se o valor foi alterado, retorna TRUE Senão,
// retorna FALSE
int inserirDados(Matriz *mat, int n, int m, int valor);

// Pede uma Matriz para encontrar sua transposta
// Se conseguir transformar, retorna a matriz transposta
// Senão, retorna NULL
Matriz *tornarTransposta(Matriz *mat);

// Pede duas Matriz para poder multiplicar
// Se conseguir multiplicar, retorna o resultado
// Senão, retorna NULL
Matriz *multiplicarMatriz(Matriz *ma, Matriz *mb);

// Pede uma Matriz para destruir
// Se a matriz foi destruida, retorna TRUE
// Senão, retorna FALSE
int destruirMatriz(Matriz *mat);

#endif