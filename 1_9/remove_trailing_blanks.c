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
    if (remove_trailing_blanks(line, length) == 0)
      continue;
    printf("%s\n", line);
  }
  return 0;
}
