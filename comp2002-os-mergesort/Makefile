CC = gcc
CFLAGS = -Wall -Wpointer-arith -Wstrict-prototypes -std=gnu89 -fPIC -MMD -MP -lpthread

all: test-mergesort

#This builds an executable 
test-mergesort: test-mergesort.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $^

# Build the simple merge test with the merge implementation.
test-merge: test-merge.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $^

# Run our merge test.

.PHONY: test clean

test: test-merge
	./test-merge

clean:
	/bin/rm -f *.o *.d test-mergesort test-merge