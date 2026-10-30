## Assignment 2 - Programming Task

* Authors: Wenqing, Lachlan, Elijah
* Group name: 78

## Overview

This program uses POSIX threads to implement parallel merge sort to sort an array of random integers. A cutoff level controls the switch from parallel to sequential sorting, and the test program checks the order for correctness and measures the run time.

## Manifest

* `mergesort.c` - Implements merging, sequential merge sort, parallel merge sort and thread argument allocation.
* `mergesort.h` - Declares the sorting functions, argument structure and shared arrays.
* `test-mergesort.c` - Generates input, runs the full sort, checks ascending order and reports sorting time.
* `test-merge.c` - Tests merging separately using two small, sorted halves.
* `Makefile` - Builds the programs, runs the merge test and removes generated files.
* `README.template` - Contains the project documentation.


## Building the project

This project requires GCC, Make, and a Linux environment with pthread support. If on Windows, use an environment like WSL, as the supplied test program uses Unix headers and functions.

From the `comp2002-os-mergesort` folder, build the sorting program using:

```bash
make
```

To build and run the separate merge test:

```bash
make test
```

To remove the generated files:

```bash
make clean
```


## Features and Usage

Run the full program with three arguments:

```bash
./test-mergesort <input size> <cutoff level> <seed>
```

* Input size is the number of integers to sort and must be at least 2.
* Cutoff level controls the depth of thread creation. The main thread starts at level 0, so a cutoff of 0 uses sequential sorting. Higher cutoffs allow threads to sort the halves until the cutoff is reached.
* Seed controls the random input. Using the same size and seed lets us compare cutoff levels with the same values.

For example:

```bash
./test-mergesort 100000 0 42
./test-mergesort 100000 2 42
```

These are example commands, rather than recorded test results. The program prints the number of elements and sorting time in seconds if the output is sorted, or reports a sorting failure otherwise.

Merging uses the temporary array `B` before copying the result back into `A`. The parallel version waits for its child threads before merging their results. If a child argument cannot be allocated or a thread cannot be created, that half is sorted sequentially instead.


## Testing

For the initial merge work, we added a small test in `test-merge.c` to check merging separately from the recursive and threaded parts. The input is `{2, 5, 8, 1, 3, 9}`, containing two sorted halves: `{2, 5, 8}` and `{1, 3, 9}`.

The test sets up `A` and a six-element temporary buffer `B`, then calls `merge(0, 2, 3, 5)`. Each result is compared against `{1, 2, 3, 5, 8, 9}` using `assert`. A mismatch stops the test; if all checks pass, it prints `PASS: merge produced [1, 2, 3, 5, 8, 9]`.

This checks that values from both halves are placed in order and that the remaining value from the right half is copied across. It is only a starting test: it does not cover duplicates, uneven halves, or a merge starting at a nonzero index. It does not test recursion or threads. The assertions must be enabled; the supplied Makefile does not define `NDEBUG`.

Initial merge test run and actual result:

The test passed and printed PASS: merge produced [1, 2, 3, 5, 8, 9], confirming that the two sorted halves were merged into the expected array.

Sequential merge sort testing:

We ran test-mergesort.c witht the arguments 100000 0 42. This generated 100,000 integers using seed 42. A cutoff of 0 used sequential merge sort. The program reported successful sorting and printed the elapsed time.

| Input size | Cutoff | Seed | Time (seconds) |
|   ---  | - | -- |  --  |
| 100000 | 0 | 42 | 0.02 |

Parallel merge sort and cutoff testing:

We repeated the test with arguments 100000 2 42 to test parallel merge sort with a cutoff level of 2. Keeping the input size and seed unchanged gave us the same input as the sequential test. The program again reported successful sorting.

| Input size | Cutoff | Seed | Time (seconds) |
|   ---  | - | -- |  --  |
| 100000 | 2 | 42 | 0.01 |

Timing comparisons and additional cases:

| Input size | Cutoff | Seed | Time (seconds) |
|   ---  | - | -- |  --  |
| 100000 | 0 | 42 | 0.02 |
| 100000 | 2 | 42 | 0.01 |


| Input size | Cutoff | Seed | What it checks | Result | Time (s) |
|---|---|---|---|---|---|
| 2 | 0 | 42 | Smallest supported input using sequential sorting | Passed | 0.00 |
| 2 | 2 | 42 | Threaded sorting stops correctly for tiny input | Passed | 0.00 |
| 7 | 0 | 42 | Sequential sorting handles uneven halves | Passed | 0.00 |
| 7 | 2 | 42 | Parallel sorting handles uneven halves | Passed | 0.00 |
| 100000 | 1 | 42 | Sorting works with a cutoff level of 1 | Passed | 0.02 |
| 100000 | 3 | 123 | Sorting works with a deeper cutoff and a different seed | Passed | 0.01 |
| 1 | 0 | 42 | Input below the minimum size is rejected | Rejected as expected | N/A |

These tests checked small inputs, uneven halves, different cutoff levels
and invalid input handling. Times of 0.00 seconds reflect the displayed
precision rather than zero execution time.


| Input size | Cutoff | Seed | Time (s) |
|---|---|---|---|
| 1000000 | 0 | 42 | 0.28 |
| 1000000 | 1 | 42 | 0.21 |
| 1000000 | 2 | 42 | 0.20 |
| 1000000 | 3 | 42 | 0.17 |

We compared sequential and parallel sorting using one million integers
with the same random seed. In these runs, the time decreased from
0.28 seconds with cutoff 0 to 0.17 seconds with cutoff 3. These are
single-run measurements, so repeated runs would be needed to establish
whether the improvement is consistent.


### speed_test.cpp Results

### Speed (ints/ms)

| Speed (ints/ms) | cutoff=0 | cutoff=1 | cutoff=2 | cutoff=3 | cutoff=4 | cutoff=5 | cutoff=6 | cutoff=7 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ints=1024 | 38.442 | 13.970 | 6.037 | 2.542 | 1.105 | 0.635 | 0.283 | 0.133 |
| ints=2048 | 35.718 | 23.598 | 13.052 | 5.896 | 2.685 | 1.329 | 0.595 | 0.277 |
| ints=4096 | 32.824 | 34.904 | 23.812 | 11.791 | 6.005 | 2.465 | 1.220 | 0.577 |
| ints=8192 | 30.301 | 39.072 | 33.563 | 17.845 | 10.013 | 4.722 | 2.278 | 1.079 |
| ints=16384 | 29.615 | 46.355 | 49.198 | 38.197 | 18.606 | 9.921 | 4.672 | 2.064 |
| ints=32768 | 27.324 | 47.113 | 64.020 | 59.956 | 38.279 | 18.963 | 9.683 | 4.413 |
| ints=65536 | 24.897 | 45.387 | 68.764 | 75.327 | 56.484 | 33.559 | 17.015 | 8.279 |
| ints=131072 | 23.594 | 43.875 | 74.655 | 96.226 | 88.379 | 55.704 | 32.049 | 15.708 |
| ints=262144 | 23.240 | 42.250 | 74.006 | 99.159 | 108.078 | 84.485 | 54.065 | 29.834 |
| ints=524288 | 22.588 | 40.970 | 69.345 | 104.811 | 121.755 | 121.436 | 82.626 | 50.045 |
| ints=1048576 | 22.152 | 39.600 | 69.229 | 104.459 | 132.748 | 145.817 | 119.858 | 78.942 |
| ints=2097152 | 21.070 | 38.684 | 67.890 | 104.688 | 136.382 | 154.053 | 148.425 | 113.098 |
| ints=4194304 | 19.792 | 37.128 | 65.763 | 102.723 | 137.123 | 155.762 | 153.185 | 143.570 |
| ints=8388608 | 19.812 | 35.629 | 63.226 | 99.135 | 135.445 | 158.080 | 151.906 | 155.637 |

### Speedup

| Speedup | cutoff=0 | cutoff=1 | cutoff=2 | cutoff=3 | cutoff=4 | cutoff=5 | cutoff=6 | cutoff=7 |
|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| ints=1024 | 1.000 | 0.363 | 0.157 | 0.066 | 0.029 | 0.017 | 0.007 | 0.003 |
| ints=2048 | 1.000 | 0.661 | 0.365 | 0.165 | 0.075 | 0.037 | 0.017 | 0.008 |
| ints=4096 | 1.000 | 1.063 | 0.725 | 0.359 | 0.183 | 0.075 | 0.037 | 0.018 |
| ints=8192 | 1.000 | 1.289 | 1.108 | 0.589 | 0.330 | 0.156 | 0.075 | 0.036 |
| ints=16384 | 1.000 | 1.565 | 1.661 | 1.290 | 0.628 | 0.335 | 0.158 | 0.070 |
| ints=32768 | 1.000 | 1.724 | 2.343 | 2.194 | 1.401 | 0.694 | 0.354 | 0.161 |
| ints=65536 | 1.000 | 1.823 | 2.762 | 3.026 | 2.269 | 1.348 | 0.683 | 0.333 |
| ints=131072 | 1.000 | 1.860 | 3.164 | 4.078 | 3.746 | 2.361 | 1.358 | 0.666 |
| ints=262144 | 1.000 | 1.818 | 3.184 | 4.267 | 4.651 | 3.635 | 2.326 | 1.284 |
| ints=524288 | 1.000 | 1.814 | 3.070 | 4.640 | 5.390 | 5.376 | 3.658 | 2.216 |
| ints=1048576 | 1.000 | 1.788 | 3.125 | 4.716 | 5.993 | 6.583 | 5.411 | 3.564 |
| ints=2097152 | 1.000 | 1.836 | 3.222 | 4.969 | 6.473 | 7.311 | 7.044 | 5.368 |
| ints=4194304 | 1.000 | 1.876 | 3.323 | 5.190 | 6.928 | 7.870 | 7.740 | 7.254 |
| ints=8388608 | 1.000 | 1.798 | 3.191 | 5.004 | 6.836 | 7.979 | 7.667 | 7.856 |

## Known Bugs

none


## Reflection and Self Assessment

For the initial merge function, we kept the test small enough to work through by hand. This made it easier to follow which half each value came from and compare the result against a known answer. The main detail was keeping the indices consistent: both end indices are included, and the merged values need to go back into the same section of `A`.

We also worked through how to build the test separately. The test supplies the shared arrays, while `mergesort.c` supplies the implementation, so both files need to be linked into the test executable. Keeping this first test separate gives us a starting point for checking the recursive and threaded code.

Further reflection on sequential sorting, threads, development issues and group contributions:


## Sources Used

* Supplied COMP2002 starter files and README template: https://github.com/Techngo10/operating-systems/tree/main/comp2002-os-mergesort
