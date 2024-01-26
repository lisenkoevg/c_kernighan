#include "common.h"
#include <stdio.h>

FILE *open_file_from_arg(int argc, char **argv);

int main(int argc, char **argv) {
  char ch;
  FILE *fd = open_file_from_arg(argc, argv);
  if (fd) {
    printf("Reading input from [__file]:\n");
    while ((ch = fgetc(fd)) != EOF)
      putchar(ch);
    fclose(fd);
  }
  printf("\n");
}
