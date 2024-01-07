#include "./bars.h"
#include "./lib.h"
#include <stdio.h>
#include <assert.h>

void print_histogram_(int *arr, int size, char mode);

void print_histogram_horiz(int *arr, int size) {
  print_histogram_(arr, size, 0);
}

void print_histogram_horiz_ch(int *arr, int size) {
  print_histogram_(arr, size, 1);
}

void print_horiz_line(int length) {
  for (int i = 0; i < length; i++)
    printf("%s", BAR);
  printf("\n");
}

void print_repeat(char c, unsigned count) {
  for (int i = 0; i < count; i++)
    printf("%c", c);
}

void print_histogram_(int *arr, int size, char mode) {
  unsigned max = arr[find_max(arr, size)];
  int scaled_val;
  for (int i = 0; i < size; i++) {
    if (arr[i] > 0) {
      scaled_val = arr[i] * MAX_DIAGRAMM_WIDTH / max;
      if (mode == 0)
        printf("%2d", i);
      if (mode == 1)
        print_nonpr(i);
      printf(" %5d ", arr[i]);
      print_horiz_line(scaled_val);
    }
  }
}

void print_histogram_vert(int *arr, int size) {
  unsigned h = MAX_DIAGRAMM_HEIGHT;
  unsigned w = MAX_DIAGRAMM_WIDTH;
  
  unsigned low = 0;
  unsigned high = size - 1;
  for (int i = 0; i < size; i++)
    if (arr[i] > 0) {
      low = i;
      break;
    }
  for (int i = 0; i < size; i++)
    if (arr[size - 1 - i] > 0) {
      high = size - 1 - i;
      break;
    }

  unsigned max = arr[find_max(arr, size)];
  if (max == 0) {
    printf("No input data\n");
    return;
  };
  const float SCALE_VERT = h / max;
  unsigned char SCALE_HORIZ = w / (high - low + 1);
  assert(SCALE_HORIZ >= 0);
  if (SCALE_HORIZ > 9) SCALE_HORIZ = 9;
  w = SCALE_HORIZ * (high - low + 1);
  char fmt[] = { '%', '0' + SCALE_HORIZ, 'd', '\0' };
  ITERATOR(NULL, low, high + 1, printf(fmt, i));
  printf("\n");
  print_repeat('-', w);
  printf("\n");
  ITERATOR(arr, low, high + 1, printf(fmt, arr[i]));
  printf("\n");
  print_repeat('-', w);
  printf("\n");

  for (int i = 0; i < h; i++) {
    for (int k = low; k <= high; k++) {
      int scaled_val = arr[k] * h / max;
      print_repeat(' ', SCALE_HORIZ - 1);
      if (scaled_val > i || (arr[k] > 0 && i == 0))
        printf("%s", BAR);
      else
        printf(" ");
    }
    printf("\n");
  }
}

