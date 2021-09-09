#include <stdio.h>
#include <stdlib.h>

int a_max (int * a, int size)
{
	int max = a[0];

	while (--size > 0)
		if (a[size] > max)
			max = a[size];
	return max;
}

/* mod(10) always give the last digit of the number */
int exp_value (int * a, int i, int exp) {return (a[i] / exp) % 10;}

/* specified counting-sort for radix-sort (exp & count size fixed as the number of digits (10)) */
void counting_sort (int * a, int size, int exp)
{
	int i,
		* count = (int *) calloc(10, sizeof(int)),
		* out = (int *) calloc(size, sizeof(int));

	if (count && out)
	{
		/* apply counting-sort only the digit at given exp */
		for (i = 0; i < size; ++i)
			++count[exp_value(a, i, exp)];

		for (i = 1; i < 10; ++i)
			count[i] += count[i - 1];

		for (i = size - 1; i >= 0; --i)
			out[--count[exp_value(a, i, exp)]] = a[i];

		for (i = 0; i < size; ++i)
		 	a[i] = out[i];
	}

	if (count != NULL) free(count);
	if (out != NULL) free(out);
}

/*
	# Apply counting sort for the digit number of max value
	# Each time call counting sort with exp value which is initially 1
	# Each iteration array sorted according to the digit value of exp (exp: 2 = second least important digit)
*/
void radix_sort (int * a, int size)
{
	int exp, max = a_max(a, size);

	for (exp = 1; max / exp > 0; exp *= 10)
		counting_sort(a, size, exp); 
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
	a_push(a, 100, &size);
	a_push(a, 32, &size);
	a_push(a, 3, &size);
	a_push(a, 89, &size);
	a_push(a, 421, &size);
	a_push(a, 12, &size);
	a_push(a, 13, &size);
	a_push(a, 1123, &size);
	a_push(a, 133, &size);
	a_push(a, 442, &size);
	a_push(a, 12, &size);
	a_push(a, 2, &size);
	a_push(a, 12, &size);
	a_push(a, 0, &size);

	radix_sort(a, size);

	a_print(a, size);
}