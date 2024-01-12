UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif
gcc_params = -g -Wall -Werror

objects = longest_line longer_than remove_trailing_blanks reverse_

all: $(objects)

$(objects): lib.c ../common/common.h

$(objects): %: %.c
	gcc -o $@$(ext) $(gcc_params) $< ../common/common.c

.PHONY: clean
clean:
	rm -f *.exe

test:
	../runtest.bat longest_line
	../runtest.bat longer_than \* 70
	../runtest.bat remove_trailing_blanks
	../runtest.bat reverse_
