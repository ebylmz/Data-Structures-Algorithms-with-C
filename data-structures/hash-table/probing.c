
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define HSIZE 10

/*
	h: hashCode returned by hash function
	m: hash-table-size
	i: current count ranged from 0 to m - 1  

	linear probing    : (h + i) % m
	quadratic probing : (h + i^2) % m
	doouble hashing   : (h1 + (h2 % m) * i) % m

	if given number cannot inserted in m iteration, it does not inserted so not every number inserting
*/


int * h_create (int hsize) {return (int *) calloc(hsize, sizeof(int ));}

int hash_function1 (int k, int hsize) {return (2 * k + 3) % hsize;}
int hash_function2 (int k, int hsize) {return (3 * k + 1) % hsize;}

int linear_probing_insert (int * htable, int hsize, int data)
{
	int i, r;
	int h = hash_function1(data, hsize);

	for (i = r = 0; i < hsize && !r; ++i)
	{
		if (h == hsize) h = 0;

		if (htable[h] == 0)
		{
			htable[h] = data;
			r = 1;
		}
		else
			++h;
	}

	return r;
}

int linear_probing_delete (int * htable, int hsize, int data)
{
	int i, r;
	int h = hash_function1(data, hsize);

	for (i = r = 0; i < hsize && !r; ++i)
	{
		if (h == hsize) h = 0;
		
		if (htable[h] == data)
		{
			htable[h] = 0;
			r = 1;
		}
	}

	return r;
}

int quadratic_probing_insert (int * htable, int hsize, int data)
{
	int i, r;
	int q, h = hash_function1(data, hsize);


	for (i = r = 0; i < hsize && !r; ++i)
	{
		q = (h + i * i) % hsize;	/* quadratic probing method for collision resolution:  (hashCode + i'2) % hsize  */

		if (htable[q] == 0)
		{
			htable[q] = data;
			r = 1;
		}
	}

	return r;
} 

int double_hashing_insert (int * htable, int hsize, int data)
{
	int i, r;
	int k,
		h1 = hash_function1(data, hsize),
		h2 = hash_function2(data, hsize);


	for (i = r = 0; i < hsize && !r; ++i)
	{
		k = (h1 + (h2 % hsize) * i) % hsize; 
		
		if (htable[k] == 0)
		{
			htable[k] = data;
			r = 1;
		}
	}

	return r;
}

void arr_print (const int * a, int size) {int i; for (i = 0; i < size; ++i) printf("%2d  ", a[i]); putchar('\n');}

int main (void)
{
	int * htable = h_create(HSIZE), n;

	double_hashing_insert(htable, HSIZE, 3);
	double_hashing_insert(htable, HSIZE, 2);
	double_hashing_insert(htable, HSIZE, 9);
	double_hashing_insert(htable, HSIZE, 6);
	double_hashing_insert(htable, HSIZE, 11);
	double_hashing_insert(htable, HSIZE, 7);
	double_hashing_insert(htable, HSIZE, 12);
	arr_print(htable, HSIZE);

	free(htable);
}