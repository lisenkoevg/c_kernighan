all: histogram_char histogram_length

histogram_char: histogram_char.c lib.c bars.c lib.h bars.h
	@gcc -Werror -g -o histogram_char.exe histogram_char.c lib.c bars.c

histogram_length: histogram_length.c lib.c bars.c lib.h bars.h
	@gcc -Werror -g -o histogram_length.exe histogram_length.c lib.c bars.c

clean:
	rm *.exe

test:
	../runtest.bat histogram_length
	../runtest.bat histogram_char
