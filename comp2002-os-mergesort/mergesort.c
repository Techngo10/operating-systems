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
	while (i <= leftend && j <= rightend) 
		if (A[i] <= A[j])
			B[k++] = A[i++];
		else
			B[k++] = A[j++];

	/* Copy anything remaining in the left half. */
	while (i <= leftend)
		B[k++] = A[i++];

	/* Copy anything remaining in the right half. */
	while (j <= rightend)
		B[k++] = A[j++];

	/* Copy the merged values back into the original array. */
	memcpy(A + leftstart, B + leftstart, (rightend - leftstart + 1) * sizeof(int));
}

/* this function will be called by parallel_mergesort() as its base case. */
void my_mergesort(int left, int right)
{
	const int size = right - left + 1;
	const int half = size / 2;
	if (size < 2)return;
	my_mergesort(left	   , left + half - 1);
	my_mergesort(left + half, right		  );
	merge(left, left + half - 1, left + half, right);
}

/* this function will be called by the testing program. */
void* parallel_mergesort(void *arg) 
{
	struct argument *args = (struct argument*) arg;
	const int left   = args->left;
	const int right  = args->right;
	const int size   = right - left + 1;
	const int half   = size / 2;
	const int level  = args->level;
	if (size < 2)return 0;
	if (level < cutoff)
	{
		struct argument arg1 = {.left = left       , .right = left + half - 1, .level = level + 1};//place args on stack instead of calling buildArgs
		struct argument arg2 = {.left = left + half, .right = right          , .level = level + 1};//because buildArgs malloc
		pthread_t thread;
		pthread_create(&thread, 0, parallel_mergesort, &arg2);
		parallel_mergesort(&arg1);
		pthread_join(thread, 0);
		merge(left, left + half - 1, left + half, right);
	}
	else
		my_mergesort(left, right);
	return 0;
}

/* we build the argument for the parallel_mergesort function. */
struct argument* buildArgs(int left, int right, int level)
{
	struct argument* result = (struct argument*)malloc(sizeof(struct argument));
	result->left = left;
	result->right = right;
	result->level = level;
	return result;
}