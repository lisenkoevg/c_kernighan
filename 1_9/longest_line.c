//
// 1.9 Exc 1.16
// Ouput longest input line
// 

#include <stdio.h>
#include "lib.c"
#define MAX_LINE_LENGTH 40

int getline_(char line[], int lim);
void copy_(char from[], char to[]);
void print_array_hex(char arr[], int size);

int main() {
  printf("MAX_LINE_LENGTH: %d\n", MAX_LINE_LENGTH);
  char line[MAX_LINE_LENGTH + 1];
  char maxline[MAX_LINE_LENGTH + 1];
  int length, maxlength, maxindex;
  length = maxlength = maxindex = 0;
  int counter = 1;
  int acc = 0;
  while ((length = getline_(line, MAX_LINE_LENGTH)) > 0) {
    if (acc == 0)
      printf("%3d | ", counter);
    if (length == MAX_LINE_LENGTH && line[MAX_LINE_LENGTH - 1] != '\n') {
      acc += length;
      line[MAX_LINE_LENGTH] = '\0';
      printf("%s", line);
      continue;
    }
    if (acc > 0) {
      length += acc;
      acc = 0;
    }
    if (length > maxlength) {
      maxlength = length;
      copy_(line, maxline);
      maxindex = counter;
    }
    printf("%s", line);
    counter++;
  }
  if (maxlength > 0) {
    printf("Maxlength: %d, line %d\n", maxlength, maxindex);
  }
  return 0;
}
