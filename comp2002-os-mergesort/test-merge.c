#include <assert.h>
#include <stdio.h>
#include "mergesort.h"

int *A;
int *B;
int cutoff = 0;

int main(void)
{
    int input[] = {2, 5, 8, 1, 3, 9};
    int expected[] = {1, 2, 3, 5, 8, 9};
    int buffer[6];
    int i;

    A = input;
    B = buffer;

    /* Merge [2, 5, 8] with [1, 3, 9]. */
    merge(0, 2, 3, 5);

    for (i = 0; i < 6; i++) {
        assert(A[i] == expected[i]);
    }

    puts("PASS: merge produced [1, 2, 3, 5, 8, 9]");
    return 0;
}