//
// 1.5.4
// "wc" analog

#include <stdio.h>

#define IN 1
#define OUT 0

int main() {
  char c;
  int nl, nw, nc, state;

  state = OUT;
  nl = nw = nc = 0;
  while ((c = getchar()) !=EOF) {
    if (c == ' ' || c == '\r' || c == '\n' || c == '\t') {
      state = OUT;
    } else if (state == OUT) {
      state = IN;
      ++nw;
    }
    if (c == '\n') ++nl;
    ++nc;
  }
  printf("Lines: %d, word: %d, chars: %d\n", nl, nw, nc);
  return 0;
}
