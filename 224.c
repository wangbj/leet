#include <string.h>
#include <stdio.h>

#define STACK_SIZE 1024

static int parens[STACK_SIZE];
static int parens_head = 0;

static int eval(char* s)
{
  int i, x, acc = 0;
  char* p;
  int status = 0;
  int sign = 1;

  for (i = 0; i < STACK_SIZE; i++) {
    parens[i] = 1;
  }

  while (*s != '\0') {
    if (*s == ' ' || *s == '\t') {
      ++s;
    } else if (*s == '(') {
      ++parens_head;
      if (sign == 1) {
	parens[parens_head] = parens[parens_head-1];
      } else {
	parens[parens_head] = -parens[parens_head-1];
      }
      sign = 1;
      ++s;
    } else if (*s == '+') {
      sign = 1;
      ++s;
    } else if (*s == '-') {
      sign = -1;
      ++s;
    } else if (*s == ')') {
      --parens_head;
      ++s;
    } else {
      x = strtoul(s, &p, 10);
      s = p;
      if (sign != parens[parens_head]) {
	acc -= x;
      } else {
	acc += x;
      }
    }
  }
  return acc;
}

int calculate(char* s)
{
  return eval(s);
}
