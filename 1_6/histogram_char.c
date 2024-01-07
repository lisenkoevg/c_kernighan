//
// 1.6 Exc 1.14
// Print histogram of char frequency
//

#include "./bars.h"
#include "./lib.h"
#include <assert.h>
#include <stdio.h>

#define MAX_CHAR_CODE 255

int main() {
  char c;
  unsigned int freqs[MAX_CHAR_CODE];
  int counter = 0;

  init_array(freqs, MAX_CHAR_CODE);
  while (((c = getchar()) != EOF) && !feof(stdin)) {
    freqs[c]++;
  }
  print_histogram_horiz_ch(freqs, MAX_CHAR_CODE);
  return 0;
}
