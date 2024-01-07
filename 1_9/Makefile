obj = longest_line.c longer_than.c lib.c

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

all: longest_line longer_than

longest_line: longest_line.c lib.c
	gcc -o longest_line$(ext) -g -Wall -Werror longest_line.c

clean:
	rm *.exe

test:
	../runtest.bat longest_line
	../runtest.bat longer_than 70

