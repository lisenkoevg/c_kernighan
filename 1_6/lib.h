#include "type.h"

typedef struct {
  uchar a;
  uchar b;
} replacer_t;

#define ITERATOR(arr, from, to, action) \
  for (uchar i = (from); i < (to); i++) (action)

void init_array(uint *arr, uint size);
void print_array(uint *arr, uint size);
void print_array_ch(uint *arr, uint size);
unsigned find_max(uint *arr, uint size);
void print_nonpr(uchar);
