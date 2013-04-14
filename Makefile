CFLAGS=-g -Wall

all: rbenv

strarray.o: strarray.c strarray.h
	$(CC) $(CFLAGS) -o strarray.o -c strarray.c

path.o: path.c path.h strarray.o
	$(CC) $(CFLAGS) -o path.o -c path.c strarray.o

rbenv.o: rbenv.c rbenv.h
	$(CC) $(CFLAGS) -o rbenv.o -c rbenv.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

rbenv: main.o rbenv.o strarray.o path.o
	$(CC) -o rbenv main.o rbenv.o strarray.o path.o

clean:
	rm -fr rbenv *.o *.dSYM test/*.o test/*.dSYM

test/test.o: test/test.c test/test.h
	$(CC) $(CFLAGS) -o test/test.o -c test/test.c

test/test_path: test/test_path.c test/test.o path.o
	$(CC) $(CFLAGS) -o test/test_path test/test_path.c test/test.o path.o
	test/test_path

test/test_strarray: test/test_strarray.c test/test.o strarray.o
	$(CC) $(CFLAGS) -o test/test_strarray test/test_strarray.c test/test.o strarray.o
	test/test_strarray

test: test/test_path test/test_strarray
