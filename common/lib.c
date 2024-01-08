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
