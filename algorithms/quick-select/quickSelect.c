#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10

void swap (int * i, int * j) {int tmp = *i; *i = *j; *j = tmp;}

int partition (int * a, int lo, int hi) {
	int i, r, p = lo;

	r = lo + rand() % (hi - lo + 1);

	swap(a + r, a + hi);

	for (i = lo; i < hi; ++i) {
		if (a[i] <= a[hi]) {
			swap(a + p, a + i);
			++p;

		}
	}
	swap(a + p, a + hi);

	return p;
} 

/*  quickSelect sort the array same as quick sort till
	given index n returned as pivot index from partition func */
int quickSelect (int * a, int lo, int hi, int n) {
	int p, r = -1;

	if (hi == lo && n == hi)
		r = a[n];	
	else if (hi > lo) {
		p = partition(a, lo, hi);
		/* sort only the part that n placed */
		if (p == n)
			r = a[n];
		else if (n < p)
			r = quickSelect(a, lo, p - 1, n);
		else
			r = quickSelect(a, p + 1, hi, n);
	}

	return r;
}

void arr_print (int * a, int size) {
	int i;

	for (i = 0; i < size; ++i)
		printf("%d ", a[i]);
	printf("\n\n");
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

int main (void) {
	int i, r, n, a[N];

	srand(time(NULL));

	for (i = 0, n = N * N; i < N; ++i)
		a[i] = rand() % n;

	arr_print(a, N);
	r = rand() % N;	/* select random index */

	n = quickSelect(a, 0, N - 1, r);

	/* check if find index is true */
	quick_sort(a, 0, N - 1);
	arr_print(a, N);
	
	if (a[r] == n) 
		printf("TRUE IMPLEMENTATION\n");
	else
		printf("FALSE IMPLEMENTATION\n");

}