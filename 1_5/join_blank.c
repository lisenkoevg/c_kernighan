
// 1.5.3 Exc 1.8
// join blank symbols in input

#include <stdio.h>

int main() {
  char c, first;

  first = 0;
  while ((c = getchar()) != EOF) {
    if ((c == ' ') || (c == '\t') || (c == '\n')) {
      if (first == 0 || first != c) {
        putchar(c);
        first = c;
      }
    } else {
      putchar(c);
      if (first != 0)
        first = 0;
    }
  };
  return 0;
}




