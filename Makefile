install:
	mkdir -p bin
	cc -Wall -g src/evy.c -o bin/evy
	rm -fR bin/evy.dSYM
clean:
	rm -fR bin
