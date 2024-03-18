//
// 1.6 Exc 1.14
// Print histogram of char frequency
//

#include "./bars.h"
#include "./lib.h"
#include <assert.h>
#include <stdio.h>

#define MAX_CHAR_CODE 255

int main(int argc, char **argv) {
  argv[argc - 1] = argv[argc - 1];
  char c;
  uint freqs[MAX_CHAR_CODE] = {0};

  init_array(freqs, MAX_CHAR_CODE);
  while (((c = (char)getchar()) != EOF) && !feof(stdin)) {
    freqs[(uchar)c]++;
  }
  print_histogram_horiz_ch(freqs, MAX_CHAR_CODE);
  return 0;
}
