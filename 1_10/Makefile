UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

gcc_params = -g -Wall -Werror
objects = detab entab

all: $(objects)

# include ../common/Makefile

entab: ../common/common.o

$(objects): %: %.c
	gcc $(gcc_params) -o $@$(ext) $<

.PHONY: clean
clean:
	rm -f *.exe

.PHONY: Makefile

test:
	../runtest.bat detab 1\* 7
	../runtest.bat detab 2\* 13
	../runtest.bat entab 1\* 4
	../runtest.bat entab 2\* 9
