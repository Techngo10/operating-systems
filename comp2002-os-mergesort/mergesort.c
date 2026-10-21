/**
 * This file implements parallel mergesort.
 */

#include <stdio.h>
#include <string.h> /* for memcpy */
#include <stdlib.h> /* for malloc */
#include "mergesort.h"

/* this function will be called by mergesort() and also by parallel_mergesort(). */
void merge(int leftstart, int leftend, int rightstart, int rightend)
{
    int i = leftstart;
    int j = rightstart;
    int k = leftstart;

    /* Compare both sorted halves and take the smaller value. */
    while (i <= leftend && j <= rightend) {
        if (A[i] <= A[j]) {
            B[k++] = A[i++];
        } else {
            B[k++] = A[j++];
        }
    }

    /* Copy anything remaining in the left half. */
    while (i <= leftend) {
        B[k++] = A[i++];
    }

    /* Copy anything remaining in the right half. */
    while (j <= rightend) {
        B[k++] = A[j++];
    }

    /* Copy the merged values back into the original array. */
    for (k = leftstart; k <= rightend; k++) {
        A[k] = B[k];
    }
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right){
}

/* this function will be called by the testing program. */
void * parallel_mergesort(void *arg) {

    // Cast into arg struct from mergesort.h
    struct argument *args = (struct argument*) arg;

    int left  = args->left;
    int right = args->right;

    int level = args->level;


    // Base case

    if(level <= 0)
    {
        my_mergesort(left, right);
    }
    else
    {
        // Todo: divide up threads
    }

    free(args);


    return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

