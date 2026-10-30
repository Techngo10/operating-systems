CC       = gcc
CFLAGS   = -Wall -Wpointer-arith -Wstrict-prototypes -std=gnu89 -fPIC -MMD -MP -march=native
LDLIBS   = -lpthread

CXX      = g++
CXXFLAGS = -O3 -std=c++20 -Wall -Wextra -march=native -pthread

.PHONY: all test check benchmark clean

all: test-mergesort correctness_test speed_test

# original
test-mergesort: test-mergesort.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

test-merge: test-merge.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# c++ tests
correctness_test: correctness_test.cpp mergesort.c mergesort.h
	$(CXX) $(CXXFLAGS) -x c++ correctness_test.cpp mergesort.c -o $@

speed_test: speed_test.cpp mergesort.c mergesort.h
	$(CXX) $(CXXFLAGS) -x c++ speed_test.cpp mergesort.c -o $@

# execute
test: test-merge
	./test-merge

check: correctness_test
	./correctness_test

benchmark: speed_test
	./speed_test

clean:
	rm -f *.o *.d test-mergesort test-merge correctness_test speed_test

-include $(wildcard *.d)