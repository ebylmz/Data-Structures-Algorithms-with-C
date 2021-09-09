#include <stdio.h>
#include <stdlib.h>

int a_max (int * a, int size)
{
	int i, r = a[0];

	for (i = 1; i < size; ++i)
		if (a[i] > r) r = a[i];
	return r;
}

/* 	--counting-sort properties 
	1. Counting sort is efficient if the range of input data is not significantly greater than the number of objects to be sorted. 
	Consider the situation where the input sequence is between range 1 to 10K and the data is 10, 5, 10K, 5K. 
	2. It is not a comparison based sorting. It running time complexity is O(n) with space proportional to the range of data. 
	3. It is often used as a sub-routine to another sorting algorithm like radix sort. 
	4. Counting sort uses a partial hashing to count the occurrence of the data object in O(1). 
	5. Counting sort can be extended to work for negative inputs also. Converting min number to zero by adding and end of the function substracting.
	6. Not for floating-point numbers, it can be integer or char 
	
	--algorithm
	1. take the max value as variable k
	2. allocate k + 1 sized empty array to count the numbers
	3. allocate a new arr to sort given original array (after sorting we copy to original array)
	4. count the number of distinct values by incrementing the index of their value in count array
	5. update counting array as a[n] = a[n] + a[n - 1], for keeping track of indexes
	6. start from end of the original array and put the values to new array by choosing index at count arr
	7. copy the new arr to the original array
*/
void * counting_sort (int * a, int size, int k)
{
	int i,  * r = (int *) calloc(size, sizeof(int)),
		* count = (int *) calloc(k + 1, sizeof(int));
		
	if (r && count)
	{
		for (i = 0; i < size; ++i)
			++count[a[i]];

		/* do not forget size of the count arr is max value + 1  */
		for (i = 1; i < k + 1; ++i)
			count[i] += count[i - 1];

		/* index = count[a[i]] - 1 (decrease 1, to convert from size to index value (0 based indexed))	*/
		for (i = size - 1; i >= 0; --i)
			r[--count[a[i]]] = a[i];

		for (i = 0; i < size; ++i)
			a[i] = r[i];
	} 

	if (count != NULL) free(count);
	if (r != NULL) free(r);
}

void a_push (int * a, int data, int * size)
{
	a[*size] = data;
	++(*size);
}

void a_print (int * a, int size)
{
	int i = 0;

	while (i < size)
		printf("%d ", a[i++]);
	putchar('\n');
}

int main (void) 
{
	int size = 0, a[100];

	a_push(a, 12, &size);
	a_push(a, 15, &size);
	a_push(a, 12, &size);
	a_push(a, 10, &size);
	a_push(a, 32, &size);
	a_push(a, 89, &size);
	a_push(a, 42, &size);
	a_push(a, 12, &size);
	a_push(a, 1, &size);
	a_push(a, 42, &size);
	a_push(a, 12, &size);
	a_push(a, 2, &size);
	a_push(a, 12, &size);
	a_push(a, 0, &size);

	counting_sort(a, size, a_max(a, size));

	a_print(a, size);
}