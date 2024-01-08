typedef struct {
  char a;
  char b;
} replacer_t;

#define ITERATOR(arr, from, to, action) \
  for (int i = (from); i < (to); i++) action

void init_array(int *arr, int size); 
void print_array(int *arr, int size); 
void print_array_ch(int *arr, int size); 
unsigned find_max(int *arr, int size); 
void print_nonpr(unsigned char);
