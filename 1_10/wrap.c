//
// 1.10 Exc 1.22
// Wrap long lines
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define WRAP_AT 5
#define SPACE ' '
#define EOL '\n'
#define WRAP_SYMB '-'

void putword(char *word, int pos_word, char is_first_word);

int main(int argc, char **argv) {
  unsigned char wrap_at = WRAP_AT;

  if (argc > 1) {
    wrap_at = atoi((const char *)argv[1]);
    assert(wrap_at > 0);
  }

  char word[wrap_at];
  char ch;
  int pos_line = 0;
  int pos_word = 0;

  while((ch = getchar()) != EOF) {
    assert(pos_line >= 0 && pos_line <= wrap_at);
    assert(pos_word >= 0 && pos_word <= wrap_at);

    char is_first_word = pos_word >= pos_line;
    if (ch == EOL) {
      putword(word, pos_word, is_first_word);
      putchar(EOL);
      pos_line = pos_word = 0;
      continue;
    }
    if (pos_line < wrap_at) {
      if (ch == SPACE) {
        putword(word, pos_word, is_first_word);
        pos_word = 0;
      } else {
        word[pos_word++] = ch;
      }
    } else {
      if (ch == SPACE) {
        putword(word, pos_word, is_first_word);
        putchar(EOL);
        pos_line = pos_word = 0;
        continue;
      } else {
        if (is_first_word) {
          putword(word, pos_word - 1, 1);
          putchar(WRAP_SYMB);
          putchar(EOL);
          word[0] = word[pos_word - 1];
          pos_line = pos_word = 1;
          word[pos_word++] = ch;
        } else {
          putchar(EOL);
          word[pos_word++] = ch;
          pos_line = 0;
        }
      }
    }
    pos_line++;
  }
  putword(word, pos_word, 1);
  return 0;
}

void putword(char *word, int pos_word, char is_first_word) {
  if (!is_first_word)
    putchar(SPACE);
  for (int i = 0; i < pos_word; putchar(word[i++]))
    ;
}

