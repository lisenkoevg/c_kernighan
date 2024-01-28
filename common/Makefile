objects = common

all: $(addsuffix .o,$(objects))

include ../Make_deps

include $(addsuffix .d,$(objects))

.PHONY: clean
clean:
	rm -f *.d *.o

# test_open_file_from_arg: test_open_file_from_arg.c common.o
# 	gcc -g -o $@ common.o $<
#
# test: test_open_file_from_arg
# 	./test_open_file_from_arg.exe __common.h
#
# clean:
# 	rm -f *.exe
