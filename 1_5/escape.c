//
// 1.5.3 Exc 1_10
// Escape tab, backspace and backslash

#include <stdio.h>

int main() {
  char c;

  while ((c = getchar()) != EOF) {
    if (c != '\\' && c != '\t' && c != '\b')
      putchar(c);
    else {
      putchar('\\');
      if (c == '\\') putchar('\\');
      if (c == '\t') putchar('t');
      if (c == '\b') putchar('b');
    }
  }
  return 0;
}
