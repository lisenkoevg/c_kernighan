UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif
gcc_params = -g -Wall -Werror

all: detab

detab: detab.c
	gcc $(gcc_params) -o detab$(ext) detab.c

clean:
	rm -f *.exe
