//
// Write intput split by char
//

#include <stdio.h>

int main() {
  unsigned char c;

  while (c = getchar()) {
    if (feof(stdin))
      break;
    putchar(c);
    if (c != '\n') putchar('\n');
  }
  return 0;
}
