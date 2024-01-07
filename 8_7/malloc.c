#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#define NALLOC 8
#define BR printf("\n");

#define DPRINT 0
#define BOX_WIDTH 10

typedef long Align;
typedef unsigned int uint;
typedef unsigned long ulong;

union header {
  struct {
    union header *ptr;
    unsigned size;
  } s;
  Align x;
};

typedef union header Header;
static Header base;
static Header *freep = NULL;
static void *sbrk_start = NULL;

int allocated_count = 0;
int free_count = 0;

void *malloc_(uint);
void *morecore(uint);
void free_(void *);
void print_header(Header *);
void print_list();
uint get_list_length();
ulong bToU(uint bytes);
void test();

#define COUNT 10000


int main() {
  sbrk_start = sbrk(0);
  assert((void *)&base < sbrk_start);
  test();
  
  print_list();
}

void *malloc_(uint nbytes) {
  Header *p, *prevp;
  uint nunits;
  nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
  if ((prevp = freep) == NULL) {
    base.s.ptr = prevp = freep = &base;
    base.s.size = 0;
  }
  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) {
      if (p->s.size == nunits) {
        prevp->s.ptr = p->s.ptr;
        freep = prevp;
      } else {
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      free_count -= nunits;
#if DPRINT
      printf("malloc_(size=%u)\n", nunits);
      print_list();
#endif
      return (void *)(p + 1);
    }
    if (p == freep) {
      if ((p = morecore(nunits)) == NULL) {
        return NULL;
      }
    }
  }
}

void *morecore(uint nu) {
  void *sbrk(intptr_t);
  Header *up;
  if (nu < NALLOC)
    nu = NALLOC;
  up = (Header *)sbrk(nu * sizeof(Header));
  allocated_count += nu;
  if (up == (Header *)-1)
    return NULL;
  up->s.size = nu;
  free_((void *)(up+1));
  return freep;
}

void free_(void *ap) {
  Header *bp, *p;
  bp = (Header *)ap - 1;
  for (p = freep; !(p < bp && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
      break; /* freed block at start or end of arena */
  }
  free_count += bp->s.size;
  if (bp + bp->s.size == p->s.ptr) {
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else
    bp->s.ptr = p->s.ptr;
  freep = bp;
  if (p + p->s.size == bp) {
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
    freep = p;
  } else
    p->s.ptr = bp;
  // freep = p;
#if DPRINT
  printf("free_(address=%lu), size=%u\n", bToU(ap - 1 - sbrk_start), bp->s.size);
  print_list();
#endif
}

void test() {
  
  void *res[COUNT];
  int i;
  srand(time(NULL));
  
  for (i = 0; i < COUNT; res[i++] = NULL);
  
  for (int i = 0; i < COUNT; i++) {
    int j = rand() % COUNT;
    int allocSize = rand() % 100 + 1;
    if (rand() % 10 == 0) {
      if (res[j] == NULL)
        res[j] = malloc_(allocSize * 16);
    } else {
      if (res[j] != NULL){
        free_(res[j]);
        res[j] = NULL;
      }
    }
  }
  for (i = 0; i < COUNT; i++)
    if (res[i] != NULL)
      free_(res[i]);
    
  // for (i = 0; i < COUNT; printf("%p %d\n", res[i], res[i] != NULL ? ((Header *)(res[i]-1))->s.size : 0), i++);
  // free_();
  
  // void *p;  
  // printf(
    // "base\t\t= %p %6ldGb\nsbrk_start\t= %p %6ldGb\ndiff\t\t= %14lx %6ldGb\n",
    // &base,
    // ((void *)&base - (void *)0) / 1024 / 1024 / 1024,
    // sbrk_start,
    // (sbrk_start - (void *)0) / 1024 / 1024 / 1024,
    // sbrk_start - (void *)&base,
    // (sbrk_start - (void *)&base) / 1024 / 1024 / 1024
  // );
}

void print_header(Header *p) {
  printf("{address: ");
  if (p == &base)
    printf("  (b)");
  else
    printf("%5ld", bToU((void *) p - sbrk_start));
  printf(", ptr: ");
  if (p->s.ptr == &base)
    printf("  (b)");
  else if (p->s.ptr == NULL)
    printf("(nil)");
  else
    printf("%5ld", bToU((void *) p->s.ptr - sbrk_start));
  printf(", size: %2d}", p->s.size);
  if (p == freep)
    printf(" <---freep");
  printf("\n");
}

void print_list() {
  Header *p;
  uint i;
  for (p = (Header *)&base, i = 1;; p = p->s.ptr, i++) {
    printf("%3u) ", i);
    print_header(p);
    if (p->s.ptr == NULL || p->s.ptr == (Header *)&base)
      break;
  }
  printf("Allocated (incl. headers): %d units, free (incl. headers): %d units.\n", allocated_count, free_count);
  BR
}

uint get_list_length() {
  uint i;
  Header *p;
  for (p = (Header *)&base, i = 0;; p = p->s.ptr, i++) {
    if (p->s.ptr == NULL || p->s.ptr == (Header *)&base)
      return i;
  }
}

ulong bToU(uint bytes) {
  return bytes / sizeof(Header);
}