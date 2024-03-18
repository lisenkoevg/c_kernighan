//
// 1.10 Exc 1.20
// Replace tabs with spaces
//

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define TABSIZE 7

int main(int argc, char **argv) {
  char c, i;
  unsigned char tabsize = TABSIZE;
  if (argc > 1) {
    tabsize = (unsigned char)atoi((const char *)argv[1]);
    assert(tabsize > 0);
  }
  printf("tabsize: %u\n", tabsize);
  while ((c = (char)getchar()) != EOF) {
    if (c == '\t') {
      do {
        putchar(' ');
      } while (++i % tabsize != 0);
    } else {
      putchar(c);
      if (c != '\n')
        ++i;
      else
        i = 0;
    }
  }
  return 0;
}
