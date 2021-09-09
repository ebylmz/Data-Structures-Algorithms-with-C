#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void merge (int * a, int l, int m, int r)	/* left, mid, right */
{
	int j1, j2, j0,	/* j0 is index of the related part (l to r) of the original array */
		n1 = m - l + 1, n2 = r - m;

	/* create two array as copy of original array, indexed l to m and m + 1 to r */
	int * a1 = (int *) calloc(n1, sizeof(int)),
		* a2 = (int *) calloc(n2, sizeof(int));

	if (a1 && a2)
	{
		/* the important thing is we will only use the indexes of original array l to r, so j0 starts as l */
		for (j0 = l, j1 = 0; j1 < n1; ++j1, ++j0)
			a1[j1] = a[j0];

		for (j2 = 0; j2 < n2; ++j2, ++j0) 
			a2[j2] = a[j0];

		/* every iteration select the lower one as j0th item of original list (a) */
		for (j0 = l, j1 = j2 = 0; j1 < n1 && j2 < n2; ++j0)
			a[j0] = a1[j1] < a2[j2] ? a1[j1++] : a2[j2++];

		/* in case of one list finished early the other one */
		while (j1 < n1)	a[j0++] = a1[j1++];
		while (j2 < n2) a[j0++] = a2[j2++];
	}

	if (a1 != NULL) free(a1);
	if (a2 != NULL) free(a2);
}

void merge_sort (int * a, int l, int r)
{
	int m;

	if (r > l)
	{
		/* split the current array as two half */
		m = l + (r - l) / 2; 		/* start point (l) + half of the total distance (r - l) */
		merge_sort(a, l, m);		/* sort the left half */
		merge_sort(a, m + 1, r);	/* sort the right half */
		merge(a, l, m, r);			/* merge to sorted half */
	}		
}


/*-------------------------------------------*/

void print_arr (int * a, int asize)
{
	int i;

	for (i = 0; i < asize; ++i) 
		printf("%4d ", a[i]);
	putchar('\n');
}


int main (void)
{
	int a[1000], asize = 10, i;

	srand(time(NULL));

	for (i = 0; i < asize; ++i)
		a[i] = rand() % 990 + 10;

	printf("unsorted: ");
	print_arr(a, asize);

	/* merge sort */
	printf("sorted  : ");
	merge_sort(a, 0, asize - 1);
	print_arr(a, asize);
}