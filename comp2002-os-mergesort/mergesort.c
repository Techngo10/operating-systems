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

    // Base cases

    
    if(left >= right)
    {
        free(args);
        return NULL;
    }


    if(level <= 0)
    {
        my_mergesort(left, right);
    }
    else
    {
        // Divide up threads
        pthread_t thread1, thread2;
        
        // Get middle for merge sort
        int middle = left + (right - left) / 2;

        struct argument *arg1 = buildArgs(left, middle, level - 1);
        struct argument *arg2 = buildArgs(middle + 1, right, level - 1);

        // Split off threads recursively
        // (call pthread_create(), which will then call parallel_mergesort())

        // Optimisation, run parallel mergesort on this thread too

        pthread_create(&thread1, NULL, parallel_mergesort, arg1);
        parallel_mergesort(arg2);
        
        // Work is done, join back and merge results
        pthread_join(thread1, NULL);
    }

    free(args);


    return NULL;
}

/* we build the argument for the parallel_mergesort function. */
struct argument * buildArgs(int left, int right, int level){
		return NULL;
}

