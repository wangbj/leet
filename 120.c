#define minBound 0x80000000
#define maxBound 0x7fffffff

struct Pair {
  int x;
  int y;
};

int prev(int** t, int rows, int* cols, int i, int j, struct Pair* pair)
{
  int k = 0;

  if (j-1 >= 0 && j-1<cols[i-1]) {
    pair[k].x = i - 1;
    pair[k].y = j - 1;
    ++k;
  }

  if (j < cols[i-1]) {
    pair[k].x = i - 1;
    pair[k].y = j;
    ++k;
  }

  return k;
}

static inline int maximum(int* arr, int n)
{
  int r = minBound;
  int i;

  for (i = 0; i < n; i++) {
    if (arr[i] > r) r = arr[i];
  }

  return r;
}

static inline int minimum(int* arr, int n)
{
  int r = maxBound;
  int i;

  for (i = 0; i < n; i++) {
    if (arr[i] < r) r = arr[i];
  }

  return r;
}

int** alloc2d(int rows, int cols)
{
  int** res;
  int i;
  
  if (!rows || !cols) return NULL;

  res = (int**)calloc(1 + rows, sizeof(int*));
  for (i = 0; i < rows; i++) {
    res[i] = (int*)calloc(1+cols, sizeof(int));
  }

  return res;
}

void free2d(int** arr, int rows, int cols)
{
  int i;

  for (i = 0; i < rows; i++) {
    free(arr[i]);
  }
  free(arr);
}

int minimumTotal(int** triangle, int triangleRowSize, int *triangleColSizes)
{
  int maxCols = maximum(triangleColSizes, triangleRowSize);
  struct Pair last[2];
  int x, y;
  int k, n, t;
  
  int** cache = alloc2d(triangleRowSize, maxCols);
  int i, j;

  for (i = 0; i < triangleColSizes[0]; i++) {
    cache[0][i] = triangle[0][i];
  }
  
  for (i = 1; i < triangleRowSize; i++) {
    for (j = 0; j < triangleColSizes[i]; j++) {
      n = prev(triangle, triangleRowSize, triangleColSizes, i, j, last);
      t = maxBound;      
      for (k = 0; k < n; k++) {
	x = last[k].x;
	y = last[k].y;
	if (cache[x][y] < t) {
	  t = cache[x][y];
	}
      }
      cache[i][j] = triangle[i][j] + t;
    }
  }

  t = minimum(cache[triangleRowSize-1], triangleColSizes[triangleRowSize-1]);
  
  free2d(cache, triangleRowSize, maxCols);
  
  return t;
}
