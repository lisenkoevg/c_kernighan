#include "common.h"
#include <stdio.h>

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

int mygetline(char *line, int lim) {
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

// If args contain argument in format '__xxx',
// then open 'xxx' file for reading
// and return pointer to file descriptor
// Used to cope with redirection bug in cygwin-gdb https://sourceware.org/legacy-ml/cygwin/1999-04/msg00308.html
FILE *open_file_from_arg(int argc, char **argv) {
  char *test_file;
  int test_file_i;

  if (argc == 1)
    return NULL;

  for (int i = 0; i < argc; i++) {
    if (argv[i][0] == '_' && argv[i][1] == '_') {
      test_file_i = i;
      test_file = argv[i];
      break;
    }
  }
  if (test_file_i == 0)
    return NULL;
  for (int i = 0; (test_file[i] = test_file[i + 2]); i++)
    ;
  FILE *fd;
  fd = fopen(test_file, "r");
  return fd;
}
