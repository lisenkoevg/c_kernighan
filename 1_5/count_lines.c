  
// 1.5.3
// "wc --lines" analog

#include <stdio.h>

int main() {
  int c, nl;

  while ((c = getchar()) != EOF)
    if (c == '\n')
      ++nl;
  printf("lines: %d\n", nl);
  return 0;
}
