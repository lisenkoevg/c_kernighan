UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

# warn = -Wno-unused-but-set-variable -Wno-unused-variable
gcc_params = -g -Wall -Werror $(warn)

objects = detab entab wrap

all: $(objects)

# include ../common/Makefile

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
	../runtest.bat wrap 1\* 5
	../runtest.bat wrap 2\* 5
	../runtest.bat wrap 3\* 20
