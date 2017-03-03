CC=gcc
CFLAGS=-I.
DEPS = workHeap.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: workHeap.o workHeap.o
	gcc -o hellomake workHeap.o -I.
