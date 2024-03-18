#include "./bars.h"
#include "./lib.h"
#include <stdio.h>
#include <assert.h>


void print_histogram_(uint *arr, uint size, uchar mode);
void print_repeat(uchar c, uchar count);

void print_histogram_horiz(uint *arr, uchar size) {
  print_histogram_(arr, size, 0);
}

void print_histogram_horiz_ch(uint *arr, uchar size) {
  print_histogram_(arr, size, 1);
}

void print_horiz_line(uchar length) {
  for (uint i = 0; i < length; i++)
    printf("%s", BAR);
  printf("\n");
}

void print_repeat(uchar c, uchar count) {
  for (uchar i = 0; i < count; i++)
    printf("%c", c);
}

void print_histogram_(uint *arr, uint size, uchar mode) {
  uint max = arr[find_max(arr, size)];
  uchar scaled_val;
  for (uchar i = 0; i < size; i++) {
    if (arr[i] > 0) {
      scaled_val = (uchar)(arr[i] * MAX_DIAGRAMM_WIDTH / max);
      if (mode == 0)
        printf("%2u", i);
      if (mode == 1)
        print_nonpr(i);
      printf(" %5u ", arr[i]);
      print_horiz_line(scaled_val);
    }
  }
}

void print_histogram_vert(uint *arr, uchar size) {
  uchar h = MAX_DIAGRAMM_HEIGHT;
  uchar w = MAX_DIAGRAMM_WIDTH;

  uchar low = 0;
  uchar high = (uchar)(size - 1);
  for (uchar i = 0; i < size; i++)
    if (arr[i] > 0) {
      low = i;
      break;
    }
  for (uchar i = 0; i < size; i++)
    if (arr[size - 1 - i] > 0) {
      high = (uchar)(size - 1 - i);
      break;
    }

  unsigned max = arr[find_max(arr, size)];
  if (max == 0) {
    printf("No input data\n");
    return;
  };
//   const float SCALE_VERT = h / max;
  int SCALE_HORIZ = w / (high - low + 1);
  assert(SCALE_HORIZ >= 0);
  if (SCALE_HORIZ > 9) SCALE_HORIZ = 9;
  w = (uchar)(SCALE_HORIZ * (high - low + 1));
  char fmt[] = { '%', (char)('0' + SCALE_HORIZ), 'd', '\0' };
  ITERATOR(NULL, low, (uchar)(high + 1), printf(fmt, i));
  printf("\n");
  print_repeat('-', w);
  printf("\n");
  ITERATOR(arr, low, (uchar)(high + 1), printf(fmt, arr[i]));
  printf("\n");
  print_repeat('-', w);
  printf("\n");

  for (uint i = 0; i < h; i++) {
    for (uint k = low; k <= high; k++) {
      uint scaled_val = arr[k] * h / max;
      print_repeat(' ', (uchar)(SCALE_HORIZ - 1));
      if (scaled_val > i || (arr[k] > 0 && i == 0))
        printf("%s", BAR);
      else
        printf(" ");
    }
    printf("\n");
  }
}

