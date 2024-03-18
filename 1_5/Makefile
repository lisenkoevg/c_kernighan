UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
  ext = .out
else
  ext = .exe
endif

objects = cat_ count_all count_blank count_bytes count_lines escape join_blank split_word split_char
override CFLAGS += -g

all: $(objects)

%: %.c
	$(CC) $(CFLAGS) $^ -o $@$(ext)

clean:
	rm -f *.exe *.out

test:
	-bash ../runtest.sh count_all
	-bash ../runtest.sh split_word
	-bash ../runtest.sh split_char

