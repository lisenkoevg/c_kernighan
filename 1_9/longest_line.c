
// 1.9
// Ouput longest input line
// 

#include <stdio.h>
#define MAX_LINE_LENGTH 4

int getline_(char line[], int lim);
void copy_(char from[], char to[]);
void print_array_hex(char arr[], int size);

int main() {
  char line[MAX_LINE_LENGTH + 1];
  char maxline[MAX_LINE_LENGTH + 1];
  int length, maxlength, maxindex;
  length = maxlength = maxindex = 0;
  int counter = 1;
  int acc = 0;
  while ((length = getline_(line, MAX_LINE_LENGTH)) > 0) {
//     printf("%3d | ", counter);
//     if (length == MAX_LINE_LENGTH && line[MAX_LINE_LENGTH - 1] != '\n') {
//       acc += length;
//       line[MAX_LINE_LENGTH] = '\0';
//       printf("%s", line);
//       continue;
//     }
    if (acc > 0) {
      length += acc;
      acc = 0;
    }
    if (length > maxlength) {
      maxlength = length;
      copy_(line, maxline);
      maxindex = counter;
    }
//     printf("%s\n", line);
    counter++;
  }
  if (maxlength > 0) {
    printf("\n%3d | ", maxindex);
    printf("'%s'", maxline);
    printf("\n%d\n", maxlength);
    print_array_hex(maxline, MAX_LINE_LENGTH);
  }
  return 0;
}

int getline_(char *line, int lim) {
  char c;
  int i;
  for (i = 0; (i < lim) && ((c = getchar()) != EOF) && (c != '\n'); i++) {
    line[i] = c;
  }
//   if (c == '\n')
//     line[i] = '^';
  line[i + 1] = '\0';
  return i;
}

void copy_(char from[], char to[]) {
  int i = 0;
  while ((to[i++] = from[i]) != '\0')
    ;
}

void print_array_hex(char arr[], int size) {
  for (int i = 0; i < size; i++)
    printf("%#04x ", arr[i]);
  printf("\n");
}
