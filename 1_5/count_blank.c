
// 1.5.3 Exc 1.8
// count blank symbols

#include <stdio.h>

int main() {
  char c;
  int ns, nt, nn;
  ns = nt = nn = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++ns;
    else if (c == '\t')
      ++nt;
    else if (c == '\n')
      ++nn;
  }
  printf("Spaces: %d, tabs: %d, newlines: %d\n", ns, nt, nn);
  return 0;
}

