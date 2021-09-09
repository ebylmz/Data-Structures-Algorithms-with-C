#include <stdio.h>

int binary_search (int a[], int size, int v) 
{
	int l = 0, m, r = size - 1;	/* left mid right */

	while (l <= r) {
		m = l + (r - l) / 2;

		if (v > a[m])	/* If v is greater, ignore left half */
			l = m + 1;
		else if (v < a[m]) /* If v is smaller, ignore right half */
			r = m - 1;
		else
			return m;
	}
    /* if we reach here, then element was not present */
	return -1;
}

int main (void)
{
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int r = binary_search(a, 10, 2);

	if (r == -1)
		printf("Does not find\n");
	else
		printf("Finded at index %d\n", r);
}