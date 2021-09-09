#include <stdio.h>
#include <stdlib.h>

#define HSIZE 17

typedef struct llist_t {
	int data;
	struct llist_t * next;
} llist_t;

llist_t * ll_insert_end (llist_t * l, int data)
{
	if (l == NULL)
	{
		l = (llist_t *) malloc(sizeof(llist_t));

		if (l != NULL)
		{
			l->data = data;
			l->next = NULL;
		}
	}
	else
		l->next = ll_insert_end(l->next, data);

	return l;
}

llist_t * ll_delete (llist_t * l, int data)
{
	llist_t * tmp;

	if (l != NULL)
	{
		if (l->data == data)
		{
			tmp = l;
			l = l->next;
			free(tmp);
		}
		else
			l->next = ll_delete(l->next, data);
	}

	return l;
}

void ll_print (llist_t * l) 
{ 
	if (l != NULL) 
	{ 
		printf("%d ", l->data);
		ll_print(l->next);
	}
	else
		putchar('\n');
}


llist_t ** h_create (int size) { return (llist_t **) calloc(size, sizeof(llist_t *));}

int hash_code (int hsize, int data) { return data % hsize;}

void h_insert (llist_t ** hasht, int hsize, int data)
{
	int hcode = hash_code(hsize, data); /* apply hash function */
	hasht[hcode] = ll_insert_end(hasht[hcode], data);
}

void h_delete (llist_t ** hasht, int hsize, int data)
{
	int hcode = hash_code(hsize, data); /* apply hash function */
	hasht[hcode] = ll_delete(hasht[hcode], data);
}

void h_display (llist_t ** hasht, int hsize)
{
	int i;

	putchar('\n');

	for (i = 0; i < hsize; ++i)
	{
		printf("h[%-2d]: ", i);
		ll_print(hasht[i]);		
	}
}

int main (void)
{
	llist_t ** h = h_create(HSIZE);	/* array of llist_t pointers */

	h_insert(h, HSIZE, 23);
	h_insert(h, HSIZE, 22);
	h_insert(h, HSIZE, 3);
	h_insert(h, HSIZE, 23);
	h_insert(h, HSIZE, 54);
	h_insert(h, HSIZE, 13);
	h_insert(h, HSIZE, 17);

	h_display(h, HSIZE);

	h_delete(h, HSIZE, 23);

	h_display(h, HSIZE);
}