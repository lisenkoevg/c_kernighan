//
// 1.10 Exc 1.21
// Replace spaces with tabs
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TABSIZE 4

#define IN 1
#define OUT 0
#define SPACE ' '
#define TAB '\t'
#define EOL '\n'
#define CR '\r'

#define SWITCH 1

int main(int argc, char **argv) {
  unsigned char tabsize = TABSIZE;
  if (argc > 1) {
    tabsize = atoi((const char *)argv[1]);
    assert(tabsize > 0);
  }
  printf("tabsize: %d\n\n", tabsize);

  char c;
  int state = OUT;
  int laststart = 0;
  int col = 0;

  while ((c = getchar()) != EOF) {
    switch (c) {
      case EOL: 
      case CR: 
        if (state == IN) {
          state = OUT;
          putchar(TAB);
        }
        col = 0;
        laststart = 0;
        putchar(c);
        break;
      case SPACE: 
        if (col == tabsize)
          col = 0;

        if (state == IN) {
          if (col == 0) {
            putchar(TAB);
            laststart = 0;
          }
          col++;
        } else {
          state = IN;
          laststart = col;
          col++;
        }
        break;
      default:
        if (col == tabsize)
          col = 0;
        if (state == IN) {
          if (col == 0)
            putchar(TAB);
          else {
            if ((col - laststart == 1) && (laststart != 0)) {
              putchar(SPACE);
              col++;
            } else {
              putchar(TAB);
              col = 0;
            }
          }
          state = OUT;
          laststart = 0;
        }
        putchar(c);
        col++;
        break;
    }
  }
  return 0;
}

