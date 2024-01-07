#include <stdio.h>

#define MAXLENGTH 10

void reverse(char *s, char *r);

int main() {
  char c;
  char s[MAXLENGTH] = {0};
  char r[MAXLENGTH] = {0};
  int i, res, val;
  for (i = 0; (c = getchar()) != EOF && (i < MAXLENGTH); i++) {
    s[i] = c;
  }
  reverse(s, r);
  printf("%s -> %s\n", s, r);
  return 0;
  
}

void reverse(char *s, char *r) {
  int i, length;
  char tmp;
  for (i = 0; s[i] != '\0'; i++)
    ;
  length = i;
  for (i = 0; i < length; r[i] = s[length - i - 1], i++)
    ;
  r[i] = '\0';
}