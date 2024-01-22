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
	bash ../runtest.sh detab '1*' 7
	bash ../runtest.sh detab '2*' 13
	bash ../runtest.sh entab '1*' 4
	bash ../runtest.sh entab '2*' 9
	bash ../runtest.sh wrap '1*' 5
	bash ../runtest.sh wrap '2*' 5
	bash ../runtest.sh wrap '3*' 20
	bash ../runtest.sh wrap 'g*' 40
