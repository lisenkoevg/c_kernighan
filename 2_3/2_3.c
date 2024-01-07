#include <stdio.h>

#define MAXLENGTH 10

int htoi(char *s);

int main() {
  char c;
  char s[MAXLENGTH] = {0};
  int i, res, val;
  for (i = 0; (c = getchar()) != EOF && (i < MAXLENGTH); i++) {
    s[i] = c;
  }
  printf("%s = %d (%%x -> %x)\n", s, htoi(s), htoi(s));
  return 0;
}

int htoi(char *s) {
  int res, val;
  char c;
  char r[MAXLENGTH] = {0};
  res = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] >= '0' && s[i] <= '9')
      val = s[i] - '0';
    else if (s[i] >= 'a' && s[i] <= 'f')
      val = s[i] - 'a' + 10;
    else if (s[i] >= 'A' && s[i] <= 'F')
      val = s[i] - 'A' + 10;
    res = res * 16 + val;
  }
  return res;
}
