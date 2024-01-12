#include <stdio.h>
#include "lib.h"

char is_blank(char c) {
  if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
    return 1;
  return 0;
}

void print_array_hex(char arr[], int size) {
  for (int i = 0; i <= size; i++)
    printf("%#04x ", arr[i]);
  printf("\n");
}

int remove_trailing_blanks(char *line, int length) {
  int i;
  for (i = 0; i < length && is_blank(line[length - 1 - i]); i++)
    ;
  line[length - i] = '\0';
  int new_length = length - i;
  return new_length;
}
