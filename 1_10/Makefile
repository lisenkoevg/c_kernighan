UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif
gcc_params = -g -Wall -Werror

objnames = detab entab
objects = $(addsuffix $(ext), $(objnames))

all: $(objects)

$(objects): %$(ext): %.c
	gcc $(gcc_params) -o $@ $<

.PHONY: clean
clean:
	rm -f $(objects)

.PHONY: Makefile

test:
	../runtest.bat detab 1\* 7
	../runtest.bat detab 2\* 13
	../runtest.bat entab \*
