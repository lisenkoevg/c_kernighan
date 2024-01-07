//
// 1.5.4 Exc 1.12  
// Print output one word per line

#include <stdio.h>
#define IN 0
#define OUT 1

int main() {
  char c;
  char state;
  
  state = OUT;
  while (c = getchar()) {
    if (feof(stdin))
      break;
    if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
      if (state == IN)
        putchar('\n');
      state = OUT;
    } else {
      state = IN;
      putchar(c);
    }
  }
  return 0;
}
