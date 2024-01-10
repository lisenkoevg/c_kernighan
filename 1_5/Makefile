UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

all: cat_ count_all count_blank count_bytes count_lines escape join_blank split_word split_char

cat_: cat_.c
	gcc cat_.c -o cat_$(ext)

count_all: count_all.c
	gcc count_all.c -o count_all$(ext)

count_blank: count_blank.c
	gcc count_blank.c -o count_blank$(ext)

count_bytes: count_bytes.c
	gcc count_bytes.c -o count_bytes$(ext)

count_lines: count_lines.c
	gcc count_lines.c -o count_lines$(ext)

escape: escape.c
	gcc escape.c -o escape$(ext)

join_blank: join_blank.c
	gcc join_blank.c -o join_blank$(ext)

split_word: split_word.c
	gcc split_word.c -o split_word$(ext)

split_char: split_char.c
	gcc split_char.c -o split_char$(ext)

clean:
	rm -f *.exe *.out

test:
	../runtest.bat count_all
	../runtest.bat split_word
	../runtest.bat split_char

.PHONY: Makefile

