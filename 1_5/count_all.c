//
// 1.5.4
// "wc" analog

#include <stdio.h>

// grep -r setmode /usr/include
// grep -r O_BINARY /usr/include
// _setmode(_fileno(stdin), _O_BINARY);
// _setmode(_fileno(stdout), _O_BINARY);
// _setmode(_fileno(stderr), _O_BINARY);

extern int _setmode(int, int);

#define IN 1
#define OUT 0

int main() {
  _setmode(STDIN_FILENO, 0x8000);
//   _setmode(STDOUT_FILENO, 0x8000);
//   _setmode(STDERR_FILENO, 0x8000);
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
