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

| size | cutoff | speed (ns/int) | speedup |
|-----|-----|-----|-----|
|1024|0|41.863|1.000|
|1024|1|78.108|0.536|
|1024|2|151.253|0.277|
|1024|3|354.770|0.118|
|1024|4|813.237|0.051|
|1024|5|1689.983|0.025|
|1024|6|3373.784|0.012|
|1024|7|7006.199|0.006|
|2048|0|45.443|1.000|
|2048|1|52.548|0.865|
|2048|2|76.896|0.591|
|2048|3|192.842|0.236|
|2048|4|403.950|0.112|
|2048|5|815.223|0.056|
|2048|6|1725.703|0.026|
|2048|7|3250.429|0.014|
|4096|0|50.558|1.000|
|4096|1|37.408|1.352|
|4096|2|46.755|1.081|
|4096|3|106.778|0.473|
|4096|4|202.357|0.250|
|4096|5|414.042|0.122|
|4096|6|856.471|0.059|
|4096|7|1686.587|0.030|
|8192|0|53.254|1.000|
|8192|1|34.918|1.525|
|8192|2|36.068|1.476|
|8192|3|53.394|0.997|
|8192|4|106.516|0.500|
|8192|5|210.091|0.253|
|8192|6|428.770|0.124|
|8192|7|839.483|0.063|
|16384|0|58.079|1.000|
|16384|1|34.086|1.704|
|16384|2|29.119|1.995|
|16384|3|36.624|1.586|
|16384|4|59.154|0.982|
|16384|5|110.936|0.524|
|16384|6|219.906|0.264|
|16384|7|425.544|0.136|
|32768|0|60.779|1.000|
|32768|1|33.658|1.806|
|32768|2|23.656|2.569|
|32768|3|25.364|2.396|
|32768|4|35.431|1.715|
|32768|5|59.188|1.027|
|32768|6|114.545|0.531|
|32768|7|226.438|0.268|
|65536|0|63.640|1.000|
|65536|1|35.323|1.802|
|65536|2|22.764|2.796|
|65536|3|22.156|2.872|
|65536|4|26.517|2.400|
|65536|5|36.224|1.757|
|65536|6|61.257|1.039|
|65536|7|113.577|0.560|
|131072|0|67.145|1.000|
|131072|1|38.171|1.759|
|131072|2|22.777|2.948|
|131072|3|19.582|3.429|
|131072|4|18.816|3.568|
|131072|5|25.495|2.634|
|131072|6|36.424|1.843|
|131072|7|61.144|1.098|
|262144|0|69.972|1.000|
|262144|1|40.098|1.745|
|262144|2|23.783|2.942|
|262144|3|18.797|3.723|
|262144|4|16.166|4.328|
|262144|5|19.855|3.524|
|262144|6|24.825|2.819|
|262144|7|37.551|1.863|
|524288|0|92.836|1.000|
|524288|1|42.931|2.162|
|524288|2|24.746|3.751|
|524288|3|16.759|5.539|
|524288|4|15.395|6.030|
|524288|5|16.430|5.650|
|524288|6|19.704|4.712|
|524288|7|25.917|3.582|
|1048576|0|90.007|1.000|
|1048576|1|46.101|1.952|
|1048576|2|27.264|3.301|
|1048576|3|17.238|5.221|
|1048576|4|15.151|5.941|
|1048576|5|15.783|5.703|
|1048576|6|16.514|5.450|
|1048576|7|19.732|4.562|
|2097152|0|87.812|1.000|
|2097152|1|47.677|1.842|
|2097152|2|27.992|3.137|
|2097152|3|18.977|4.627|
|2097152|4|14.927|5.883|
|2097152|5|14.491|6.060|
|2097152|6|15.019|5.847|
|2097152|7|16.920|5.190|
|4194304|0|88.319|1.000|
|4194304|1|47.611|1.855|
|4194304|2|29.256|3.019|
|4194304|3|19.389|4.555|
|4194304|4|15.874|5.564|
|4194304|5|14.805|5.966|
|4194304|6|15.165|5.824|
|4194304|7|15.905|5.553|
|8388608|0|90.724|1.000|
|8388608|1|49.073|1.849|
|8388608|2|29.583|3.067|
|8388608|3|19.500|4.652|
|8388608|4|14.824|6.120|
|8388608|5|15.005|6.046|
|8388608|6|15.050|6.028|
|8388608|7|15.446|5.874|

## Known Bugs

List known bugs that you weren't able to fix (or ran out of time to fix).


## Reflection and Self Assessment

For the initial merge function, we kept the test small enough to work through by hand. This made it easier to follow which half each value came from and compare the result against a known answer. The main detail was keeping the indices consistent: both end indices are included, and the merged values need to go back into the same section of `A`.

We also worked through how to build the test separately. The test supplies the shared arrays, while `mergesort.c` supplies the implementation, so both files need to be linked into the test executable. Keeping this first test separate gives us a starting point for checking the recursive and threaded code.

Further reflection on sequential sorting, threads, development issues and group contributions:


## Sources Used

* Supplied COMP2002 starter files and README template: https://github.com/Techngo10/operating-systems/tree/main/comp2002-os-mergesort
