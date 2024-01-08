UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

all: longest_line longer_than remove_trailing_blanks

longest_line: longest_line.c lib.c
	gcc -o longest_line$(ext) -g -Wall -Werror longest_line.c

longer_than: longer_than.c lib.c
	gcc -o longer_than$(ext) -g -Wall -Werror longer_than.c

remove_trailing_blanks: remove_trailing_blanks.c lib.c ../common/lib.c
	gcc -o remove_trailing_blanks$(ext) -g -Wall -Werror remove_trailing_blanks.c ../common/lib.c

clean:
	rm *.exe

test:
	../runtest.bat longest_line
	../runtest.bat longer_than 70
	../runtest.bat remove_trailing_blanks

