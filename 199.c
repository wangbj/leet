#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef TEST
/**
 * Definition for a binary tree node.
 */

struct TreeNode {
  int val;
  struct TreeNode *left;
  struct TreeNode *right;
};

#endif

struct TreeNodeLabeled {
  int label;
  struct TreeNode* node;
};

#define MAXQ 8192

typedef struct TreeNodeLabeled* queue_element_t;

struct queue {
  queue_element_t queue[MAXQ];
  int head, tail;
};

struct TreeNodeLabeled* labNode(struct TreeNode* node, int label)
{
  struct TreeNodeLabeled* lab = (struct TreeNodeLabeled*)calloc(1, sizeof(struct TreeNodeLabeled));
  lab->label = label;
  lab->node = node;
  return lab;
}

static void push_back(struct queue* Q, queue_element_t x)
{
  Q->queue[Q->tail++] = x;

  if (Q->tail >= MAXQ) Q->tail = 0;
}

static int empty(struct queue* Q)
{
  return Q->head == Q->tail;
}

static int queue_size(struct queue* Q)
{
  if (Q->tail > Q->head) {
    return Q->tail - Q->head;
  } else {
    return MAXQ - Q->head + Q->tail;
  }
}

static queue_element_t pop_front(struct queue* Q)
{
  queue_element_t x = Q->queue[Q->head++];

  if (Q->head >= MAXQ) Q->head = 0;

  return x;
}

struct vector {
  int* vect;
  int size;
  int size_allocated;
};

#define BLKSIZ 256

void push(struct vector* v, int x)
{
  if (v->size >= v->size_allocated) {
    v->size_allocated += BLKSIZ;
    v->vect = realloc(v->vect, v->size_allocated*sizeof(int));
  }
  v->vect[v->size++] = x;  
}

void bfs(struct queue* Q, struct vector* vect)
{
  struct TreeNodeLabeled* t, *l, *r;
  int next;
  
  if (empty(Q)) return;

  t = pop_front(Q);

  if (t->label > vect->size) {
    push(vect, t->node->val);
  }

  next = 1 + t->label;
  if (t->node->right) {
    r = labNode(t->node->right, next);
    push_back(Q, r);
  }
  
  if (t->node->left) {
    l = labNode(t->node->left, next);
    push_back(Q, l);
  }

  free(t);
  
  bfs(Q, vect);
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* size)
{
  if (!root) return NULL;
  struct vector vect;
  struct queue Q;
  struct TreeNodeLabeled* labeled;
  
  memset(&vect, 0, sizeof(struct vector));
  memset(&Q, 0, sizeof(struct queue));

  labeled = labNode(root, 1);
  push_back(&Q, labeled);

  bfs(&Q, &vect);

  if (size) *size = vect.size;
  return vect.vect;
}
