//
// 1.6 Exc 1.13
// Print histogram of words length
//

#include "../common/lib.h"
#include "./bars.h"
#include "./lib.h"
#include <assert.h>
#include <stdio.h>

#define MAX_WORD_LENGTH 100

int main() {
  char c;
  unsigned int lengths[MAX_WORD_LENGTH];
  int counter = 0;

  init_array(lengths, MAX_WORD_LENGTH);
  while (((c = getchar()) != EOF) && !feof(stdin)) {
    if (is_blank(c)) {
      if (counter > 0) {
        assert(counter < MAX_WORD_LENGTH);
        lengths[counter]++;
        counter = 0;
      }
    } else
      ++counter;
  }
  print_histogram_horiz(lengths, MAX_WORD_LENGTH);
  printf("\n");
  print_histogram_vert(lengths, MAX_WORD_LENGTH);
  return 0;
}
