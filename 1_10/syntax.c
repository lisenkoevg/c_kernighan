//
// 1.10 Exc 1.24
// Syntax check (balances braces and parenthesis)
//

#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"

#define OPEN_BRACE '{'
#define CLOSE_BRACE '}'
#define OPEN_PARENTHESIS '('
#define CLOSE_PARENTHESIS ')'
#define OPEN_BRACKET '['
#define CLOSE_BRACKET ']'
#define EOL '\n'

#define ADIFF(p1, p2) ((size_t)(p1) - (size_t)(p2))

#define DUMP_TO stderr

typedef struct node {
  int start_pos;
  int start_line;
  int start_col;
  int end_pos;
  int end_line;
  int end_col;
  struct node *next, *prev;
} region_t;

static region_t *brace_base;
static region_t *parenthesis_base;
static region_t *bracket_base;

region_t *add_node(region_t **base);
region_t *find_node(const region_t *base);
void free_list(region_t **b);
void dump_list(const region_t *const base, char c);
void dump_node(const region_t *p, const region_t *const base);
void print_not_paired(char c, int pos, int line, int col);
int check_not_paired_open(region_t *base, char c);

region_t **cToBase(char c) {
  switch (c) {
    case OPEN_BRACE:
    case CLOSE_BRACE:
      return &brace_base;
    case OPEN_PARENTHESIS:
    case CLOSE_PARENTHESIS:
      return &parenthesis_base;
    case OPEN_BRACKET:
    case CLOSE_BRACKET:
      return &bracket_base;
  }
  return (region_t **)NULL;
}

int main(int argc, char **argv) {
  FILE *fd = open_file_from_arg(argc, argv);
  char ch;
  int col = 0;
  int line = 0;
  int pos = 0;
  int syntax_ok = 1;

  while ((ch = fgetc(fd ? fd : stdin)) != EOF) {
    region_t *br;
    switch (ch) {
      case EOL:
        line++;
        pos++;
        col = 0;
        continue;
      case OPEN_BRACE:
      case OPEN_PARENTHESIS:
      case OPEN_BRACKET:
        br = add_node(cToBase(ch));
        br->start_pos = pos;
        br->start_line = line;
        br->start_col = col;
        break;
      case CLOSE_BRACE:
      case CLOSE_PARENTHESIS:
      case CLOSE_BRACKET:
        br = find_node((const region_t *)(*cToBase(ch)));
        if (br) {
          br->end_pos = pos;
          br->end_line = line;
          br->end_col = col;
        } else {
          syntax_ok = 0;
          print_not_paired(ch, pos, line, col);
        }
        break;
      default:
        break;
    }
    col++;
    pos++;
  }
  if (!check_not_paired_open(*cToBase(OPEN_BRACE), OPEN_BRACE)) syntax_ok = 0;
  if (!check_not_paired_open(*cToBase(OPEN_PARENTHESIS), OPEN_PARENTHESIS))
    syntax_ok = 0;
  if (!check_not_paired_open(*cToBase(OPEN_BRACKET), OPEN_BRACKET))
    syntax_ok = 0;

  dump_list(*cToBase(OPEN_BRACE), OPEN_BRACE);
  dump_list(*cToBase(OPEN_PARENTHESIS), OPEN_PARENTHESIS);
  dump_list(*cToBase(OPEN_BRACKET), OPEN_BRACKET);

  free_list(cToBase(OPEN_BRACE));
  free_list(cToBase(OPEN_PARENTHESIS));
  free_list(cToBase(OPEN_BRACKET));

  if (syntax_ok) printf("Syntax Ok\n");
  if (fd) fclose(fd);
  return 0;
}

region_t *add_node(region_t **base) {
  region_t *res = (region_t *)malloc(sizeof(region_t));
  if (!res) {
    printf("Malloc error\n");
    abort();
  }
  res->start_line = res->end_line = -1;
  res->start_col = res->end_col = -1;
  res->start_pos = res->end_pos = -1;
  if (!*base) {
    *base = res->next = res->prev = res;
  } else {
    region_t *last = (*base)->prev;
    last->next = res;
    res->prev = last;
    res->next = *base;
    (*base)->prev = res;
  }
  return res;
}

region_t *find_node(const region_t *base) {
  if (!base) return (region_t *)NULL;
  const region_t *p = base->prev;
  do {
    if (p->end_pos == -1) return (region_t *)p;
    p = p->prev;
  } while (p != base->prev);
  return (region_t *)NULL;
}

void free_list(region_t **base) {
  region_t *cur = *base;
  region_t *p;
  if (!cur) return;
  do {
    p = cur;
    cur = cur->next;
    free(p);
  } while (cur != *base);
  *base = NULL;
}

void print_not_paired(char c, int pos, int line, int col) {
  printf("Not paired \"%c\" at pos %d:%d\n", c, line + 1, col + 1);
}

int check_not_paired_open(region_t *base, char c) {
  int res = 1;
  region_t *p = base;
  if (base) do {
      if (p->end_pos == -1) {
        print_not_paired(c, p->start_pos, p->start_line, p->start_col);
        res = 0;
      }
      p = p->next;
    } while (p != base);
  return res;
}

void dump_node(const region_t *p, const region_t *const base) {
#ifdef DUMP_TO
  if (!p) return;
  fprintf(DUMP_TO, "adr: %p (%6ld), ", p, ADIFF(p, base));
  fprintf(DUMP_TO, "prev: ");
  if (p->prev)
    fprintf(DUMP_TO, "%6ld, ", ADIFF(p->prev, base));
  else
    fprintf(DUMP_TO, "(NULL), ");
  fprintf(DUMP_TO, "next: ");
  if (p->next)
    fprintf(DUMP_TO, "%6ld, ", ADIFF(p->next, base));
  else
    fprintf(DUMP_TO, "(NULL), ");
  fprintf(DUMP_TO, "start: %4d(%3d:%2d), ", p->start_pos, p->start_line,
          p->start_col);
  fprintf(DUMP_TO, "end: %4d(%3d:%2d)", p->end_pos, p->end_line, p->end_col);
  fprintf(DUMP_TO, "\n");
#endif
}

void dump_list(const region_t *const base, char c) {
  const region_t *p;
#ifdef DUMP_TO
  fprintf(DUMP_TO, "Dump list for \"%c\"\n", c);
  if (!base) return;
  p = (const region_t *)base;
  do {
    dump_node(p, base);
    p = p->next;
  } while (p != base);
#endif
}
