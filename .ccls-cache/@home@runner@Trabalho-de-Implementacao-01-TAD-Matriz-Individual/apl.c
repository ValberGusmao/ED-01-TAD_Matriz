#include "matriz.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMITEMATRIZES 5
#define SEPARADOR "------------------------------------\n"

/* As funções entrada servem para impedir que o
usuário passe um valor inválido para o programa*/

/* Pede para o usuário entrar com um valor determinado,
se o valor for inválido a função pede novamente,
repetindo até ser válido. */
/* Um valor válido é aquele que é igual, ou está entre
os pararametros min e max */
// Retorna a entrada válida
char entradaChar(char min, char max);

/* Pede para o usuário entrar com um int, se não for um número
a função pede novamente, repetindo até ser válido*/
// Retorna a entrada válida
int entradaInt();

// Pede uma Matriz para mostra todos os seus elementos
// Se existir a Matriz, retorna TRUE
// Senão, retorna FALSE
int exibirMatriz(Matriz *mat);

//---------------------------------------------------------------------
// As funções menu servem apenas para organizar a interface do programa
void menuIniciar();
void menuCriar();
void menuAcessar();
void menuEditar();
void menuTransposta();
void menuDestruir();
void menuMultiplicar();
void menuSalvar(Matriz *mAux);
//---------------------------------------------------------------------

// Essas variáveis são globais, porque todas as funções menu as utilizam
char entChar;
int entInt, quantMat = 0;
Matriz **matrizes;

int main(void) {
  matrizes = (Matriz **)malloc(sizeof(Matriz *) * LIMITEMATRIZES);

  printf("\nTAD DE MATRIZ:\n");
  do {
    menuIniciar();
    switch (entChar) {
    case 'a':
      if (quantMat < LIMITEMATRIZES) {
        menuCriar();
      } else {
        printf("\nOPERACAO INVALIDA!\nO LIMITE DE MATRIZES FOI ATINGIDO\n");
      }
      break;
    case 'b':
      if (quantMat > 0) {
        menuAcessar();
      } else {
        printf("\nOPERACAO INVALIDA!\nNENHUMA MATRIZ FOI CRIADA\n");
      }
      entChar = 'b';
      break;
    case 'c':
      if (quantMat > 0) {
        menuMultiplicar();
      } else {
        printf("\nOPERACAO INVALIDA!\nNENHUMA MATRIZ FOI CRIADA\n");
      }
      break;
    }
  } while (entChar != 'd');
  return 0;
}

void menuIniciar() {
  printf("\n%s", SEPARADOR);
  printf("\n - Menu - \n\n");
  printf("a - Criar Matriz\n");
  printf("b - Acessar Matriz\n");
  printf("c - Multiplicar Matriz\n");
  printf("d - SAIR\n");
  printf("\nQuantidade de Matrizes criadas (%d/%d)\n", quantMat,
         LIMITEMATRIZES);

  entChar = entradaChar('a', 'd');
  printf(SEPARADOR);
}

void menuCriar() {
  Matriz *mAux;
  int l, c;

  printf("Insira o numero de linhas da matriz: \n");
  l = entradaInt();
  printf("Insira o numero de colunas da matriz: \n");
  c = entradaInt();
  mAux = criarMatrix(l, c);

  if (mAux != NULL) {
    matrizes[quantMat] = mAux;
    printf("\n%s", SEPARADOR);
    printf("\nMatriz ||%d|| \n", quantMat);
    printf("ADICIONADA com SUCESSO (%dx%d)\n\n", l, c);
    printf("Adicione os valores para a Matriz:\n");

    for (int i = 0; i < l; i++) {
      for (int j = 0; j < c; j++) {
        printf("|%d-%d| \n", i, j);
        entInt = entradaInt();
        inserirDados(matrizes[quantMat], i, j, entInt);
      }
    }
    quantMat += 1;
  } else {
    printf("\nERRO ao ADICIONAR a matriz");
  }
}

void menuAcessar() {
  printf("Digite o número da matriz:\n");
  entInt = entradaInt();
  if (entInt >= 0 && entInt < quantMat) {
    do {
      printf("\nMatriz |%d|\n", entInt);
      exibirMatriz(matrizes[entInt]);
      printf("\na - Inserir Dados\n");
      printf("b - Transposta da Matriz\n");
      printf("c - Destruir Matriz\n");
      printf("d - Voltar\n\n");
      entChar = entradaChar('a', 'd');

      if (entChar != 'd') {
        switch (entChar) {
        case 'a':
          menuEditar(matrizes, entInt);
          break;
        case 'b':
          menuTransposta(matrizes, entInt);
          break;
        case 'c':
          menuDestruir(matrizes, entInt, *&quantMat);
          entChar = 'd';
          break;
        }
      }
    } while (entChar != 'd');
  } else {
    printf("\n--ESSA MATRIZ NÃO EXISTE--\n");
  }
}

void menuEditar() {
  int l, c, valor;
  printf("\n%s", SEPARADOR);
  printf("\nNumero da linha:\n");
  l = entradaInt();
  printf("Numero da coluna:\n");
  c = entradaInt();
  printf("Valor:\n");
  valor = entradaInt();
  if (inserirDados(matrizes[entInt], l, c, valor)) {
    printf("VALOR INSERIDO COM SUCESSO\n");
  } else {
    printf("ERRO AO INSERIR VALOR\n");
  }
  printf(SEPARADOR);
}

void menuTransposta() {
  Matriz *mAux = tornarTransposta(matrizes[entInt]);
  if (mAux != NULL) {
    menuSalvar(mAux);
  }
}

void menuMultiplicar() {
  Matriz *mAux;

  printf("Digite o número da primeira matriz:\n");
  entInt = entradaInt();

  if (entInt >= 0 && entInt < quantMat) {
    mAux = matrizes[entInt];
    printf("Digite o número da segunda matriz:\n");
    entInt = entradaInt();

    if (entInt >= 0 && entInt < quantMat) {
      mAux = multiplicarMatriz(mAux, matrizes[entInt]);

      if (mAux != NULL) {

        menuSalvar(mAux);
        return;
      } else {
        printf("ERRO AO MULTIPLICAR A MATRIZ");
      }
    }
  }
}

void menuDestruir() {
  if (destruirMatriz(matrizes[entInt])) {
    printf("\nMatriz DESTRUIDA com SUCESSO\n");
    for (int i = entInt; i < quantMat; i++) {
      matrizes[i] = matrizes[i + 1];
    }
    quantMat -= 1;
  } else {
    printf("\nERRO ao DESTRUIR a matriz\n");
  }
}

void menuSalvar(Matriz *mAux) {
  int entradaAnterior = entInt;
  printf("\n%s\n", SEPARADOR);
  exibirMatriz(mAux);
  do {
    printf("\nDigite onde salvar a matriz: (0~%d)", quantMat);
    printf("\nPara não salvar digite (-1): \n");
    entInt = entradaInt();
  } while (entInt < -1 || entInt > quantMat);
  if (entInt != -1) {
    matrizes[entInt] = mAux;
    printf("\nMatriz Salva com Sucesso\n");

    if (entInt == quantMat) {
      quantMat += 1;
    }
  } else {
    printf("\nA Matriz Não foi salva\n");
    entInt = entradaAnterior;
  }
}

char entradaChar(char min, char max) {
  char entrada[20];
  char saida;
  do {
    printf("DIGITE-> ");
    scanf(" %s", entrada);
    if (strlen(entrada) == 1) {
      saida = tolower(entrada[0]);
    } else {
      saida = ' ';
    }
  } while (saida == ' ' || saida < tolower(min) || saida > tolower(max));
  return saida;
}

int entradaInt() {
  char entrada[20];
  int saida;
  do {
    printf("DIGITE-> ");
    scanf(" %s", entrada);
    if (strlen(entrada) == 1 && entrada[0] == '0') {
      return 0;
    } else {
      saida = atoi(entrada);
    }
  } while (saida == 0);
  return saida;
}

int exibirMatriz(Matriz *mat) {
  if (mat != NULL) {
    for (int i = 0; i < numeroLinhas(mat); i++) {
      printf("| ");
      for (int j = 0; j < numeroColunas(mat); j++) {
        printf("%d ", lerMatrix(mat, i, j));
      }
      printf("|\n");
    }
    return TRUE;
  }
  return FALSE;
}