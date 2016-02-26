#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int kmpPrefix(const char* s, int* v)
{
  int i = 0, j = 1;

  if (*s == '\0') return 0;

  v[0] = 0;
  while(s[j] != '\0') {
    if (s[i] == s[j]) {
      v[j++] = ++i;
    } else {
      if (i == 0) {
	v[j++] = 0;
      } else {
	i = v[i-1];
      }
    }
  }
  return j;
}

int kmpMatch(const char* s, const char* t, int len)
{
  int* prefix;
  int prefix_size;
  int i = 0, j = 0;

  prefix = (int*)calloc(sizeof(int), 1+len);
  
  prefix_size = kmpPrefix(t, prefix);

  while(s[i] != '\0') {
    if (s[i] == t[j]) {
      ++i;
      ++j;
    } else {
      if (j == 0) {
	++i;
      } else {
	j = prefix[j-1];
      }
    }
    if (j >= prefix_size) break;
  }

  free(prefix);
  
  return j;
}

void reverse(char* s, int len)
{
  int i;
  char ch;
  for (i = 0; i < len/2; i++) {
    ch = s[i];
    s[i] = s[len-i-1];
    s[len-i-1] = ch;
  }
}

char* shortestPalindrome(char* s)
{
  char* p, *t;
  int i;
  
  if (!s) return NULL;
  
  int len = strlen(s);

  t = strdup(s);
  reverse(t, len);

  i = kmpMatch(t, s, len);

  p = (char*)calloc(1, 2*len+1);
  strncpy(p, t, len);
  strncpy(p+len, s+i, len-i);
  free(t);
  
  return p;
}

int main(int argc, char* argv[])
{
  if (argc == 2) {
    printf("%s\n", shortestPalindrome(argv[1]));
  }
  return 0;
}
