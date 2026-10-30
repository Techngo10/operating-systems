## Assignment 2 - Programming Task

* Authors: Wenqing Liu (a1944096), Lachlan, Elijah Ngo (a1924791)
* Group name: 78

## Overview

This program uses POSIX threads to implement parallel merge sort to sort an array of integers. `cutoff` controls the switch from parallel to sequential sorting, and `correctness_test.cpp` checks for correctness and `speed_test.cpp` prints benchmark result into markdown tables.

## Manifest

|file|what it does|
|---|---|
|`mergesort.h`|declares the sorting functions, argument structure and shared arrays|
|`mergesort.c`|implement everything in `mergesort.h`|
|`correctness_test.cpp`|checks algo correctness|
|`speed_test.cpp`|benchmark algo, print result in markdown tables|
|`Makefile` |compiles `correctness_test.cpp` and `speed_test.cpp` (linux)|
|`correctness_test.bat`|compiles and executes `correctness_test.cpp` (windows)|
|`speed_test.bat`|compiles and executes `speed_test.cpp` (windows)|

## Building (and Executing) the project

### linux

`cd` into `comp2002-os-mergesort`

**build and run `correctness_test.cpp`**

```bash
g++ -o3 -march=native -std=c++20 "mergesort.c" "correctness_test.cpp" -o correctness_test
./correctness_test
```

**build and run `speed_test.cpp`**

```bash
g++ -o3 -march=native -std=c++20 "mergesort.c" "speed_test.cpp" -o speed_test
./speed_test
```

### windows

#### build g++ from https://github.com/gcc-mirror/gcc.git

#### build and run

    .\comp2002-os-mergesort\correctness_test.bat
    .\comp2002-os-mergesort\speed_test.bat

## Features

Merging uses the temporary array `B` before copying the result back into `A`. The parallel version waits for its child threads before merging their results. If a child argument cannot be allocated or a thread cannot be created, that half is sorted sequentially instead.

## Testing

### correctness_test.cpp

1. loops over $\{\text{size}\in [0,10000]\} \times \{\text{cutoff}\in [0,7]\}$
2. for each pair fill A with random ints, fill another array `expected` of same `size` with same ints as A
3. sort `A` with `parallel_mergesort`
4. sort `expected` with `std::sort`
5. if `A!=expected`, then test fails
6. print `"success"` if 0 test fails

### speed_test.cpp

1. loops over $\{\text{size}\in \text{1<<i} | \text{i}\in[10,24)\} \times \{\text{cutoff}\in [0,7]\}$
2. for each pair fill A with random ints
3. times execution time of `parallel_mergesort` for `repeat=8` times
4. print `Speed (ints/ms)` table in markdown
5. print `Speedup` table in markdown

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

### `mergesort.h` is poorly designed as library code (its fine as is as assignment code)

1. theres no way to pass `which array to sort` as argument
2. global variable (when it can be avoided by letting users pass array as arg)
3. `buildArgs` requires heap allocation (which can be avoided by having `argument` as stack variable)

### potential optimization opportunity exists, but implementing it risks violating rubric, or confuses grader, or both

> see my post on `https://edstem.org/au/courses/38313/discussion/3682500` for detail

1. place args on stack stead of calling `buildArgs` to skip `malloc`/`free`
2. spawn only 1 extra thread per `parallel_mergesort` call

**(skips error checking for clarity)**

instead of
```c++
struct argument* arg1 = buildArgs(left       , left + half - 1, level + 1);
struct argument* arg2 = buildArgs(left + half, right          , level + 1);
pthread_t thread1, thread2;
pthread_create(&thread1, 0, parallel_mergesort, arg1);
pthread_create(&thread2, 0, parallel_mergesort, arg2);
pthread_join(thread1, 0); free(arg1);
pthread_join(thread2, 0); free(arg2);
```
i do this instead
```c++
struct argument arg1 = {.left = left       , .right = left + half - 1, .level = level + 1};
struct argument arg2 = {.left = left + half, .right = right          , .level = level + 1};
pthread_t thread;
pthread_create(&thread, 0, parallel_mergesort, &arg2);
parallel_mergesort(&arg1);
pthread_join(thread, 0);
```

## Sources Used

* Supplied COMP2002 starter files and README template: https://github.com/Techngo10/operating-systems/tree/main/comp2002-os-mergesort
