//
// 1.10 Exc 1.21
// Replace spances with tabs
//

#include "../common/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TABSIZE 4
#define INTAB 1
#define OUTTAB 0
#define SPACE ' '
#define TAB '\t'

unsigned process_column(char *column, unsigned char length, unsigned char is_eol);

int main(int argc, char **argv) {
  unsigned char tabsize = TABSIZE;
  if (argc > 1) {
    tabsize = atoi((const char *)argv[1]);
    assert(tabsize > 0);
  }

  char col[tabsize];
  for (int j = 0; j < tabsize; j++)
    col[j] = '\0';

  char c;
  unsigned char is_eol = 0;
  unsigned i, c_in, c_out;
  i = c_in = c_out = 0;
  while ((c = getchar()) != EOF) {
    c_in++;
    if (c != '\n') {
      col[i] = c;
    } else {
      is_eol = 1;
    }
    if (i % tabsize < (tabsize - 1) && !is_eol) {
      i++;
      continue;
    }
    c_out += process_column(col, tabsize, is_eol);
    if (is_eol) {
      putchar('\n');
      c_out++;
      is_eol = 0;
    }
  }
//   printf("counter in: %u, counter out: %u\n", c_in, c_out);
  return 0;
}

unsigned process_column(char *column, unsigned char length, unsigned char is_eol) {
  unsigned count = 0;

  int pos = length - 1;
  if (is_eol) {
//  remove trailing spaces before end of line
    while (pos >= 0 && column[pos--] == '\0')
      length--;
    for (unsigned j = 1; j <= length; j++) {
      if (column[length - j] == '\0')
        continue;
      if (column[length - j] == SPACE)
        column[length - j] = '\0';
      else
        break;
    }
  }
  for (unsigned j = 0; j < length; j++) {
    if (column[j] != '\0') {
      putchar(column[j]);
      column[j] = '\0';
      count++;
    }
  }
  for (unsigned j = 0; j < length; j++)
    column[j] = '\0';
  return count;
}
