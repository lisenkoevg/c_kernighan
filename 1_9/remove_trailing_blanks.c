//
// 1.9 Exc 1.18
// Remove trailing blank symbols and empty lines from input
//

#include "../common/lib.h"
#include "lib.c"
#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1000

int main(int argc, char **argv) {
  char line[MAX_LINE_LENGTH];
  int length;

  while ((length = getline_(line, MAX_LINE_LENGTH)) > 0) {
    int i;
    for (i = 0; i < length && is_blank(line[length - 1 - i]); i++)
      ;
    if (i == length) continue;
    line[length - i] = '\0';
    printf("%s\n", line);
  }
  return 0;
}
