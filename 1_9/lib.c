#include <stdio.h>
void copy_(char from[], char to[]) {
  int i = 0;
  while ((to[i++] = from[i]) != '\0')
    ;
}
