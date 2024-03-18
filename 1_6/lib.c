#include "./lib.h"
#include <stdio.h>

#define NON_PRINT_MAX 33

replacer_t non_pr[NON_PRINT_MAX];

void init_nonpr(void);

void init_array(uint *arr, uint size) {
  for (uint i = 0; i < size; i++)
    *(arr + i) = 0;
}

void print_array(uint *arr, uint size) {
  uint total = 0;
  for (uint i = 0; i < size; i++) {
    if (arr[i] > 0)
      printf("%u = %u\n", i, arr[i]);
    total += arr[i];
  }
  printf("Total: %u\n", total);
}

void init_nonpr() {
  for (uint i = 0; i < NON_PRINT_MAX; i++)
    non_pr[i].a = non_pr[i].b = 0;
  non_pr[10].a = '\\';
  non_pr[10].b = 'n';
  non_pr[32].a = 'S';
  non_pr[32].b = 'P';
}

void print_nonpr(uchar c) {
  static char is_init = 0;
  if (!is_init) {
    init_nonpr();
    is_init = 1;
  }
  if (c < NON_PRINT_MAX && non_pr[c].a) {
    printf("%c%c(%3u)", non_pr[c].a, non_pr[c].b, c);
  } else {
    printf("%-2c(%3d)", c, c);
  }
}

void print_array_ch(uint *arr, uint size) {
  uint total = 0;
  for (uchar i = 0; i < size; i++) {
    if (arr[i] > 0) {
      print_nonpr(i);
      printf(" = %u\n", arr[i]);
    }
    total += arr[i];
  }
  printf("Total: %u\n", total);
}

unsigned find_max(uint *arr, uint size) {
  unsigned result = 0;
  for (uint i = 1; i < size; i++)
    if (arr[i] > arr[result])
      result = i;
  return result;
}
