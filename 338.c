/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countBits(int num, int* size) {
  int *v, i, j;
  
  v = (int*)calloc(1+num, sizeof(int));
  v[0] = 0;

  for (i = 1; i <= num; i++) {
    int x = i >> 1;
    int y = i & 1;
    v[i] = v[x] + y;
  }
  if (size) *size = 1+num;

  return v;
}
