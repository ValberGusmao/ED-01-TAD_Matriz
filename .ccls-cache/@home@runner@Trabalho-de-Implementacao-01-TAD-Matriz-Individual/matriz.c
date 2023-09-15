#include "matriz.h"
#include <stdlib.h>

struct matriz {
  int lin;
  int col;
  int *vMat;
};

int numeroLinhas(Matriz *mat) {
  if (mat != NULL) {
    return mat->lin;
  }
  return INT_ERR;
}
int numeroColunas(Matriz *mat) {
  if (mat != NULL) {
    return mat->col;
  }
  return INT_ERR;
}

Matriz *criarMatrix(int n, int m) {
  Matriz *mat;
  if (n > 0 && m > 0) {
    mat = (Matriz *)malloc(sizeof(Matriz));
    if (mat != NULL) {
      mat->lin = n;
      mat->col = m;
      mat->vMat = (int *)malloc(sizeof(int) * (n * m));
      if (mat->vMat != NULL) {
        return mat;
      }
      free(mat);
    }
  }
  return NULL;
}

int lerMatrix(Matriz *mat, int n, int m) {
  if (mat != NULL) {
    if (n >= 0 && m >= 0) {
      return mat->vMat[mat->col * n + m];
    }
  }
  return INT_ERR;
}

int inserirDados(Matriz *mat, int n, int m, int valor) {
  if (mat != NULL) {
    if (n >= 0 && m >= 0) {
      if (n < mat->lin && m < mat->col) {
        mat->vMat[mat->col * n + m] = valor;
        return TRUE;
      }
    }
  }
  return FALSE;
}

Matriz *tornarTransposta(Matriz *mat) {
  Matriz *auxMat;
  if (mat != NULL) {
    auxMat = criarMatrix(mat->col, mat->lin);
    if (auxMat != NULL) {
      for (int i = 0; i < mat->lin; i++) {
        for (int j = 0; j < mat->col; j++) {
          auxMat->vMat[auxMat->col * j + i] = mat->vMat[mat->col * i + j];
        }
      }
      return auxMat;
    }
  }
  return NULL;
}

Matriz *multiplicarMatriz(Matriz *ma, Matriz *mb) {
  Matriz *mc;
  if (ma != NULL && mb != NULL) {
    if (ma->col == mb->lin) {
      mc = criarMatrix(ma->lin, mb->col);
      if (mc != NULL) {
        for (int i = 0; i < ma->lin; i++) {
          for (int j = 0; j < mb->col; j++) {
            mc->vMat[mc->col * i + j] = 0;
            for (int k = 0; k < ma->col; k++) {
              mc->vMat[mc->col * i + j] +=
                  ma->vMat[ma->col * i + k] * mb->vMat[mb->col * k + j];
            }
          }
        }
        return mc;
      }
    }
  }
  return NULL;
}

int destruirMatriz(Matriz *mat) {
  if (mat != NULL) {
    free(mat->vMat);
    free(mat);
    return TRUE;
  }
  return FALSE;
}