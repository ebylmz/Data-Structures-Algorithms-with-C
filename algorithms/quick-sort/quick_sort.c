#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

#define N 100

void swap (int * a, int * b) {int tmp = *a; *a = *b; *b = tmp;} 


/*	Hoare partition
 	pivot selected as first element */
int partition0 (int * a, int lo, int hi) {
	int start = lo, end = hi, piv = a[lo];

	while (start < end) {
		/*  start and end indexes holds the wrong values that's need to swap
			start index holds the value that larger than pivot and end does reverse */
		while (a[start] <= piv)
			++start;

		while (a[end] > piv)
			--end;

		if (start < end)
			swap(a + start, a + end);
	}
	swap(a + lo, a + end);

	return end;
} 

/* 	Lomuto partition
	pivot selected randomly and to implementation placed ed high index */
int partition (int * a, int lo, int hi) {
	int i, r, p = lo;
	/* 	index p tracks the pivot point,
	 	end of the function we put there pivot value */

	/* select randomly the index of pivot */
	r = lo + rand() % (hi - lo + 1);
	swap(a + r, a + hi);

	for (i = lo; i < hi; ++i) {
		/* all the less or equal values placed left of pivot */
		if (a[i] <= a[hi]) {
			if (p != i) 
				swap(a + p, a + i);
			++p;
		}
	}
	swap(a + p, a + hi); /* locate pivot as it's sorted place */

	return p;
}

void quick_sort (int * a, int lo, int hi) {
	int p;

	if (lo < hi) {
		/*  after partition array diveded into imaginary two piece,
			left side of p less, right side bigger than it's value 	*/
		p = partition(a, lo, hi);

		quick_sort(a, lo, p - 1);	
		quick_sort(a, p + 1, hi);	
	}
}

void arr_print (int * a, int size) {
	int i;

	for (i = 0; i < size; ++i)
		printf("%d ", a[i]);
	printf("\n\n");
}

int main (void) {
	int i, n, a[N];

	srand(time(NULL));

	for (i = 0, n = N * N; i < N; ++i)
		a[i] = rand() % n;
	/*
	for (i = 0; i < N; ++i)
		a[i] = N - i;
	*/

	arr_print(a, N);
	quick_sort(a, 0, N - 1);
	arr_print(a, N);
}