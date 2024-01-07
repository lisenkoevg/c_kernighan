
// 1.5.2
// "wc --bytes" analog

#include <stdio.h>

int main() {
  int nc = 0;
  while (getchar() != EOF)
    ++nc;
  printf("count: %d\n", nc);
  return 0;
}
