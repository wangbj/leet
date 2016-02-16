#include <stdlib.h>
#include <stdio.h>

#define assert(x)

struct NumMatrix {
  int** mtx;
  long long** sums;
  long long** rowsums;
  int rows;
  int cols;
};

static void NumMatrixGenRowColSums(struct NumMatrix* mtx)
{
  int i, j;

  for (i = 0; i < mtx->rows; i++) {
    for (j = 0; j < mtx->cols; j++) {
      mtx->rowsums[i][1 + j] = mtx->rowsums[i][j] + mtx->mtx[i][j];
    }
  }
}

/** Initialize your data structure here. */
struct NumMatrix* NumMatrixCreate(int** matrix, int matrixRowSize, int matrixColSize) {
  int i, j;
    
  struct NumMatrix* M = (struct NumMatrix*)calloc(1, sizeof(struct NumMatrix));
  assert(M);
    
  M -> rows = matrixRowSize;
  M -> cols = matrixColSize;
    
  M -> mtx = (int**)calloc(1 + matrixRowSize, sizeof(int*));
  assert(M -> mtx);
  M -> sums = (long long**)calloc(1 + matrixRowSize, sizeof(long long*));
  assert(M -> sums);
    
  M -> rowsums = (long long**)calloc(1 + matrixRowSize, sizeof(long long*));
  assert (M -> rowsums);
    
  for (i = 0; i <= matrixRowSize; i++) {
    M->mtx[i] = (int*)calloc(1 + matrixColSize, sizeof(int));
    assert(M->mtx[i]);
    M->sums[i] = (long long*)calloc(1 + matrixColSize, sizeof(long long));
    assert(M->sums[i]);
    M->rowsums[i] = (long long*)calloc(1 + matrixColSize, sizeof(long long));
    assert(M->rowsums[i]);
  }

  /* copy matrix */
  for (i = 0; i < matrixRowSize; i++) {
    for (j = 0; j < matrixColSize; j++) {
      M->mtx[i][j] = matrix[i][j];
    }
  }

  /* generate sums for corner cases */
  for (i = 0; i < M->cols; i++) {
    M->sums[1][1 + i] = M->sums[1][i] + M->mtx[0][i];
    M->rowsums[1][1 + i] = M->sums[1][1+i];
  }

  /* generate sums for corner cases */
  for (i = 0; i < M->rows; i++) {
    M->sums[1 + i][1] = M->sums[i][1] + M->mtx[i][0];
  }

  NumMatrixGenRowColSums(M);

  for (i = 2; i <= M->rows; i++) {
    for (j = 2; j <= M->cols; j++) {
      M->sums[i][j] = M->sums[i-1][j] + M->rowsums[i-1][j];
    }
  }
  
  return M;
}

int sumRegion(struct NumMatrix* numMatrix, int row1, int col1, int row2, int col2) {
  long long total = numMatrix->sums[1+row2][1+col2];
  long long left = numMatrix->sums[1+row2][col1];
  long long up = numMatrix->sums[row1][1+col2];
  long long corner = numMatrix->sums[row1][col1];

  return total + corner - left - up;
}

/** Deallocates memory previously allocated for the data structure. */
void NumMatrixFree(struct NumMatrix* numMatrix) {
  int i;
  
  if (numMatrix) {
    for (i = 0; i <= numMatrix->rows; i++) {
      free(numMatrix->rowsums[i]);
      free(numMatrix->sums[i]);
      free(numMatrix->mtx[i]);      
    }
    free(numMatrix->rowsums);
    free(numMatrix->sums);
    free(numMatrix->mtx);

    free(numMatrix);
  }
}

// Your NumMatrix object will be instantiated and called as such:
// struct NumMatrix* numMatrix = NumMatrixCreate(matrix, matrixRowSize, matrixColSize);
// sumRegion(numMatrix, 0, 1, 2, 3);
// sumRegion(numMatrix, 1, 2, 3, 4);
// NumMatrixFree(numMatrix);
