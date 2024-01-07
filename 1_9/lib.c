#include <stdio.h>

int getline_(char *line, int lim) {
  char c;
  int i;
  for (i = 0; (i < lim) && ((c = getchar()) != EOF) && c != '\n'; i++) {
    line[i] = c;
  }
  if (c == '\n')
    line[i++] = '\n';
  line[i] = '\0';
  return i;
}

void copy_(char from[], char to[]) {
  int i = 0;
  while ((to[i++] = from[i]) != '\0')
    ;
}

void print_array_hex(char arr[], int size) {
  for (int i = 0; i <= size; i++)
    printf("%#04x ", arr[i]);
  printf("\n");
}
