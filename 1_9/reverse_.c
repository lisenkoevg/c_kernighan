//
// 1.9 Exc 1.17
// Reverse string, print intput reversed each line
//

#include "../common/common.h"
#include "lib.c"
#define MAX_LINE_LENGTH 1000

void reverse_(char line[], int length);

int main() {
  char line[MAX_LINE_LENGTH];
  int length;

  while ((length = mygetline(line, MAX_LINE_LENGTH)) > 0) {
    int len = length;
    for (int i = 0; i < length; i++)
      if (line[length - i - 1] == '\n') {
        len = length - i - 1;
        if (length - i - 2 >= 0 && line[length - i - 2] == '\r')
          len = length - i - 2;
        break;
      }
    reverse_(line, len);
    printf("%s", line);
  }
  return 0;
}

void reverse_(char line[], int length) {
  char tmp;
  for (int i = 0; i < length / 2; i++) {
    tmp = line[i];
    line[i] = line[length - 1 - i];
    line[length - 1 - i] = tmp;
  }
}


