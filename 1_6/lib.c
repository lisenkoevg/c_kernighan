#include "./lib.h"
#include <stdio.h>

#define NON_PRINT_MAX 33

replacer_t non_pr[NON_PRINT_MAX];

char is_blank(char c) {
  if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
    return 1;
  return 0;
}

void init_array(int *arr, int size) {
  for (int i = 0; i < size; i++)
    *(arr + i) = 0;
}

void print_array(int *arr, int size) {
  int total = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > 0)
      printf("%d = %d\n", i, arr[i]);
    total += arr[i];
  }
  printf("Total: %d\n", total);
}

void init_nonpr() {
  for (int i = 0; i < NON_PRINT_MAX; i++) 
    non_pr[i].a = non_pr[i].b = 0;
  non_pr[10].a = '\\';
  non_pr[10].b = 'n';
  non_pr[32].a = '\\';
  non_pr[32].b = 'S';
}

void print_nonpr(unsigned char c) {
  static char is_init = 0;
  if (!is_init) {
    init_nonpr();
    is_init = 1;
  }
  if (non_pr[c].a)
    printf("%c%c(%3d)", non_pr[c].a, non_pr[c].b);
  else
    printf("%-2c(%3d)", c, c);
}

void print_array_ch(int *arr, int size) {
  int total = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] > 0) {
      print_nonpr((unsigned char) i);
      printf(" = %d\n", arr[i]);
    }
    total += arr[i];
  }
  printf("Total: %d\n", total);
}

unsigned find_max(int *arr, int size) {
  unsigned result = 0;
  for (int i = 1; i < size; i++)
    if (arr[i] > arr[result])
      result = i;
  return result;
}
