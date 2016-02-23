#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef TEST
#include <assert.h>
#else
#define assert(x)
#endif

static inline int parent(int x)
{
  return x & (x-1);
}

static inline int next(int x)
{
  return x + (x & (-x));
}

struct NumArray {
  int* nums;
  int size;
  long* vect;
};

/** Initialize your data structure here. */
struct NumArray* NumArrayCreate(int* nums, int numsSize) {
  struct NumArray* arr = (struct NumArray*)calloc(1, sizeof(struct NumArray));
  int i, j;

  assert(arr);
  arr -> size = numsSize;
  arr -> nums = (int*)calloc(sizeof(int), 1 + numsSize);
  assert(arr->nums);
  arr -> vect = (long*)calloc(sizeof(long), 1 + numsSize);
  assert(arr->vect);

  memcpy(arr->nums, nums, numsSize * sizeof(int));

  for (i = 0; i < numsSize; i++) {
    j = 1 + i;
    while (j <= numsSize) {
      arr->vect[j] += nums[i];
      // printf("vect[%d] = %ld\n", j, arr->vect[j]);
      j = next(j);      
    }
  }

  return arr;
}

void update(struct NumArray* numArray, int i, int val) {
  int j = 1 + i;

  int x = val - numArray->nums[i];
  numArray->nums[i] = val;

  while (j <= numArray->size) {
    numArray->vect[j] += x;
    // printf("update vect[%d] = %ld\n", j, numArray->vect[j]);
    j = next(j);
  }
}

int sumUpto(struct NumArray* numArray, int i)
{
  int j = 1 + i;
  int sum = 0;
  
  while (j > 0) {
    sum += numArray->vect[j];
    j = parent(j);
  }
  return sum;
}

int sumRange(struct NumArray* numArray, int i, int j) {
  if (j < i) return sumRange(numArray, j, i);
  if (i == 0) return sumUpto(numArray, j);

  int s1 = sumUpto(numArray, i-1);
  int s2 = sumUpto(numArray, j);

  return s2 - s1;
}

/** Deallocates memory previously allocated for the data structure. */
void NumArrayFree(struct NumArray* numArray) {
  if (numArray) {
    free(numArray->nums);
    free(numArray->vect);
    free(numArray);
  }
}

// Your NumArray object will be instantiated and called as such:
// struct NumArray* numArray = NumArrayCreate(nums, numsSize);
// sumRange(numArray, 0, 1);
// update(numArray, 1, 10);
// sumRange(numArray, 1, 2);
// NumArrayFree(numArray);
