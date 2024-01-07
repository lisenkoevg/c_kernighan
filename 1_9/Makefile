obj = longest_line

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  out = $(obj).out
else
  out = $(obj).exe
endif

all: $(obj)

longest_line: $(obj).c
	gcc -o $(out) -g -Wall -Werror $(obj).c

clean:
	rm *.exe

test:
	../runtest.bat $(obj)

