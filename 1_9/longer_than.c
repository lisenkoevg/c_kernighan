//
// 1.9 Exc 1.17
// Ouput lines longer than
//

#include "lib.c"
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE_LENGTH 1000
#define MIN_OUTPUT 70

int main(int argc, char **argv) {
  char line[MAX_LINE_LENGTH];
  int length;
  int min_output = MIN_OUTPUT;

  if (argc > 1)
    min_output = atoi(argv[1]);
  printf("MIN_OUTPUT: %d\n", min_output);
  while ((length = getline_(line, MAX_LINE_LENGTH)) > 0) {
    if (length > min_output)
      printf("%s", line);
  }
  return 0;
}
