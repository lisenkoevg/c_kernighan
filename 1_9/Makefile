UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif
gcc_params = -g -Wall -Werror

all: longest_line longer_than remove_trailing_blanks reverse_

longest_line: longest_line.c lib.c
	gcc -o longest_line$(ext) $(gcc_params) longest_line.c

longer_than: longer_than.c lib.c
	gcc -o longer_than$(ext) $(gcc_params) longer_than.c

remove_trailing_blanks: remove_trailing_blanks.c lib.c ../common/lib.c
	gcc -o remove_trailing_blanks$(ext) $(gcc_params) remove_trailing_blanks.c ../common/lib.c

reverse_: reverse_.c lib.c
	gcc -o reverse_$(ext) $(gcc_params) reverse_.c

clean:
	rm *.exe

test:
	../runtest.bat longest_line
	../runtest.bat longer_than 70
	../runtest.bat remove_trailing_blanks
	../runtest.bat reverse_
