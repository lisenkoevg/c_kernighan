//
// 1.10 Exc 1.23
// Remove C-comments
//

#include "../common/common.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define QUOTE '\''
#define DQUOTE '"'
#define SLASH '/'
#define BSLASH '\\'
#define ASTERISK '*'
#define EOL '\n'

#define IN 1
#define OUT 0

const char SINGLE_LINE_COMMENT[2] = {SLASH, SLASH};

int main(int argc, char **argv) {
  FILE *fd = open_file_from_arg(argc, argv);
  if (fd == NULL)
    fd = stdin;
  char ch;
  char prev[2] = {'\0', '\0'};
  int state_q, state_dq, state_com_single, state_com_multi;

  state_q = state_dq = state_com_single = state_com_multi = OUT;
  while ((ch = fgetc(fd)) != EOF) {
    switch (ch) {
    case EOL:
      if (state_com_multi == OUT) {
        if (state_com_single == IN) {
          state_com_single = OUT;
        } else {
          if (prev[1] == SLASH && prev[0] != ASTERISK)
            putchar(SLASH);
        }
        putchar(ch);
      }
      break;
    case QUOTE:
      if (state_com_single == OUT && state_com_multi == OUT) {
        if (state_q == OUT)
          state_q = IN;
        else if (prev[1] != BSLASH)
          state_q = OUT;
        putchar(ch);
      }
      break;
    case DQUOTE:
      if (state_com_single == OUT && state_com_multi == OUT) {
        if (state_dq == OUT)
          state_dq = IN;
        else
          state_dq = OUT;
        putchar(ch);
      }
      break;
    case SLASH:
      if (state_dq == IN || state_q == IN) {
        putchar(ch);
      } else if (state_com_multi == IN) {
        if (prev[1] == ASTERISK)
          state_com_multi = OUT;
      } else if (state_com_single == OUT) {
        if (prev[1] == SLASH)
          state_com_single = IN;
      }
      break;
    case ASTERISK:
      if (state_dq == IN || state_q == IN) {
        putchar(ch);
      } else if (state_com_single == OUT && state_com_multi == OUT) {
        if (prev[1] == SLASH)
          state_com_multi = IN;
        else
          putchar(ch);
      }
      break;
    case BSLASH:
      putchar(ch);
      break;
    default:
      if (state_com_single == OUT && state_com_multi == OUT) {
        if (prev[1] == SLASH && prev[0] != ASTERISK && state_dq == OUT && state_q == OUT)
          putchar(SLASH);
        putchar(ch);
      }
      break;
    }
    prev[0] = prev[1];
    prev[1] = ch;
    fflush(NULL);
  }
  if (fd != NULL && fd != stdin)
    fclose(fd);
}
