UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

all: histogram_char histogram_length

histogram_char: histogram_char.c lib.c bars.c
	@gcc -Werror -g -o histogram_char$(ext) histogram_char.c lib.c bars.c

histogram_length: histogram_length.c lib.c bars.c ../common/lib.c
	@gcc -Werror -g -o histogram_length$(ext) histogram_length.c lib.c bars.c ../common/lib.c

clean:
	rm -f *.exe *.out

test:
	../runtest.bat histogram_length
	../runtest.bat histogram_char
