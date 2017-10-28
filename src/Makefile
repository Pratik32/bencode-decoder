DEPS=myheader.h bencodeutils.h
objects = bencodeutils.o utils.o test.o
%.o:$(DEPS)


test:$(objects)
	gcc -o out $(objects)
all:
	gcc -o out bencodeutils.c utils.c test.c

clean:
	rm *.o
	rm out
