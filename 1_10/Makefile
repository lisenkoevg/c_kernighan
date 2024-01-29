ifeq ($(shell uname), Linux)
  ext = .out
else
  ext = .exe
endif

# To append CFLAGS execute cmd: make CFLAGS="-Wno-unused-but-set-variable -Wno-unused-variable"...
override CFLAGS += -g -Wall -Werror

# Just experiment, run: make -n ...
# CPPFLAGS = CPPFLAGS
# TARGET_ARCH = TARGET_ARCH
# LDFLAGS = LDFLAGS
# LOADLIBES = LOADLIBES
# LDLIBS = LDLIBS

objects = detab entab wrap uncomment syntax
all: $(objects)

include ../Make_common
common_objects = $(addsuffix .o,$(common_libs_f))
uncomment syntax: $(common_objects)

include ../Make_deps
include $(addsuffix .d,$(objects) $(common))

.PHONY: clean
clean:
	rm -f *.exe *.out *.d *.o $(foreach ext,o d, $(common_dir)/*.$(ext)) $(objects) *.stackdump

test:
	bash ../runtest.sh detab '1*' 7
	bash ../runtest.sh detab '2*' 13
	bash ../runtest.sh entab '1*' 4
	bash ../runtest.sh entab '2*' 9
	bash ../runtest.sh wrap '1*' 5
	bash ../runtest.sh wrap '2*' 5
	bash ../runtest.sh wrap '3*' 20
	bash ../runtest.sh wrap 'g*' 40
	bash ../runtest.sh uncomment '1*'
	bash ../runtest.sh uncomment '2*'
	bash ../runtest.sh syntax

