## Assignment 2 - Programming Task

* Authors: Wenqing, Lachlan, Elijah
* Group name: 78

## Overview

This program sorts random integers using merge sort, with POSIX threads used to sort separate halves in parallel. A cutoff level controls when it switches to sequential sorting, and the test program checks the final order and reports the time taken.


## Manifest

* `mergesort.c` - Implements merging, sequential merge sort, parallel merge sort and thread argument allocation.
* `mergesort.h` - Declares the sorting functions, argument structure and shared arrays.
* `test-mergesort.c` - Generates input, runs the full sort, checks ascending order and reports sorting time.
* `test-merge.c` - Tests merging separately using two small, sorted halves.
* `Makefile` - Builds the programs, runs the merge test and removes generated files.
* `README.template` - Contains the project documentation.


## Building the project

The project needs GCC, Make and a Linux/POSIX environment with pthread support. On Windows, use a Linux environment such as WSL because the supplied test program uses Unix headers and functions.

From the `comp2002-os-mergesort` folder, build the full sorting program with:

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


## Features and usage

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


## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).


## Reflection and Self Assessment

For the initial merge function, we kept the test small enough to work through by hand. This made it easier to follow which half each value came from and compare the result against a known answer. The main detail was keeping the indices consistent: both end indices are included, and the merged values need to go back into the same section of `A`.

We also worked through how to build the test separately. The test supplies the shared arrays, while `mergesort.c` supplies the implementation, so both files need to be linked into the test executable. Keeping this first test separate gives us a starting point for checking the recursive and threaded code.

Further reflection on sequential sorting, threads, development issues and group contributions:

To be completed by the group based on the work and testing carried out.


## Sources Used

* Supplied COMP2002 starter files and README template: https://github.com/Techngo10/operating-systems/tree/main/comp2002-os-mergesort

* ChatGPT (openAI) was used to with testing and result tables

Group members should add any other sources they actually used, including documentation, websites and textbook references.
