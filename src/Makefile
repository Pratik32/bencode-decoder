DEPS=myheader.h

%.o:$(DEPS)
test:bencodeutils.o utils.o test.o
	gcc -o out bencodeutils.o utils.o test.o
all:
	gcc -o out bencodeutils.c utils.c test.c

clean:
	rm *.o
	rm out
