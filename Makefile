# This is how you write comments
# Use gcc as a compiler
CC=gcc
# CFLAGS will be the options we'll pass to the compiler
# CFLAGS=-Wall -g -fno-pic -D__32BIT__=1

all: elfloader test1 test2 test3

elfloader: elfloader.c
	$(CC) $(CFLAGS) -g elfloader.c -o elfloader

test1: test/test1.o
	ld -N -e main -Ttext 0 -o test1 test/test1.o

test/test1.o: test/test1.c
	$(CC) -c -fno-pic -static -fno-builtin -ggdb -fno-omit-frame-pointer test/test1.c -o test/test1.o

test2: test/test2.o
	ld -N -e main -Ttext 0 -o test2 test/test2.o

test/test2.o: test/test2.c
	$(CC) -c -fno-pic -static -fno-builtin -ggdb -fno-omit-frame-pointer test/test2.c -o test/test2.o

test3: test/test3.o
	ld -N -e main -o test3 test/test3.o

test/test3.o: test/test3.c
	$(CC) -c -fno-pic -static -fno-builtin -ggdb -fno-omit-frame-pointer test/test3.c -o test/test3.o

test4: test/test3.c
	$(CC) -c test/test3.c -o test4

test-test1: elfloader test1
	./elfloader test1 3 4

test-test2: elfloader test2
	./elfloader test2 10 13

test-test3: elfloader test3
	./elfloader test3 22 19

test-test4: elfloader test4
	test/check-test4.sh

test-test5: elfloader test/check-test5.sh
	test/check-test5.sh

clean:
	rm -f *.o elfloader test1 test2 test3 test4

run: all
	./ll test1

_32bit:
	make CFLAGS="-Wall -g -fno-pic -D__32BIT__"

_64bit:
	make CFLAGS="-Wall -g -fno-pic -D__64BIT__"
