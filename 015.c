#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int defaultcmp(const void* l, const void* r)
{
  int x = *(int*)l;
  int y = *(int*)r;

  return x - y;
}

int binarysearch(int* v, int i, int j, int x)
{
  while(i <= j) {
    int k = (i+j) / 2;

    if (v[k] == x) return k;
    else if (v[k] > x) j = k - 1;
    else i = k + 1;
  }
  return -1;
}

struct tuple3 {
  int **elems;
  int size;
  int size_allocated;
};

void push(struct tuple3* t, int x, int y, int z)
{
  int i;
  
  if (t->size >= t->size_allocated) {
    t->size_allocated += 128;
    t -> elems = (int**)realloc(t->elems, t->size_allocated * sizeof(int*));
    for (i = t->size; i < t->size_allocated; i++) {
      t->elems[i] = (int*)calloc(3, sizeof(int));
    }
    t->elems[t->size][0] = x;
    t->elems[t->size][1] = y;
    t->elems[t->size][2] = z;
  } else {
    t->elems[t->size][0] = x;
    t->elems[t->size][1] = y;
    t->elems[t->size][2] = z;
  }
  ++t->size;
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** threeSum(int* v, int size, int* retsize) {
  struct tuple3 t;
  qsort(v, size, sizeof(int), defaultcmp);
  int i, j, k, x;

  if (size < 3) {
    if (retsize) *retsize = 0;
    return NULL;
  }

  memset(&t, 0, sizeof(struct tuple3));

  for (i = 0; i < size - 2; i++) {
    while (i > 0 && v[i] == v[i-1]) ++i;
    for (j = size-1; j >= i+2; j--) {
      while(j < size -1 && v[j] == v[j+1]) --j;
      
      k = -(v[i] + v[j]);
      x = binarysearch(v, 1+i, j-1, k);
      if (x != -1) {
	push(&t, v[i], k, v[j]);	
      }
    }
  }

  if (retsize) *retsize = t.size;
  return t.elems;
}

#define ARRAY_SIZE(arr) ( (sizeof(arr)) / sizeof((arr)[0]) )

int main(int argc, char* argv[])
{
  int arr[] = {-4,-2,1,-5,-4,-4,4,-2,0,4,0,-2,3,1,-5,0};
  int** r, n, i;

  r = threeSum(arr, ARRAY_SIZE(arr), &n);

  for (i = 0; i < n; i++) {
    printf("%d %d %d\n", r[i][0], r[i][1], r[i][2]);
  }

  return 0;
}
