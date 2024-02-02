//
// 1.10 Exc 1.24
// Syntax check (balances braces and parenthesis)
//

#include "../common/common.h"
#include <stdio.h>
#include <stdlib.h>

#define OPEN_BRACE '{'
#define CLOSE_BRACE '}'
#define OPEN_PARENTHESIS '('
#define CLOSE_PARENTHESIS ')'
#define OPEN_BRACKET '['
#define CLOSE_BRACKET ']'
#define EOL '\n'
#define QUOTE '\''
#define DQUOTE '"'
#define SLASH '/'
#define BSLASH '\\'
#define ASTERISK '*'
#define ADIFF(p1, p2) (long)((size_t)(p1) - (size_t)(p2))
#define DUMP_TO stderr

enum state_t {
  NONE,
  SINGLELINE_COMMENT,
  MULTILINE_COMMENT,
  SINGLE_QUOTE,
  DOUBLE_QUOTE
};

typedef struct pos {
  int pos, line, col;
} pos_t;

typedef struct region {
  pos_t start;
  pos_t end;
  struct region *next, *prev;
} region_t;

static region_t *brace_base;
static region_t *parenthesis_base;
static region_t *bracket_base;
static enum state_t state = NONE;

region_t *add_node(region_t **base);
region_t *find_node(const region_t *base);
void free_list(region_t **b);
void dump_list(const region_t *const base, char c);
void dump_node(const region_t *p, const region_t *const base);
void print_not_paired(char c, pos_t p);
int check_not_paired(region_t *base, char c);
void set_pos(pos_t *p, int pos, int line, int col);
region_t **cToBase(char c);

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
  default:;
  }
  return (region_t **)NULL;
}

int main(int argc, char **argv) {
  FILE *fd = open_file_from_arg(argc, argv);
  char ch, prev[2] = {0, 0};
  pos_t cur = {0, 0, 0};
  pos_t non_nested = {-1, -1, -1};
  int syntax_ok = 1;
  while ((ch = (char)fgetc(fd ? fd : stdin)) != EOF) {
    region_t *r;
    switch (ch) {
    case EOL:
      if (state == SINGLELINE_COMMENT)
        state = NONE;
      else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE) {
        if (state == SINGLE_QUOTE) {
          print_not_paired(QUOTE, non_nested);
        } else if (state == DOUBLE_QUOTE)
          print_not_paired(DQUOTE, non_nested);
        syntax_ok = 0;
        state = NONE;
        set_pos(&non_nested, -1, -1, -1);
      }
      cur.line++;
      cur.col = -1;
      break;
    case OPEN_BRACE:
    case OPEN_PARENTHESIS:
    case OPEN_BRACKET:
      if (state == NONE) {
        r = add_node(cToBase(ch));
        r->start = cur;
      }
      break;
    case CLOSE_BRACE:
    case CLOSE_PARENTHESIS:
    case CLOSE_BRACKET:
      if (state == NONE) {
        r = find_node((const region_t *)(*cToBase(ch)));
        if (r) {
          r->end = cur;
        } else {
          syntax_ok = 0;
          print_not_paired(ch, cur);
        }
      }
      break;
    case SLASH:
      if (state == NONE) {
        if (prev[1] == SLASH)
          state = SINGLELINE_COMMENT;
      } else if (state == MULTILINE_COMMENT)
        if (prev[1] == ASTERISK)
          state = NONE;
      break;
    case QUOTE:
    case DQUOTE:
      if (state == NONE) {
        non_nested = cur;
        if (ch == QUOTE)
          state = SINGLE_QUOTE;
        else if (ch == DQUOTE)
          state = DOUBLE_QUOTE;
      } else if (state == SINGLE_QUOTE || state == DOUBLE_QUOTE) {
        if (prev[1] != BSLASH) {
          state = NONE;
          set_pos(&non_nested, -1, -1, -1);
        }
      }
      break;
    case ASTERISK:
      if (state == NONE)
        if (prev[1] == SLASH) {
          state = MULTILINE_COMMENT;
          non_nested = cur;
        }
      break;
    case BSLASH:
      break;
    default:;
    }
    cur.col++;
    cur.pos++;
    prev[0] = prev[1];
    prev[1] = ch;
  }
  if (state == MULTILINE_COMMENT) {
    print_not_paired('*', non_nested);
    syntax_ok = 0;
  }
  char tmp[5] = {OPEN_BRACE, OPEN_PARENTHESIS, OPEN_BRACKET};
  for (int i = 0; i < 3; i++)
    if (!check_not_paired(*cToBase(tmp[i]), tmp[i]))
      syntax_ok = 0;

  dump_list(*cToBase(OPEN_BRACE), OPEN_BRACE);
  dump_list(*cToBase(OPEN_PARENTHESIS), OPEN_PARENTHESIS);
  dump_list(*cToBase(OPEN_BRACKET), OPEN_BRACKET);
  free_list(cToBase(OPEN_BRACE));
  free_list(cToBase(OPEN_PARENTHESIS));
  free_list(cToBase(OPEN_BRACKET));

  if (syntax_ok)
    printf("Syntax Ok\n");
  if (fd)
    fclose(fd);
  return 0;
}

region_t *add_node(region_t **base) {
  region_t *res = (region_t *)malloc(sizeof(region_t));
  if (!res) {
    printf("Malloc error\n");
    abort();
  }
  set_pos(&res->start, -1, -1, -1);
  set_pos(&res->end, -1, -1, -1);
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
  if (!base)
    return (region_t *)NULL;
  region_t *p = base->prev;
  do {
    if (p->end.pos == -1)
      return p;
    p = p->prev;
  } while (p != base->prev);
  return (region_t *)NULL;
}

void free_list(region_t **base) {
  region_t *cur = *base;
  region_t *p;
  if (!cur)
    return;
  do {
    p = cur;
    cur = cur->next;
    free(p);
  } while (cur != *base);
  *base = NULL;
}

void print_not_paired(char c, pos_t p) {
  printf("Not paired \"%c\" at pos %d:%d\n", c, p.line + 1, p.col + 1);
}

int check_not_paired(region_t *base, char c) {
  int res = 1;
  region_t *p = base;
  if (base)
    do {
      if (p->end.pos == -1) {
        print_not_paired(c, p->start);
        res = 0;
      }
      p = p->next;
    } while (p != base);
  return res;
}

void set_pos(pos_t *p, int pos, int line, int col) {
  p->pos = pos;
  p->line = line;
  p->col = col;
}

void dump_node(const region_t *p, const region_t *const base) {
#ifdef DUMP_TO
  if (!p)
    return;
  fprintf(DUMP_TO, "adr: %p (%6ld), ", (const void *)p, ADIFF(p, base));
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
  fprintf(DUMP_TO, "start: %4d(%3d:%2d), ", p->start.pos, p->start.line,
          p->start.col);
  fprintf(DUMP_TO, "end: %4d(%3d:%2d)", p->end.pos, p->end.line, p->end.col);
  fprintf(DUMP_TO, "\n");
#endif
}

void dump_list(const region_t *const base, char c) {
  const region_t *p;
#ifdef DUMP_TO
  fprintf(DUMP_TO, "Dump list for \"%c\"\n", c);
  if (!base)
    return;
  p = (const region_t *)base;
  do {
    dump_node(p, base);
    p = p->next;
  } while (p != base);
#endif
}
