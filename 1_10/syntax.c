//
// 1.10 Exc 1.24
// Syntax check (balances braces and parenthesis)
//

#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"

#define MAX 1000

#define OPEN_BRACE '{'
#define CLOSE_BRACE '}'
#define EOL '\n'

typedef struct node {
  int start_line;
  int start_col;
  int end_line;
  int end_col;
  struct node *next, *prev;
} region_t;

static region_t *brace_base;

region_t *add_node();
void free_list(region_t **b);
void dump_list(region_t *base);
void dump_node(region_t *p, region_t *base);

int main(int argc, char **argv) {
  FILE *fd = open_file_from_arg(argc, argv);
  char ch;
  int col = 0;
  int line = 0;
  region_t *br;
  while ((ch = fgetc(fd ? fd : stdin)) != EOF) {
    switch (ch) {
      case EOL:
        line++;
        col = 0;
        break;
      case OPEN_BRACE:
        region_t *tmp = add_node();
        if (brace_base) {
          br->next = tmp;
          tmp->prev = br;
        } else {
          tmp->prev = tmp->next = NULL;
          brace_base = tmp;
        }
        br = tmp;
        br->start_line = line;
        br->start_col = col;
        break;
      case CLOSE_BRACE:
        br->end_line = line;
        br->end_col = col;
      default:
        break;
    }
    col++;
  }
  dump_list(brace_base);
  free_list(&brace_base);
  if (fd) fclose(fd);
}

region_t *add_node() {
  region_t *res = (region_t *)malloc(sizeof(region_t));
  if (!res) {
    printf("Malloc error\n");
    abort();
  }
  res->prev = res->next = NULL;
  res->start_line = res->start_col = -1;
  res->end_line = res->end_col = -1;
  return res;
}

void dump_list(region_t *base) {
  region_t *p;
  if (!base) return;
  p = base;
  do {
    dump_node(p, base);
    p = p->next;
  } while (p);
}

size_t adiff(region_t *p1, region_t *p2) { return (size_t)p1 - (size_t)p2; }

void dump_node(region_t *p, region_t *base) {
  if (!p) return;
  printf("adr: %p (%6ld), ", p, adiff(p, base));
  printf("prev: ");
  if (p->prev)
    printf("%6ld, ", adiff(p->prev, base));
  else
    printf("(NULL), ");
  printf("next: ");
  if (p->next)
    printf("%6ld, ", adiff(p->next, base));
  else
    printf("(NULL), ");
  printf("start: %2d:%d, ", p->start_line, p->start_col);
  printf("end: %2d:%d", p->end_line, p->end_col);
  printf("\n");
}

void free_list(region_t **base) {
  region_t *cur = *base;
  region_t *p;
  if (!cur) return;
  do {
    p = cur;
    cur = cur->next;
    free(p);
  } while (cur);
  *base = NULL;
}
