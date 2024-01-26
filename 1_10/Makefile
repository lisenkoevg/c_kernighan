ifeq ($(shell uname), Linux)
  ext = .out
else
  ext = .exe
endif

warn=-Wno-unused-but-set-variable -Wno-unused-variable
CFLAGS+=-g -Wall -Werror $(warn)

objects = detab entab wrap uncomment
common = ../common/common
common_all = $(foreach ext,o c h,$(common).$(ext))
all: $(objects)

uncomment: addLib = $(addsuffix .o,$(common))
uncomment: $(common_all)

include ../common/Makefile

$(objects): %: %.c
	gcc $(CFLAGS) -o $@$(ext) $< $(addLib)

.PHONY: clean
clean:
	rm -f *.exe *.out

test:
# 	bash ../runtest.sh detab '1*' 7
# 	bash ../runtest.sh detab '2*' 13
# 	bash ../runtest.sh entab '1*' 4
# 	bash ../runtest.sh entab '2*' 9
# 	bash ../runtest.sh wrap '1*' 5
# 	bash ../runtest.sh wrap '2*' 5
# 	bash ../runtest.sh wrap '3*' 20
# 	bash ../runtest.sh wrap 'g*' 40
	bash ../runtest.sh uncomment '1*'
	bash ../runtest.sh uncomment '2*'

