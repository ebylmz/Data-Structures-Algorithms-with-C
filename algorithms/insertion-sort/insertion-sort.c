#include <stdio.h>

void insertion_sort (int * a, int size)
{
	int i, j, key;

	for (i = 1; i < size; ++i)
	{
		j = i - 1;
		key = a[i];

		while (j >= 0 && a[j] > key) /* slip elements */
		{
			a[j + 1] = a[j];
			--j;
		}

		a[j + 1] = key;
	}
}


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


	/* insertion sort */
	printf("sorted  : ");
	insertion_sort(a, asize);
	print_arr(a, asize);

}