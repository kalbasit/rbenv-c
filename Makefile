CFLAGS=-g -Wall

all: rbenv rbenv-hooks

strarray.o: strarray.c strarray.h
	$(CC) $(CFLAGS) -o strarray.o -c strarray.c

path.o: path.c path.h strarray.o
	$(CC) $(CFLAGS) -o path.o -c path.c

exepath.o: exepath.c exepath.h
	$(CC) $(CFLAGS) -o exepath.o -c exepath.c

rbenv.o: rbenv.c rbenv.h
	$(CC) $(CFLAGS) -o rbenv.o -c rbenv.c

main.o: main.c
	$(CC) $(CFLAGS) -o main.o -c main.c

rbenv: main.o rbenv.o strarray.o path.o exepath.o
	$(CC) -o rbenv main.o rbenv.o strarray.o path.o exepath.o

rbenv-hooks.o: rbenv-hooks.c
	$(CC) $(CFLAGS) -o rbenv-hooks.o -c rbenv-hooks.c

rbenv-hooks: rbenv-hooks.o rbenv.o strarray.o path.o exepath.o
	$(CC) -o rbenv-hooks rbenv-hooks.o rbenv.o strarray.o path.o exepath.o

clean:
	rm -fr rbenv rbenv-hooks test/test_path test/test_strarray *.o *.dSYM test/*.o test/*.dSYM

test/test.o: test/test.c test/test.h
	$(CC) $(CFLAGS) -o test/test.o -c test/test.c

test/test_path: test/test_path.c test/test.o path.o
	$(CC) $(CFLAGS) -o test/test_path test/test_path.c test/test.o path.o
	test/test_path

test/test_strarray: test/test_strarray.c test/test.o strarray.o
	$(CC) $(CFLAGS) -o test/test_strarray test/test_strarray.c test/test.o strarray.o
	test/test_strarray

test: test/test_path test/test_strarray

install: rbenv rbenv-hooks
	cp rbenv rbenv-hooks $(HOME)/.rbenv/libexec
