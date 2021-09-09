#include <stdio.h>
#include <stdlib.h>

#define STEPSIZE 1 

typedef struct node_t {
	int data;
	struct node_t * next;
} node_t;

node_t * create_list (int data[], int dsize);
int is_palindrome (const node_t * ll);
void print_list (const node_t * head);
void ll_free (node_t ** head);

int main (void)
{
	int data[] = {1, 2, 3, 4, 5, 5, 4, 3, 2, 1}, dsize = 10; 
	node_t * ll = create_list(data, dsize);

	if (is_palindrome(ll))
		printf("is is_palindrome\n");
	else
		printf("not palindrome\n");

	ll_free(&ll);
}

int is_palindrome (const node_t * ll)
{
	int 	i, 
			count = 0, maxsize = 0,
			* n 	= NULL,		/* dynamic array for keeping numbers */
			* tmp 	= NULL, 		
			status 	= 1;
	
	/* allocate an dynamic array to keep the values inside it */
	while (ll != NULL)
	{
		/* check the size of filled place */
		if (count == maxsize)
		{
			maxsize += STEPSIZE;
			tmp = (int *) calloc (maxsize, sizeof(int));

			if (tmp != NULL && n != NULL)
			{
				/* copy all the entries to new allocated place */
				for (i = 0; i < count; ++i)
					tmp[i] = n[i];

				free(n);
				n = tmp;
			}
			else
			{
				if (n != NULL)
					free(n);
				status = 0; break;
			}
		}
		n[count] = ll->data; 
		++count, ll = ll->next;	
	}
	/* status becomes 0 in case of no enough memory for new allocation o.w. it initially 1 */
	if (count != 0 && status != 0)
	{
		/* check if it is palindrome */
		for (i = 0; i < count / 2; ++i)
			if (n[i] != n[count - i - 1])
			{
				status = 0; break;
			}
			else
				printf("%d == %d\n", n[i], n[count - i - 1]);
		free(n);
	}

	return status;
}

node_t * create_list (int data[], int dsize)
{
	int i;
	node_t 	* llist = NULL,
			* tmp, * np;

	if (dsize > 0)
	{
		np = (node_t *) malloc(sizeof(node_t));

		if (np != NULL)
		{
			np->data = data[0]; 
			np->next = NULL;
			tmp = llist = np;

			for (i = 1; i < dsize; ++i)
			{
				np = (node_t *) malloc(sizeof(node_t));

				if (np != NULL)
				{
					np->data = data[i];
					tmp->next = np;		/* link new node with list 			  */
					tmp = tmp->next;	/* update tmp as points the last node */
				}
				else
				{
					ll_free(&llist); break;
				}
			}
			/* after node creation , set last node next as NULL */
			np->next = NULL;
		}
	}
	return llist;
}

void print_list (const node_t * head)
{
	if (head != NULL)
	{
		printf("%d ", head->data);
		print_list(head->next);
	}
	else
		printf("\n");
}

void ll_free (node_t ** head)
{
	node_t * tmp = NULL;

	if (head != NULL)
	{
		tmp = *head;

		while (*head != NULL)
		{
			tmp = *head;
			*head = (*head)->next;
			free(tmp);
		}
	} 
}