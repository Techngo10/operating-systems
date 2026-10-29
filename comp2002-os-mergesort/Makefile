CXX = g++
CXXFLAGS = -O3 -std=c++20 -Wall -Wextra

.PHONY: all check benchmark clean
all: correctness_test speed_test

correctness_test: correctness_test.cpp mergesort.c mergesort.h
	$(CXX) $(CXXFLAGS) -pthread -x c++ correctness_test.cpp mergesort.c -o $@

speed_test: speed_test.cpp mergesort.c mergesort.h
	$(CXX) $(CXXFLAGS) -pthread -x c++ speed_test.cpp mergesort.c -o $@

check: correctness_test
	./correctness_test

benchmark: speed_test
	./speed_test

clean:
	rm -f correctness_test speed_test