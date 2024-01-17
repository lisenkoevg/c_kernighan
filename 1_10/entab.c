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
  int curpos = 0;
  while ((c = getchar()) != EOF) {

#if SWITCH 
    switch (c) {
      case EOL: 
      case CR: 
        if (state == IN) {
          state = OUT;
          putchar(TAB);
        }
        curpos = 0;
        laststart = 0;
        putchar(c);
        break;
      case SPACE: 
        if (state == IN) {
          if (curpos % tabsize == 0) {
            laststart = curpos;
            putchar(TAB);
          }
        } else {
          state = IN;
          laststart = curpos;
        }
        break;
      default:
        if (state == IN) {
          if (curpos % tabsize == 0)
            putchar(TAB);
          else {
            if ((curpos - laststart == 1) && (laststart % tabsize != 0))
              putchar(SPACE);
            else
              putchar(TAB);
          }
          state = OUT;
          laststart = 0;
        }
        putchar(c);
        break;
    }
#endif

#if !SWITCH
    if (c == EOL) {
      if (state == IN) {
        state = OUT;
        putchar(TAB);
      }
      curpos = 0;
      laststart = 0;
      putchar(EOL);
    } else if (c == SPACE) {
      if (state == IN) {
        if (curpos % tabsize == 0) {
          laststart = curpos;
          putchar(TAB);
        }
      } else {
        state = IN;
        laststart = curpos;
      }
    } else {
      if (state == IN) {
        if (curpos % tabsize == 0)
          putchar(TAB);
        else {
          if ((curpos - laststart == 1) && (laststart % tabsize != 0))
            putchar(SPACE);
          else
            putchar(TAB);
        }
        state = OUT;
        laststart = 0;
      }
      putchar(c);
    }
#endif

    if (c != EOL)
      curpos++;
  }
  return 0;
}

