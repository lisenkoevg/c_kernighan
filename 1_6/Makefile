UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext := .out
else
  ext := .exe
endif
warn = $(shell grep -v \# ../warn_config | tr \\n ' ')
excludeWarn = -Wformat-nonliteral -Wstrict-prototypes
override CFLAGS += -g -Wextra -Wall -Wpedantic -Werror $(filter-out $(excludeWarn), $(warn))

objects = histogram_char histogram_length
all: $(objects)

histogram_char: histogram_char.c lib.c bars.c
	@gcc $(CFLAGS) -o $@$(ext) $^

histogram_length: histogram_length.c lib.c bars.c ../common/common.c
	@gcc $(CFLAGS) -o $@$(ext) $^

clean:
	rm -f *.exe *.out

test:
	bash ../runtest.sh histogram_length
	bash ../runtest.sh histogram_char
