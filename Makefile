CFLAGS=-g -Wall
COMMANDS=rbenv rbenv-hooks rbenv-version-file rbenv-version-file-read rbenv-which
LIBRARIES=exepath.o path.o rbenv.o strarray.o

all: $(COMMANDS)

exepath.o: exepath.c exepath.h
	$(CC) $(CFLAGS) -o exepath.o -c exepath.c

path.o: path.c path.h strarray.o
	$(CC) $(CFLAGS) -o path.o -c path.c

rbenv.o: rbenv.c rbenv.h
	$(CC) $(CFLAGS) -o rbenv.o -c rbenv.c

strarray.o: strarray.c strarray.h
	$(CC) $(CFLAGS) -o strarray.o -c strarray.c

rbenv: main.c $(LIBRARIES)
	$(CC) $(CFLAGS) -o rbenv main.c $(LIBRARIES)

rbenv-hooks: rbenv-hooks.c $(LIBRARIES)
	$(CC) $(CFLAGS) -o rbenv-hooks rbenv-hooks.c $(LIBRARIES)

rbenv-version-file: rbenv-version-file.c $(LIBRARIES)
	$(CC) $(CFLAGS) -o rbenv-version-file rbenv-version-file.c $(LIBRARIES)

rbenv-version-file-read: rbenv-version-file-read.c
	$(CC) $(CFLAGS) -o rbenv-version-file-read rbenv-version-file-read.c

rbenv-which: rbenv-which.c $(LIBRARIES)
	$(CC) $(CFLAGS) -o rbenv-which rbenv-which.c $(LIBRARIES)

clean:
	rm -f $(COMMANDS)
	rm -fr test/test_path test/test_strarray *.o *.dSYM test/*.o test/*.dSYM

test/test.o: test/test.c test/test.h
	$(CC) $(CFLAGS) -o test/test.o -c test/test.c

test/test_path: test/test_path.c test/test.o path.o
	$(CC) $(CFLAGS) -o test/test_path test/test_path.c test/test.o path.o
	test/test_path

test/test_strarray: test/test_strarray.c test/test.o strarray.o
	$(CC) $(CFLAGS) -o test/test_strarray test/test_strarray.c test/test.o strarray.o
	test/test_strarray

test: test/test_path test/test_strarray

install: $(COMMANDS)
	cp $(COMMANDS) $(HOME)/.rbenv/libexec
