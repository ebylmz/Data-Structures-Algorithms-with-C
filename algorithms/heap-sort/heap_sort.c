#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*-------------------------------------- HEAP OPERATIONS -------------------------------------- */

void swap (int * x, int * y)
{
	int tmp = *x;
	*x = *y;
	*y = tmp;
}

/* assumes that the leaf of given tree are max-heap */
void max_heapify (int * h, int size, int i)
{
	int l = i * 2 + 1;

	/* compare the leaf which has bigger value than the other with parent */
	if (l < size) 
	{
		if (l + 1 < size && h[l + 1] > h[l])
			++l;

		if (h[l] > h[i])
		{
			swap(h + i, h + l);
			max_heapify(h, size, l); /* since we might disrupt heapify of the child node, check it's heapify */
		}
	}
}

/* 	applying max_heapify function from right to left of array will create max-heap,
	(since max_heapify func. assumption we need to start with the last parents which is n/2 -1)  */
void build_max_heap (int * h, int size)
{
	int i;

	/* leafs are located indexs n / 2 to  n - 1 */
	for (i = size / 2 - 1; i >= 0; --i)
		max_heapify(h, size, i);
}

/* insertion must be applied the end of the heap, assumes that heap has cell to grow */
void insert (int * h, int * size, int data)
{
	h[*size] = data;
	++(*size);
}

/* since root is the max value, swap with the last element, check max-heapify of the new root value, decrease size */
int extract_max (int * h, int size)
{
	int r;

	if (size > 0)
	{
		r = h[0];
		swap(h, h + size - 1);
		max_heapify(h, size - 1, 0);
	}
	else 
		r = 0;

	return r;
}

void heap_sort (int * a, int size)
{
	build_max_heap(a, size);

	/* every iteration swap the heap-max with the last element, decrease size and be sure heap is still max-heap */
	while (size > 1)
	{
		extract_max(a, size);
		--size;
	}
}

/*---------------------------------------------------------------------------------------------*/

void print_arr (int * a, int size)
{
	int i;

	for (i = 0; i < size; ++i) 
		printf("%d ", a[i]);
	putchar('\n');
}	

int main (void)
{
	/* takes an array of number and sort them by using heap sort */
	int i, size = 12, * a = (int *) calloc(size, sizeof(int));

	if (a != NULL)
	{
		srand(time(NULL));

		for (i = 0; i < size; ++i)
			a[i] = rand() % 90 + 10;
		
		printf("Unsorted: ");
		print_arr(a, size);

		heap_sort(a, size);

		printf("Sorted: ");
		print_arr(a, size);

		free(a);
	}
}