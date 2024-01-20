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
	bash ../runtest.sh longest_line
	bash ../runtest.sh longer_than '*' 70
	bash ../runtest.sh remove_trailing_blanks
	bash ../runtest.sh reverse_
